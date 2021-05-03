#pragma once

#include "vulkan_core/VulkanSurface.h"
#include "vulkan_core/VulkanUtility.h"
#include "vulkan_core/VulkanDepthImage.h"

#include "dear_imgui/ImguiLayer.h"
#include "core/CameraController.h"

#include "vulkan_buffers/VulkanVertexBuffer.h"
#include "vulkan_buffers/VulkanIndexBuffer.h"
#include "vulkan_core/VulkanDeviceMemory.h"

#include "renderer/Object.h"

namespace Engine
{
	class Graphics
	{
	public:
		Graphics(const std::shared_ptr<Window>& window, const VkPhysicalDevice& physicalDevice, 
			const VkDevice& logicalDevice, const VkQueue& graphicsQueue, const VkQueue& presentQueue,
			const std::vector<uint16_t>& indices, const std::vector<Vertex>& vertices);
		~Graphics() = default;
	
		void createObjectsAndRecord(const std::vector<std::shared_ptr<Object>>& objects);
		void updateUniformBuffer(const std::vector<std::shared_ptr<Object>>& objects);

		void startFrame();
		void endFrame();

		void onShutDown();

	private:
		void recreateSwapChain();
		void cleanupSwapChain();

	private:
		VkPhysicalDevice physicalDeviceHandle;
		VkDevice logicalDeviceHandle;
		std::shared_ptr<Window> windowHandle;

		VkQueue graphicsQueue;
		VkQueue presentQueue;

	private:
		VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	private:
		SwapChainData swapChainData;
		void createSwapChain();
		void createImageViews();

	private: // graphics pipeline
		PipeLineData pipeline;
		void createGraphicsPipeline();

	private: // render pass
		VkRenderPassBeginInfo renderPassInfo{};
		void createRenderPass();

	private: // frame buffer
		void createFramebuffers();

	private: // command pool
		VkCommandPool commandPool; 
		void createCommandPool();

	private: // command buffer
		std::vector<VkCommandBuffer> commandBuffers; 
		void createCommandBuffers(const std::vector<std::shared_ptr<Object>>& objects);

	private: // uniforms buffers
		std::unique_ptr<VulkanDeviceMemory> uniformBufferMemory;		
		void createDescriptorSetLayout();
		void createUniformBuffers(const std::vector<std::shared_ptr<Object>>& objects);

	private: // descriptor sets
		VkDescriptorPool descriptorPool;
		void createDescriptorPool(const std::vector<std::shared_ptr<Object>>& objects);
		void createDescriptorSets(const std::vector<std::shared_ptr<Object>>& objects);

	private: // semaphores and fences
		std::vector<VkSemaphore> imageAvailableSemaphores;
		std::vector<VkSemaphore> renderFinishedSemaphores;
		std::vector<VkFence> inFlightFences;
		std::vector<VkFence> imagesInFlight;
		const int MAX_FRAMES_IN_FLIGHT = 2;
		uint32_t currentFrame = 0;
		void createSyncObjects();

	private:
		std::unique_ptr<VulkanDepthImage> depthImage;
		std::unique_ptr<ImguiLayer> imguiLayer;
		VkResult result;

		std::unique_ptr<VulkanBufferAllocator> bufferAllocator;
		std::unique_ptr<VulkanVertexBuffer> vertexBuffer;
		std::unique_ptr<VulkanIndexBuffer> indexBuffer;
	};
}
