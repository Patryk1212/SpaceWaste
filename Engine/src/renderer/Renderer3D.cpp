#include "pch.h"
#include "Renderer3D.h"
#include "vulkan_core/VulkanSurface.h"
#include "vulkan_core/SwapChain.h"

namespace Engine
{
	

	//struct Renderer3DData
	//{
	//	VkDescriptorPool descriptorPool;
	//	VkCommandPool commandPool;
	//	std::vector<VkCommandBuffer> commandBuffers;
	//
	//	std::unique_ptr<VulkanBufferAllocator> bufferAllocator;
	//	std::unique_ptr<VulkanVertexBuffer> vertexBuffer;
	//	std::unique_ptr<VulkanIndexBuffer> indexBuffer;
	//
	//	std::vector<std::unique_ptr<Cube>> objects;
	//
	//	VkPhysicalDevice physicalDeviceHandle;
	//	VkDevice logicalDeviceHandle;
	//
	//	VkQueue graphicsQueueHandle;
	//
	//	void init(const VkDevice& logicalDevice, const VkPhysicalDevice& physicalDevice, const SwapChainData& swapChainData, const PipeLineData& pipeline, const VkQueue& graphicsQueue)
	//	{
	//		physicalDeviceHandle = physicalDevice;
	//		logicalDeviceHandle = logicalDevice;
	//		graphicsQueueHandle = graphicsQueue;
	//
	//		//
	//		createCommandPool();
	//		bufferAllocator = std::make_unique<VulkanBufferAllocator>(physicalDeviceHandle, logicalDeviceHandle, graphicsQueueHandle, commandPool);
	//
	//		vertexBuffer = std::make_unique<VulkanVertexBuffer>(bufferAllocator, vertices);
	//		indexBuffer = std::make_unique<VulkanIndexBuffer>(bufferAllocator, indices);
	//
	//		createUniformBuffers(swapChainData);
	//
	//		createDescriptorPool(swapChainData);
	//		createDescriptorSets(swapChainData, pipeline);
	//		createCommandBuffers(swapChainData, pipeline);
	//	};
	//
	//	void createCommandPool()
	//	{
	//		QueueFamilyIndices queueFamilyIndices = VulkanSurface::findQueueFamilies(physicalDeviceHandle);
	//
	//		VkCommandPoolCreateInfo poolInfo{};
	//		poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	//		poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
	//		poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT; // 0; // Optional
	//
	//		if (vkCreateCommandPool(logicalDeviceHandle, &poolInfo, nullptr, &commandPool) != VK_SUCCESS)
	//		{
	//			throw std::runtime_error("failed to create command pool!");
	//		}
	//	};
	//
	//	void createUniformBuffers(const SwapChainData& swapChainData)
	//	{
	//		for (size_t i = 0; i < swapChainData.swapChainImages.size(); i++)
	//		{
	//			for (const auto& cube : objects)
	//			{
	//				cube->createUniformBuffer(bufferAllocator);
	//			}
	//		}
	//	};
	//
	//	void createDescriptorPool(const SwapChainData& swapChainData)
	//	{
	//		VkDescriptorPoolSize poolSize{};
	//		poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	//		poolSize.descriptorCount = static_cast<uint32_t>(swapChainData.swapChainImages.size()) * objects.size();
	//
	//		VkDescriptorPoolCreateInfo poolInfo{};
	//		poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	//		poolInfo.poolSizeCount = 1;
	//		poolInfo.pPoolSizes = &poolSize;
	//		poolInfo.maxSets = static_cast<uint32_t>(swapChainData.swapChainImages.size()) * objects.size();
	//
	//		if (vkCreateDescriptorPool(logicalDeviceHandle, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS)
	//		{
	//			throw std::runtime_error("failed to create descriptor pool!");
	//		}
	//	};
	//
	//	void createDescriptorSets(const SwapChainData& swapChainData, const PipeLineData& pipeline)
	//	{
	//		for (size_t i = 0; i < swapChainData.swapChainImages.size(); i++)
	//		{
	//			for (auto& cube : objects)
	//			{
	//				VkDescriptorSetAllocateInfo allocateInfo{};
	//				allocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	//				allocateInfo.descriptorPool = descriptorPool;
	//				allocateInfo.descriptorSetCount = 1;
	//				allocateInfo.pSetLayouts = &pipeline.descriptorSetLayout;
	//				vkAllocateDescriptorSets(logicalDeviceHandle, &allocateInfo, &cube->descriptorSet);
	//
	//
	//				VkDescriptorBufferInfo bufferInfo{};
	//				bufferInfo.buffer = cube->getUniformBuffer(i);
	//				bufferInfo.offset = 0;
	//				bufferInfo.range = sizeof(UniformBufferObject);
	//
	//
	//				VkWriteDescriptorSet writeDescriptorSets{};
	//
	//				writeDescriptorSets.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	//				writeDescriptorSets.dstSet = cube->descriptorSet;
	//				writeDescriptorSets.dstBinding = 0;
	//				writeDescriptorSets.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	//				writeDescriptorSets.pBufferInfo = &bufferInfo;
	//				writeDescriptorSets.descriptorCount = 1;
	//
	//				vkUpdateDescriptorSets(logicalDeviceHandle, 1, &writeDescriptorSets, 0, nullptr);
	//			}
	//		}
	//	};
	//
	//	void createCommandBuffers(const SwapChainData& swapChainData, const PipeLineData& pipeline)
	//	{
	//		commandBuffers.resize(swapChainData.swapChainFramebuffers.size());
	//
	//		VkCommandBufferAllocateInfo allocInfo{};
	//		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	//		allocInfo.commandPool = commandPool;
	//		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	//		allocInfo.commandBufferCount = (uint32_t)commandBuffers.size();
	//
	//		if (vkAllocateCommandBuffers(logicalDeviceHandle, &allocInfo, commandBuffers.data()) != VK_SUCCESS)
	//		{
	//			throw std::runtime_error("failed to allocate command buffers!");
	//		}
	//
	//		for (size_t i = 0; i < commandBuffers.size(); i++)
	//		{
	//			VkCommandBufferBeginInfo beginInfo{};
	//			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	//			beginInfo.flags = 0; // Optional
	//			beginInfo.pInheritanceInfo = nullptr; // Optional
	//
	//			if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS)
	//			{
	//				throw std::runtime_error("failed to begin recording command buffer!");
	//			}
	//
	//			VkRenderPassBeginInfo renderPassInfo{};
	//			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	//			renderPassInfo.renderPass = pipeline.renderPass;
	//			renderPassInfo.framebuffer = swapChainData.swapChainFramebuffers[i];
	//			renderPassInfo.renderArea.offset = { 0, 0 };
	//			renderPassInfo.renderArea.extent = swapChainData.swapChainExtent;
	//
	//			std::array<VkClearValue, 2> clearValues{};
	//			clearValues[0].color = { 0.0f, 0.0f, 0.0f, 1.0f };
	//			clearValues[1].depthStencil = { 1.0f, 0 };
	//
	//			renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
	//			renderPassInfo.pClearValues = clearValues.data();
	//
	//			/* --------------------------------------------------------------------------------- */
	//			vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
	//			vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.graphicsPipeline);
	//
	//
	//			VkBuffer vertexBuffers[] = { vertexBuffer->getVertexBuffer() };
	//			VkBuffer vertexBuffers1[] = { vertexBuffer->getVertexBuffer() };
	//
	//			VkDeviceSize offsets[] = { 0 };
	//			vkCmdBindVertexBuffers(commandBuffers[i], 0, 1, vertexBuffers, offsets);
	//			vkCmdBindIndexBuffer(commandBuffers[i], indexBuffer->getIndexBuffer(), 0, VK_INDEX_TYPE_UINT16);
	//
	//			bool earth = false;
	//			for (const auto& cube : objects)
	//			{
	//				if (!earth)
	//				{
	//					earth = true;
	//					vkCmdBindVertexBuffers(commandBuffers[i], 0, 1, vertexBuffers1, offsets);
	//				}
	//				else vkCmdBindVertexBuffers(commandBuffers[i], 0, 1, vertexBuffers, offsets);
	//
	//
	//				vkCmdBindDescriptorSets(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.pipelineLayout, 0, 1, &cube->descriptorSet, 0, nullptr);
	//
	//				vkCmdDrawIndexed(commandBuffers[i], indexBuffer->getCount(), 1, 0, 0, 0);
	//			}
	//
	//			vkCmdEndRenderPass(commandBuffers[i]);
	//
	//			if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS)
	//			{
	//				throw std::runtime_error("failed to record command buffer!");
	//			}
	//		}
	//	};
	//};

	//static Renderer3DData data;

	void Renderer3D::init(const std::shared_ptr<Window>& window, const VkPhysicalDevice& physicalDevice, const VkDevice& logicalDevice, const VkQueue& graphicsQueue, const VkQueue& presentQueue)
	{
		swapchain = new VulkanSwapChain(window, physicalDevice, logicalDevice, graphicsQueue, presentQueue);
		//data.init(logicalDevice, physicalDevice, swapChainData, pipeline, graphicsQueue);
	}

	void Renderer3D::shutDown()
	{
		swapchain->onShutDown();
		delete swapchain;
	}

	void Renderer3D::beginFrame()
	{
		swapchain->startFrame();
	}

	void Renderer3D::updateFrame(float deltaTime, const std::unique_ptr<Camera>& camera)
	{
		swapchain->updateFrame(deltaTime, camera);
	}

	void Renderer3D::endFrame()
	{
		swapchain->endFrame();
	}
}