#pragma once

#include "vulkan_core/VulkanSurface.h"
#include "vulkan_core/VulkanUtility.h"
#include "vulkan_core/VulkanDepthImage.h"

#include "dear_imgui/ImguiLayer.h"
#include "core/CameraController.h"

#include "vulkan_buffers/VulkanVertexBuffer.h"
#include "vulkan_buffers/VulkanIndexBuffer.h"

#include "renderer/Object.h"

namespace Engine
{
	class Graphics
	{
	public:
		Graphics(const std::shared_ptr<Window>& window, const VkPhysicalDevice& physicalDevice, const VkDevice& logicalDevice, const VkQueue& graphicsQueue, const VkQueue& presentQueue);
		~Graphics() = default;
		
		std::unique_ptr<CameraController> cameraController;
		void createObjectsAndRecord(const std::vector<std::unique_ptr<Object>>& objects);

		void startFrame();
		void updateFrame(float deltaTime, const std::unique_ptr<Camera>& camera);
		void endFrame();

		int newData = 0;
		bool ready1 = false;
		VkRenderPassBeginInfo renderPassInfo{};
		void recordCmd(int imageIndex)
		{
			VkCommandBufferBeginInfo beginInfo{};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			beginInfo.flags = VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT;// VK_COMMAND_BUFFER_USAGE_FLAG_BITS_MAX_ENUM;// VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
	
			vkResetCommandBuffer(commandBuffers[imageIndex], VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);
			if (vkBeginCommandBuffer(commandBuffers[imageIndex], &beginInfo) != VK_SUCCESS)
			{
				throw std::runtime_error("failed to begin recording command buffer!");
			}
			
			renderPassInfo.framebuffer = swapChainData.swapChainFramebuffers[imageIndex];
			vkCmdBeginRenderPass(commandBuffers[imageIndex], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
			vkCmdBindPipeline(commandBuffers[imageIndex], VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.graphicsPipeline);

			// Record new stuff
			VkBuffer vertexBuffers[] = { vertexBuffer->getVertexBuffer() };

			VkDeviceSize offsets[] = { 0 };
			vkCmdBindVertexBuffers(commandBuffers[imageIndex], 0, 1, vertexBuffers, offsets);
			vkCmdBindIndexBuffer(commandBuffers[imageIndex], indexBuffer->getIndexBuffer(), 0, VK_INDEX_TYPE_UINT16);

			for (const auto& cube : cubes)
			{
				vkCmdBindDescriptorSets(commandBuffers[imageIndex], VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.pipelineLayout, 0, 1, &cube->descriptorSet, 0, nullptr);
				vkCmdDrawIndexed(commandBuffers[imageIndex], indexBuffer->getCount(), 1, 0, 0, 0);
			}


			// Submit command buffer
			vkCmdEndRenderPass(commandBuffers[imageIndex]);

			if (vkEndCommandBuffer(commandBuffers[imageIndex]) != VK_SUCCESS)
			{
				throw std::runtime_error("failed to record command buffer!");
			}
		}

		void onShutDown();

	public:
		void createSyncObjects();
		void recreateSwapChain();
		void cleanupSwapChain();

	private:
		VkPhysicalDevice physicalDeviceHandle;
		VkDevice logicalDeviceHandle;
		std::shared_ptr<Window> windowHandle;

		VkQueue graphicsQueue;
		VkQueue presentQueue;

	private: // swap chain
		VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

		void createSwapChain();
		void createImageViews();

	private: // graphics pipeline
		void createGraphicsPipeline();

	private: // render pass
		void createRenderPass();

	private: // frame buffer
		void createFramebuffers();

	private: // command pool
		void createCommandPool();

	private: // command buffer
		void createCommandBuffers();
		void createCommandBuffers(const std::vector<std::unique_ptr<Object>>& objects);

	private: // uniforms buffers
		void createDescriptorSetLayout();

		void createUniformBuffers();//
		void createUniformBuffers(const std::vector<std::unique_ptr<Object>>& objects);//

		void updateUniformBuffer(const std::unique_ptr<Camera>& camera);//
	public:
		void updateUniformBuffer(const std::vector<std::unique_ptr<Object>>& objects);

	private: // descriptor sets
		void createDescriptorPool();
		void createDescriptorPool(const std::vector<std::unique_ptr<Object>>& objects);//
		void createDescriptorSets();
		void createDescriptorSets(const std::vector<std::unique_ptr<Object>>& objects);//

	private: // swap chain
		SwapChainData swapChainData;

	private: // graphics pipeline
		PipeLineData pipeline;

	private: // command pool
		VkCommandPool commandPool; // possible 3d

	private: // command buffer
		std::vector<VkCommandBuffer> commandBuffers; // possible 3d

	private: // semaphores and fences
		std::vector<VkSemaphore> imageAvailableSemaphores;
		std::vector<VkSemaphore> renderFinishedSemaphores;
		std::vector<VkFence> inFlightFences;
		std::vector<VkFence> imagesInFlight;
		const int MAX_FRAMES_IN_FLIGHT = 2;
		uint32_t currentFrame = 0;

	private:
		std::unique_ptr<VulkanDepthImage> depthImage;
		std::unique_ptr<ImguiLayer> imguiLayer;
		VkResult result;

		//to be deleted
		/* - - - - - - - - - - - - - - - - - - - - - - - */
		VkDescriptorPool descriptorPool; // 3d
		std::unique_ptr<VulkanBufferAllocator> bufferAllocator;
		std::unique_ptr<VulkanVertexBuffer> vertexBuffer;
		std::unique_ptr<VulkanVertexBuffer> vertexBuffer1;
		std::unique_ptr<VulkanIndexBuffer> indexBuffer;



		/* - - - - - - - - - - - - - - - - - - - - - - - */

		// cube test
		std::vector<std::unique_ptr<Object>> cubes;
	};
}
