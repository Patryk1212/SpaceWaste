#include "pch.h"
#include "imguiLayer.h"

#include "vulkan_core/VulkanContext.h"

namespace Engine
{
	ImguiLayer::ImguiLayer(const std::shared_ptr<Window>& window, const VkDevice& logicalDevice, const VkPhysicalDevice& physicalDevice, const VkQueue& graphicsQueue, const SwapChainData& swapChainData)
		: windowHandle(window), logicalDeviceHandle(logicalDevice), physicalDeviceHandle(physicalDevice), graphicsQueueHandle(graphicsQueue)
	{
		createImGuiRenderPass(swapChainData.swapChainImageFormat);
		createImGuiCommandPool();
		createImGuiDescriptorPool();
		createImGuiCommandBuffers(static_cast<uint32_t>(swapChainData.swapChainFramebuffers.size()));
		createImGuiFrameBuffers(swapChainData);
		initImGui(static_cast<uint32_t>(swapChainData.swapChainImages.size()));

		commandBufferInfo = {};
		commandBufferInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		commandBufferInfo.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

		VkClearValue color = { 0.0f, 0.0f, 0.0f, 1.0f };
		renderPassInfo = {};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = imguiRenderPass;
		renderPassInfo.framebuffer = imguiFrameBuffers[0];
		renderPassInfo.renderArea.extent.width = swapChainData.swapChainExtent.width;
		renderPassInfo.renderArea.extent.height = swapChainData.swapChainExtent.height;
		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &color;
	}

	void ImguiLayer::startFrame()
	{
		ImGui_ImplVulkan_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
		////
		////// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		////if (true)
		//bool show_demo_window = true;
		//ImGui::ShowDemoWindow(&show_demo_window);

		
	}

	void ImguiLayer::endFrame(int imageIndex)
	{
		ImGui::Render();

		vkResetCommandPool(logicalDeviceHandle, imguiCommandPool, 0);
		vkBeginCommandBuffer(cmdBuffer[imageIndex], &commandBufferInfo);

		renderPassInfo.framebuffer = imguiFrameBuffers[imageIndex];
		vkCmdBeginRenderPass(cmdBuffer[imageIndex], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		// Record Imgui Draw Data and draw funcs into command buffer
		ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), cmdBuffer[imageIndex]);

		// Submit command buffer
		vkCmdEndRenderPass(cmdBuffer[imageIndex]);
		vkEndCommandBuffer(cmdBuffer[imageIndex]);
	}

	void ImguiLayer::onShutDown()
	{
		// Resources to destroy on swapchain recreation
		for (auto framebuffer : imguiFrameBuffers)
		{
			vkDestroyFramebuffer(logicalDeviceHandle, framebuffer, nullptr);
		}

		vkDestroyRenderPass(logicalDeviceHandle, imguiRenderPass, nullptr);

		vkFreeCommandBuffers(logicalDeviceHandle, imguiCommandPool, static_cast<uint32_t>(cmdBuffer.size()), cmdBuffer.data());
		vkDestroyCommandPool(logicalDeviceHandle, imguiCommandPool, nullptr);

		// Resources to destroy when the program ends
		ImGui_ImplVulkan_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		vkDestroyDescriptorPool(logicalDeviceHandle, imguiDescriptorPool, nullptr);
	}

	VkCommandBuffer ImguiLayer::getCurrentlyUsedCmdBuffer(int imageIndex) const
	{
		return cmdBuffer[imageIndex];
	}

	void ImguiLayer::initImGui(uint32_t swapChainImagesSize)
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForVulkan(windowHandle->getWindow(), true);

		ImGui_ImplVulkan_InitInfo init_info = {};
		init_info.Instance = VulkanContext::getInstance();
		init_info.PhysicalDevice = physicalDeviceHandle;
		init_info.Device = logicalDeviceHandle;
		init_info.QueueFamily = 1;
		init_info.Queue = graphicsQueueHandle;
		init_info.PipelineCache = nullptr;
		init_info.DescriptorPool = imguiDescriptorPool;
		init_info.Allocator = nullptr;
		init_info.MinImageCount = 2;
		init_info.ImageCount = swapChainImagesSize;
		init_info.CheckVkResultFn = nullptr;
		ImGui_ImplVulkan_Init(&init_info, imguiRenderPass);

		VkCommandBuffer command_buffer = beginSingleTimeCommands();
		ImGui_ImplVulkan_CreateFontsTexture(command_buffer);
		endSingleTimeCommands(command_buffer);

		ImGui_ImplVulkan_DestroyFontUploadObjects();
	}

	void ImguiLayer::createImGuiRenderPass(VkFormat swapChainImageFormat)
	{
		VkAttachmentDescription colorAttachment = {};
		colorAttachment.format = swapChainImageFormat;
		colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
		colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
		colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		colorAttachment.initialLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;// VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
		colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		VkAttachmentReference colorAttachmentRef = {};
		colorAttachmentRef.attachment = 0;
		colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		VkSubpassDescription subpass = {};
		subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass.colorAttachmentCount = 1;
		subpass.pColorAttachments = &colorAttachmentRef;

		VkSubpassDependency dependency = {};
		dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
		dependency.dstSubpass = 0;
		dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;// VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependency.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
		dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

		VkRenderPassCreateInfo info = {};
		info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		info.attachmentCount = 1;
		info.pAttachments = &colorAttachment;
		info.subpassCount = 1;
		info.pSubpasses = &subpass;
		info.dependencyCount = 1;
		info.pDependencies = &dependency;

		if (vkCreateRenderPass(logicalDeviceHandle, &info, nullptr, &imguiRenderPass) != VK_SUCCESS)
		{
			throw std::runtime_error("Could not create Dear ImGui's render pass");
		}
	}

	void ImguiLayer::createImGuiDescriptorPool()
	{
		VkDescriptorPoolSize pool_sizes[] =
		{
			{ VK_DESCRIPTOR_TYPE_SAMPLER, 1000 },
			{ VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
			{ VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000 },
			{ VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000 },
			{ VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000 },
			{ VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000 },
			{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000 },
			{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000 },
			{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
			{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
			{ VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000 }
		};

		VkDescriptorPoolCreateInfo pool_info = {};
		pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
		pool_info.maxSets = 1000 * std::size(pool_sizes);
		pool_info.poolSizeCount = std::size(pool_sizes);
		pool_info.pPoolSizes = pool_sizes;

		vkCreateDescriptorPool(logicalDeviceHandle, &pool_info, nullptr, &imguiDescriptorPool);
	}

	void ImguiLayer::createImGuiCommandPool()
	{
		QueueFamilyIndices queueFamilyIndices = VulkanSurface::findQueueFamilies(physicalDeviceHandle);

		VkCommandPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
		poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT; // Optional

		if (vkCreateCommandPool(logicalDeviceHandle, &poolInfo, nullptr, &imguiCommandPool) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create command pool!");
		}
	}

	void ImguiLayer::createImGuiCommandBuffers(uint32_t swapChainFramebuffers)
	{
		cmdBuffer.resize(swapChainFramebuffers);

		VkCommandBufferAllocateInfo commandBufferAllocateInfo = {};
		commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		commandBufferAllocateInfo.commandPool = imguiCommandPool;
		commandBufferAllocateInfo.commandBufferCount = static_cast<uint32_t>(cmdBuffer.size());
		vkAllocateCommandBuffers(logicalDeviceHandle, &commandBufferAllocateInfo, cmdBuffer.data());
	}

	void ImguiLayer::createImGuiFrameBuffers(const SwapChainData& swapChainData)
	{
		imguiFrameBuffers.resize(swapChainData.swapChainFramebuffers.size());

		VkImageView attachment[1];
		VkFramebufferCreateInfo info = {};
		info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		info.renderPass = imguiRenderPass;
		info.attachmentCount = 1;
		info.pAttachments = attachment;
		info.width = swapChainData.swapChainExtent.width;
		info.height = swapChainData.swapChainExtent.height;
		info.layers = 1;

		for (uint32_t i = 0; i < static_cast<uint32_t>(swapChainData.swapChainFramebuffers.size()); i++)
		{
			attachment[0] = swapChainData.swapChainImageViews[i];
			vkCreateFramebuffer(logicalDeviceHandle, &info, nullptr, &imguiFrameBuffers[i]);
		}
	}
}