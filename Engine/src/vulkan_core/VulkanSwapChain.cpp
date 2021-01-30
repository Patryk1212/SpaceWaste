#include "pch.h"
#include "VulkanSwapChain.h"

#include "vulkan_buffers/VulkanShader.h"

namespace Engine
{
	VulkanSwapChain::VulkanSwapChain(const std::shared_ptr<Window>& window, const VkPhysicalDevice& physicalDevice, const VkDevice& logicalDevice, const VkQueue& graphicsQueue, const VkQueue& presentQueue)
		: physicalDeviceHandle(physicalDevice), logicalDeviceHandle(logicalDevice), windowHandle(window), graphicsQueue(graphicsQueue), presentQueue(presentQueue)
	{
		bool earth = false;
		glm::vec2 ring0{ 14.0f, 22.0f };
		float rho, theta;
		std::default_random_engine rndGenerator((unsigned)time(nullptr));
		std::uniform_real_distribution<float> uniformDist(0.0, 1.0);

		for (int i = 0; i < 500; i++)
		{
			auto temp = std::make_unique<Cube>();

			glm::vec3 pos;
			rho = sqrt((pow(ring0[1], 2.0f) - pow(ring0[0], 2.0f)) * uniformDist(rndGenerator) + pow(ring0[0], 2.0f));
			theta = 2.0 * 3.14 * uniformDist(rndGenerator);
			pos = glm::vec3(rho * cos(theta), uniformDist(rndGenerator) * 0.5f - 0.25f, rho * sin(theta));

			temp->scale = { 0.1f, 0.1f, 0.1f };

			if (!earth)
			{
				pos = { 0.0f, 0.0f, 0.0f };
				temp->scale = { 2.5f, 2.5f, 2.5f };
				earth = true;
			}

			temp->position = pos;

			cubes.emplace_back(std::move(temp));
		}

		createSwapChain();
		createImageViews();

		createRenderPass();
		createDescriptorSetLayout();
		createGraphicsPipeline();
		createFramebuffers();
		createCommandPool();

		bufferAllocator = std::make_unique<VulkanBufferAllocator>(physicalDevice, logicalDevice, graphicsQueue, commandPool);
		vertexBuffer = std::make_unique<VulkanVertexBuffer>(bufferAllocator, vertices);
		indexBuffer = std::make_unique<VulkanIndexBuffer>(bufferAllocator, indices);


		createUniformBuffers();

		createDescriptorPool();
		createDescriptorSets();
		createCommandBuffers();
		createSyncObjects();
	}

	void VulkanSwapChain::onUpdate(float deltaTime)
	{
		vkWaitForFences(logicalDeviceHandle, 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

		uint32_t imageIndex;
		VkResult result = vkAcquireNextImageKHR(logicalDeviceHandle, swapChain, UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

		if (result == VK_ERROR_OUT_OF_DATE_KHR)
		{
			recreateSwapChain();
			return;
		}
		else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
		{
			throw std::runtime_error("failed to acquire swap chain image!");
		}

		if (imagesInFlight[imageIndex] != VK_NULL_HANDLE)
		{
			vkWaitForFences(logicalDeviceHandle, 1, &imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
		}
		imagesInFlight[imageIndex] = inFlightFences[currentFrame];

		updateUniformBuffer(imageIndex, deltaTime);

		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

		VkSemaphore waitSemaphores[] = { imageAvailableSemaphores[currentFrame] };
		VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = waitSemaphores;
		submitInfo.pWaitDstStageMask = waitStages;

		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBuffers[imageIndex];

		VkSemaphore signalSemaphores[] = { renderFinishedSemaphores[currentFrame] };
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = signalSemaphores;

		vkResetFences(logicalDeviceHandle, 1, &inFlightFences[currentFrame]);

		if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to submit draw command buffer!");
		}

		VkPresentInfoKHR presentInfo{};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = signalSemaphores;

		VkSwapchainKHR swapChains[] = { swapChain };
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = swapChains;

		presentInfo.pImageIndices = &imageIndex;

		result = vkQueuePresentKHR(presentQueue, &presentInfo);

		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || windowHandle->framebufferResized)
		{
			windowHandle->framebufferResized = false;
			recreateSwapChain();
		}
		else if (result != VK_SUCCESS)
		{
			throw std::runtime_error("failed to present swap chain image!");
		}

		currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;

		cc.onUpdate(deltaTime);
	}

	void VulkanSwapChain::onEvent(Event& event)
	{
		cc.onEvent(event);
	}

	void VulkanSwapChain::onShutDown()
	{
		cleanupSwapChain();

		//vkDestroyDescriptorSetLayout(logicalDeviceHandle, descriptorSetLayout, nullptr); //////////////////////

		vkDestroyBuffer(logicalDeviceHandle, indexBuffer->getIndexBuffer(), nullptr);
		vkFreeMemory(logicalDeviceHandle, indexBuffer->getIndexBufferMemory(), nullptr);

		vkDestroyBuffer(logicalDeviceHandle, vertexBuffer->getVertexBuffer(), nullptr);
		vkFreeMemory(logicalDeviceHandle, vertexBuffer->getVertexBufferMemory(), nullptr);

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
		{
			vkDestroySemaphore(logicalDeviceHandle, renderFinishedSemaphores[i], nullptr);
			vkDestroySemaphore(logicalDeviceHandle, imageAvailableSemaphores[i], nullptr);
			vkDestroyFence(logicalDeviceHandle, inFlightFences[i], nullptr);
		}

		vkDestroyCommandPool(logicalDeviceHandle, commandPool, nullptr);
	}

	void VulkanSwapChain::createSyncObjects()
	{
		imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
		renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
		inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
		imagesInFlight.resize(swapChainImages.size(), VK_NULL_HANDLE);


		VkSemaphoreCreateInfo semaphoreInfo{};
		semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		VkFenceCreateInfo fenceInfo{};
		fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
		{
			if (vkCreateSemaphore(logicalDeviceHandle, &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS ||
				vkCreateSemaphore(logicalDeviceHandle, &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS ||
				vkCreateFence(logicalDeviceHandle, &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS)
			{
				throw std::runtime_error("failed to create synchronization objects for a frame!");
			}
		}
	}

	void VulkanSwapChain::recreateSwapChain()
	{
		int width = 0, height = 0;
		glfwGetFramebufferSize(windowHandle->getWindow(), &width, &height);
		while (width == 0 || height == 0)
		{
			glfwGetFramebufferSize(windowHandle->getWindow(), &width, &height);
			glfwWaitEvents();
		}

		vkDeviceWaitIdle(logicalDeviceHandle);

		cleanupSwapChain();

		createSwapChain();
		createImageViews();
		createRenderPass();
		createGraphicsPipeline();
		createFramebuffers();
		createUniformBuffers();
		createDescriptorPool();
		createDescriptorSets();
		createCommandBuffers();
	}

	void VulkanSwapChain::cleanupSwapChain()
	{
		for (size_t i = 0; i < swapChainFramebuffers.size(); i++)
		{
			vkDestroyFramebuffer(logicalDeviceHandle, swapChainFramebuffers[i], nullptr);
		}

		vkFreeCommandBuffers(logicalDeviceHandle, commandPool, static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());

		vkDestroyPipeline(logicalDeviceHandle, graphicsPipeline, nullptr);
		vkDestroyPipelineLayout(logicalDeviceHandle, pipelineLayout, nullptr);
		vkDestroyRenderPass(logicalDeviceHandle, renderPass, nullptr);

		for (size_t i = 0; i < swapChainImageViews.size(); i++)
		{
			vkDestroyImageView(logicalDeviceHandle, swapChainImageViews[i], nullptr);
		}

		vkDestroySwapchainKHR(logicalDeviceHandle, swapChain, nullptr);

		for (size_t i = 0; i < swapChainImages.size(); i++)
		{
			//vkDestroyBuffer(logicalDeviceHandle, uniformBuffers[i], nullptr);
			//vkFreeMemory(logicalDeviceHandle, uniformBuffersMemory[i], nullptr); ////////////////////////////////////////
		}

		vkDestroyDescriptorPool(logicalDeviceHandle, descriptorPool, nullptr);
	}

	VkSurfaceFormatKHR VulkanSwapChain::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
	{
		for (const auto& availableFormat : availableFormats)
		{
			if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
			{
				return availableFormat;
			}
		}

		return availableFormats[0];
	}

	VkPresentModeKHR VulkanSwapChain::chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
	{
		for (const auto& availablePresentMode : availablePresentModes)
		{
			if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
			{
				return availablePresentMode;
			}
		}

		return VK_PRESENT_MODE_FIFO_KHR;
	}

	VkExtent2D VulkanSwapChain::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
	{
		if (capabilities.currentExtent.width != UINT32_MAX)
		{
			return capabilities.currentExtent;
		}
		else
		{
			int width, height;
			glfwGetFramebufferSize(windowHandle->getWindow(), &width, &height);

			VkExtent2D actualExtent =
			{
				static_cast<uint32_t>(width),
				static_cast<uint32_t>(height)
			};

			actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
			actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));

			return actualExtent;
		}
	}

	void VulkanSwapChain::createSwapChain()
	{
		SwapChainSupportDetails swapChainSupport = VulkanSurface::querySwapChainSupport(physicalDeviceHandle);

		VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
		VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
		VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

		uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
		if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
		{
			imageCount = swapChainSupport.capabilities.maxImageCount;
		}

		VkSwapchainCreateInfoKHR createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = VulkanSurface::getSurface();

		createInfo.minImageCount = imageCount;
		createInfo.imageFormat = surfaceFormat.format;
		createInfo.imageColorSpace = surfaceFormat.colorSpace;
		createInfo.imageExtent = extent;
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		QueueFamilyIndices indices = VulkanSurface::findQueueFamilies(physicalDeviceHandle);
		uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };

		if (indices.graphicsFamily != indices.presentFamily)
		{
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = queueFamilyIndices;
		}
		else
		{
			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		}

		createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = presentMode;
		createInfo.clipped = VK_TRUE;

		createInfo.oldSwapchain = VK_NULL_HANDLE;

		if (vkCreateSwapchainKHR(logicalDeviceHandle, &createInfo, nullptr, &swapChain) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create swap chain!");
		}

		vkGetSwapchainImagesKHR(logicalDeviceHandle, swapChain, &imageCount, nullptr);
		swapChainImages.resize(imageCount);
		vkGetSwapchainImagesKHR(logicalDeviceHandle, swapChain, &imageCount, swapChainImages.data());

		swapChainImageFormat = surfaceFormat.format;
		swapChainExtent = extent;
	}

	void VulkanSwapChain::createImageViews()
	{
		swapChainImageViews.resize(swapChainImages.size());

		for (size_t i = 0; i < swapChainImages.size(); i++)
		{
			VkImageViewCreateInfo createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			createInfo.image = swapChainImages[i];
			createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
			createInfo.format = swapChainImageFormat;
			createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			createInfo.subresourceRange.baseMipLevel = 0;
			createInfo.subresourceRange.levelCount = 1;
			createInfo.subresourceRange.baseArrayLayer = 0;
			createInfo.subresourceRange.layerCount = 1;

			if (vkCreateImageView(logicalDeviceHandle, &createInfo, nullptr, &swapChainImageViews[i]) != VK_SUCCESS)
			{
				throw std::runtime_error("failed to create image views!");
			}
		}
	}

	void VulkanSwapChain::createGraphicsPipeline()
	{
		/* --- SHADERS --- */
		std::unique_ptr<VulkanShader> vertexShader;
		vertexShader = std::make_unique<VulkanShader>(logicalDeviceHandle, "src/shaders/vert.spv", "vertex");

		std::unique_ptr<VulkanShader> fragmentShader;
		fragmentShader = std::make_unique<VulkanShader>(logicalDeviceHandle, "src/shaders/frag.spv", "fragment");

		VkPipelineShaderStageCreateInfo shaderStages[] = { vertexShader->getShaderInfo(), fragmentShader->getShaderInfo() };
		/* --- */

		auto bindingDescription = Vertex::getBindingDescription(); // utilities
		auto attributeDescriptions = Vertex::getAttributeDescriptions();

		VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
		vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertexInputInfo.vertexBindingDescriptionCount = 1; // static_cast<uint32_t>(bindingDescription.size()); // change 1
		vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());

		vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;// .data(); // change
		vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

		VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
		inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		inputAssembly.primitiveRestartEnable = VK_FALSE;

		VkViewport viewport{};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = (float)swapChainExtent.width;
		viewport.height = (float)swapChainExtent.height;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		VkRect2D scissor{};
		scissor.offset = { 0, 0 };
		scissor.extent = swapChainExtent;

		VkPipelineViewportStateCreateInfo viewportState{};
		viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewportState.viewportCount = 1;
		viewportState.pViewports = &viewport;
		viewportState.scissorCount = 1;
		viewportState.pScissors = &scissor;

		VkPipelineRasterizationStateCreateInfo rasterizer{};
		rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rasterizer.depthClampEnable = VK_FALSE;
		rasterizer.rasterizerDiscardEnable = VK_FALSE;
		rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
		rasterizer.lineWidth = 1.0f;
		rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
		rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
		rasterizer.depthBiasEnable = VK_FALSE;
		rasterizer.depthBiasConstantFactor = 0.0f; // Optional
		rasterizer.depthBiasClamp = 0.0f; // Optional
		rasterizer.depthBiasSlopeFactor = 0.0f; // Optional

		VkPipelineMultisampleStateCreateInfo multisampling{};
		multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		multisampling.sampleShadingEnable = VK_FALSE;
		multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
		multisampling.minSampleShading = 1.0f; // Optional
		multisampling.pSampleMask = nullptr; // Optional
		multisampling.alphaToCoverageEnable = VK_FALSE; // Optional
		multisampling.alphaToOneEnable = VK_FALSE; // Optional

		VkPipelineColorBlendAttachmentState colorBlendAttachment{};
		colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		colorBlendAttachment.blendEnable = VK_FALSE;

		VkPipelineColorBlendStateCreateInfo colorBlending{};
		colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		colorBlending.logicOpEnable = VK_FALSE;
		colorBlending.logicOp = VK_LOGIC_OP_COPY;
		colorBlending.attachmentCount = 1;
		colorBlending.pAttachments = &colorBlendAttachment;
		colorBlending.blendConstants[0] = 0.0f;
		colorBlending.blendConstants[1] = 0.0f;
		colorBlending.blendConstants[2] = 0.0f;
		colorBlending.blendConstants[3] = 0.0f;

		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 1;
		pipelineLayoutInfo.pSetLayouts = &descriptorSetLayout;// .data(); // change from &
		//pipelineLayoutInfo.pushConstantRangeCount = 0; // Optional
		//pipelineLayoutInfo.pPushConstantRanges = nullptr; // Optional

		if (vkCreatePipelineLayout(logicalDeviceHandle, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create pipeline layout!");
		}

		VkGraphicsPipelineCreateInfo pipelineInfo{};
		pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipelineInfo.stageCount = 2;
		pipelineInfo.pStages = shaderStages;
		pipelineInfo.pVertexInputState = &vertexInputInfo;
		pipelineInfo.pInputAssemblyState = &inputAssembly;
		pipelineInfo.pViewportState = &viewportState;
		pipelineInfo.pRasterizationState = &rasterizer;
		pipelineInfo.pMultisampleState = &multisampling;
		pipelineInfo.pDepthStencilState = nullptr; // Optional
		pipelineInfo.pColorBlendState = &colorBlending;
		pipelineInfo.pDynamicState = nullptr; // Optional
		pipelineInfo.layout = pipelineLayout;
		pipelineInfo.renderPass = renderPass;
		pipelineInfo.subpass = 0;
		pipelineInfo.basePipelineHandle = VK_NULL_HANDLE; // Optional
		pipelineInfo.basePipelineIndex = -1; // Optional

		if (vkCreateGraphicsPipelines(logicalDeviceHandle, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create graphics pipeline!");
		}

		vertexShader->destroy(logicalDeviceHandle);
		fragmentShader->destroy(logicalDeviceHandle);
	}

	void VulkanSwapChain::createRenderPass()
	{
		VkAttachmentDescription colorAttachment{};
		colorAttachment.format = swapChainImageFormat;
		colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;

		colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;

		colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

		colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		VkAttachmentReference colorAttachmentRef{};
		colorAttachmentRef.attachment = 0;
		colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		VkSubpassDescription subpass{};
		subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass.colorAttachmentCount = 1;
		subpass.pColorAttachments = &colorAttachmentRef;

		VkSubpassDependency dependency{};
		dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
		dependency.dstSubpass = 0;
		dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependency.srcAccessMask = 0;
		dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

		VkRenderPassCreateInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderPassInfo.attachmentCount = 1;
		renderPassInfo.pAttachments = &colorAttachment;
		renderPassInfo.subpassCount = 1;
		renderPassInfo.pSubpasses = &subpass;
		renderPassInfo.dependencyCount = 1;
		renderPassInfo.pDependencies = &dependency;

		if (vkCreateRenderPass(logicalDeviceHandle, &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create render pass!");
		}
	}

	void VulkanSwapChain::createFramebuffers()
	{
		swapChainFramebuffers.resize(swapChainImageViews.size());

		for (size_t i = 0; i < swapChainImageViews.size(); i++)
		{
			VkImageView attachments[] =
			{
				swapChainImageViews[i]
			};

			VkFramebufferCreateInfo framebufferInfo{};
			framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			framebufferInfo.renderPass = renderPass;
			framebufferInfo.attachmentCount = 1;
			framebufferInfo.pAttachments = attachments;
			framebufferInfo.width = swapChainExtent.width;
			framebufferInfo.height = swapChainExtent.height;
			framebufferInfo.layers = 1;

			if (vkCreateFramebuffer(logicalDeviceHandle, &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS)
			{
				throw std::runtime_error("failed to create framebuffer!");
			}
		}
	}

	void VulkanSwapChain::createCommandPool()
	{
		QueueFamilyIndices queueFamilyIndices = VulkanSurface::findQueueFamilies(physicalDeviceHandle);

		VkCommandPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
		poolInfo.flags = 0; // Optional

		if (vkCreateCommandPool(logicalDeviceHandle, &poolInfo, nullptr, &commandPool) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create command pool!");
		}
	}

	void VulkanSwapChain::createCommandBuffers()
	{
		commandBuffers.resize(swapChainFramebuffers.size());

		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool = commandPool;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandBufferCount = (uint32_t)commandBuffers.size();

		if (vkAllocateCommandBuffers(logicalDeviceHandle, &allocInfo, commandBuffers.data()) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to allocate command buffers!");
		}

		for (size_t i = 0; i < commandBuffers.size(); i++)
		{
			VkCommandBufferBeginInfo beginInfo{};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			beginInfo.flags = 0; // Optional
			beginInfo.pInheritanceInfo = nullptr; // Optional

			if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS)
			{
				throw std::runtime_error("failed to begin recording command buffer!");
			}

			VkRenderPassBeginInfo renderPassInfo{};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassInfo.renderPass = renderPass;
			renderPassInfo.framebuffer = swapChainFramebuffers[i];
			renderPassInfo.renderArea.offset = { 0, 0 };
			renderPassInfo.renderArea.extent = swapChainExtent;

			VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
			renderPassInfo.clearValueCount = 1;
			renderPassInfo.pClearValues = &clearColor;

			vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
			vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);


			VkBuffer vertexBuffers[] = { vertexBuffer->getVertexBuffer() };
			VkDeviceSize offsets[] = { 0 };
			vkCmdBindVertexBuffers(commandBuffers[i], 0, 1, vertexBuffers, offsets);
			vkCmdBindIndexBuffer(commandBuffers[i], indexBuffer->getIndexBuffer(), 0, VK_INDEX_TYPE_UINT16);			  

			
			for (const auto& cube : cubes)
			{
				vkCmdBindDescriptorSets(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &cube->descriptorSet, 0, nullptr);
			
				vkCmdDrawIndexed(commandBuffers[i], indexBuffer->getCount(), 1, 0, 0, 0);
			}
			
			//vkCmdBindDescriptorSets(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &descriptorSets, 0, nullptr);
			//
			//vkCmdDrawIndexed(commandBuffers[i], indexBuffer->getCount(), 1, 0, 0, 0);

			
			//vkCmdDraw(commandBuffers[i], 6, 1, 0, 0);

			//vkCmdExecuteCommands();

			vkCmdEndRenderPass(commandBuffers[i]);

			if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS)
			{
				throw std::runtime_error("failed to record command buffer!");
			}
		}
	}

	void VulkanSwapChain::createDescriptorSetLayout()
	{
		VkDescriptorSetLayoutBinding uboLayoutBinding{};
		uboLayoutBinding.binding = 0;
		uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		uboLayoutBinding.descriptorCount = 1;
		uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
		uboLayoutBinding.pImmutableSamplers = nullptr; // Optional
		
		VkDescriptorSetLayoutCreateInfo layoutInfo1{};
		layoutInfo1.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		layoutInfo1.bindingCount = 1;
		layoutInfo1.pBindings = &uboLayoutBinding;
		
		if (vkCreateDescriptorSetLayout(logicalDeviceHandle, &layoutInfo1, nullptr, &descriptorSetLayout) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create descriptor set layout!");
		}
	}

	void VulkanSwapChain::createUniformBuffers()
	{
		for (size_t i = 0; i < swapChainImages.size(); i++)
		{
			for (const auto& cube : cubes)
			{
				cube->createUniformBuffer(bufferAllocator);
			}
		}
	}

	void VulkanSwapChain::updateUniformBuffer(uint32_t currentImage, float deltaTime)
	{
		static auto startTime = std::chrono::high_resolution_clock::now();

		auto currentTime = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

		//cubes[0]->ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.0f, 0.0f));
		//cubes[1]->ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, 0.5f, 0.0f));
		//cubes[2]->ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(3.5f, 0.5f, 0.0f));

		//cubes[0].ubo.model *= glm::rotate(glm::mat4(1.0f), time * glm::radians(cubes[0].rotation), glm::vec3(1.0f, 0.0f, 0.0f));
		//cubes[1].ubo.model *= glm::rotate(glm::mat4(1.0f), time * glm::radians(cubes[0].rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		//cubes[2].ubo.model *= glm::rotate(glm::mat4(1.0f), time * glm::radians(cubes[0].rotation), glm::vec3(0.0f, 0.0f, 1.0f));

		for (auto& cube : cubes)
		{
			//cube.ubo.model = glm::rotate(glm::mat4(1.0f), deltaTime * glm::radians(90.0f), glm::vec3(0.0f, 10.0f, 1.0f));
			cube->ubo.view = cc.getCamera()->getViewMatrix();
			cube->ubo.proj = cc.getCamera()->getProjectionMatrix();
			

			cube->ubo.model =  glm::translate(glm::mat4(1.0f), cube->position);
			cube->ubo.model *= glm::rotate(glm::mat4(1.0f), time * glm::radians(cube->rotation), glm::vec3(0.0f, 0.0f, 1.0f));
			cube->ubo.model = glm::scale(cube->ubo.model, cube->scale);


			//cube.ubo.model = glm::rotate(cube.ubo.model, glm::radians(cube.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
			//cube.ubo.model = glm::rotate(cube.ubo.model, glm::radians(cube.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
			//cube.ubo.model = glm::rotate(cube.ubo.model, glm::radians(cube.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

			void* data;
			vkMapMemory(logicalDeviceHandle, cube->getUniformBufferMemory(currentImage), 0, sizeof(cube->ubo), 0, &data);
			memcpy(data, &cube->ubo, sizeof(cube->ubo));
			vkUnmapMemory(logicalDeviceHandle, cube->getUniformBufferMemory(currentImage));

		}
	}

	void VulkanSwapChain::createDescriptorPool()
	{
		VkDescriptorPoolSize poolSize{};
		poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		poolSize.descriptorCount = static_cast<uint32_t>(swapChainImages.size()) * cubes.size();

		VkDescriptorPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		poolInfo.poolSizeCount = 1;
		poolInfo.pPoolSizes = &poolSize;
		poolInfo.maxSets = static_cast<uint32_t>(swapChainImages.size()) * cubes.size();

		if (vkCreateDescriptorPool(logicalDeviceHandle, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create descriptor pool!");
		}
	}

	void VulkanSwapChain::createDescriptorSets()
	{
		for (size_t i = 0; i < swapChainImages.size(); i++)
		{
			for (auto& cube : cubes)
			{
				VkDescriptorSetAllocateInfo allocateInfo{};
				allocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
				allocateInfo.descriptorPool = descriptorPool;
				allocateInfo.descriptorSetCount = 1;
				allocateInfo.pSetLayouts = &descriptorSetLayout;
				vkAllocateDescriptorSets(logicalDeviceHandle, &allocateInfo, &cube->descriptorSet);


				VkDescriptorBufferInfo bufferInfo{};
				bufferInfo.buffer = cube->getUniformBuffer(i);
				bufferInfo.offset = 0;
				bufferInfo.range = sizeof(UniformBufferObject);


				VkWriteDescriptorSet writeDescriptorSets{};

				writeDescriptorSets.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
				writeDescriptorSets.dstSet = cube->descriptorSet;
				writeDescriptorSets.dstBinding = 0;
				writeDescriptorSets.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
				writeDescriptorSets.pBufferInfo = &bufferInfo;
				writeDescriptorSets.descriptorCount = 1;

				vkUpdateDescriptorSets(logicalDeviceHandle, 1, &writeDescriptorSets, 0, nullptr);
			}
		}
	}
}
