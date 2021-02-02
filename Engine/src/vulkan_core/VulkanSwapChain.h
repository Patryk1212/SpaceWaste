#pragma once

#include "VulkanSurface.h"
#include "VulkanUtility.h"

#include "core/CameraController.h"

#include "vulkan_buffers/VulkanVertexBuffer.h"
#include "vulkan_buffers/VulkanIndexBuffer.h"

#include "renderer/Cube.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_vulkan.h"

namespace Engine
{
	const std::vector<Vertex> vertices = 
	{
			{{-1.0f, -1.0f, -1.0f}, {0.6f, 0.75f, 0.9f}},
			{{ 1.0f, -1.0f, -1.0f}, {0.13f, 0.3f, 0.4f}},
			{{-1.0f,  1.0f, -1.0f}, {0.6f, 0.75f, 0.9f}},
			{{ 1.0f,  1.0f, -1.0f}, {0.13f, 0.3f, 0.4f}},
													  
			{{-1.0f, -1.0f,  1.0f}, {1.13f, 0.3f, 0.4f}},
			{{ 1.0f, -1.0f,  1.0f}, {1.6f, 0.75f, 0.9f}},
			{{-1.0f,  1.0f,  1.0f}, {1.13f, 0.3f, 0.4f}},
			{{ 1.0f,  1.0f,  1.0f}, {1.6f, 0.75f, 0.9f}},
													  
			{{-1.0f, -1.0f, -1.0f}, {1.f, 1.f, 0.4f}},
			{{ 1.0f, -1.0f, -1.0f}, {1.f, 1.f, 0.9f}},
			{{-1.0f, -1.0f, -1.0f}, {1.f, 1.f, 0.4f}},
			{{-1.0f, -1.0f,  1.0f}, {1.f, 1.f, 0.9f}},
													  
			{{ 1.0f, -1.0f, -1.0f}, {0.13f, 0.3f, 0.4f}},
			{{ 1.0f, -1.0f,  1.0f}, {0.6f, 0.75f, 0.9f}}
	};

	const std::vector<Vertex> vertices1 =
	{
			{{-1.0f, -1.0f, -1.0f}, {0.3f, 0.5f, 0.1f}},
			{{ 1.0f, -1.0f, -1.0f}, {0.16f, 0.36f, 0.58f}},
			{{-1.0f,  1.0f, -1.0f}, {0.3f, 0.5f, 0.1f}},
			{{ 1.0f,  1.0f, -1.0f}, {0.16f, 0.36f, 0.58f}},

			{{-1.0f, -1.0f,  1.0f}, {0.3f, 0.5f, 0.1f}},
			{{ 1.0f, -1.0f,  1.0f}, {0.16f, 0.36f, 0.58f}},
			{{-1.0f,  1.0f,  1.0f}, {0.3f, 0.5f, 0.1f}},
			{{ 1.0f,  1.0f,  1.0f}, {0.16f, 0.36f, 0.58f}},

			{{-1.0f, -1.0f, -1.0f}, {0.3f, 0.5f, 0.1f}},
			{{ 1.0f, -1.0f, -1.0f}, {0.16f, 0.36f, 0.58f}},
			{{-1.0f, -1.0f, -1.0f}, {0.3f, 0.5f, 0.1f}},
			{{-1.0f, -1.0f,  1.0f}, {0.16f, 0.36f, 0.58f}},

			{{ 1.0f, -1.0f, -1.0f}, {0.16f, 0.36f, 0.58f}},
			{{ 1.0f, -1.0f,  1.0f}, {0.3f, 0.5f, 0.1f}}
	};

	const std::vector<uint16_t> indices =
	{
		0,2,1,   2,3,1,
		4,8,5,   5,8,9,
		2,6,3,   3,6,7,
		4,5,7,   4,7,6,
		2,10,11, 2,11,6,
		12,3,7,  12,7,13
	};

	class VulkanSwapChain
	{
	public:
		VulkanSwapChain(const std::shared_ptr<Window>& window, const VkPhysicalDevice& physicalDevice, const VkDevice& logicalDevice, const VkQueue& graphicsQueue, const VkQueue& presentQueue);
		~VulkanSwapChain() = default;

		void onUpdate(float deltaTime);
		void onEvent(Event& event);
		void onShutDown();

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

	private: // uniforms buffers
		void createDescriptorSetLayout();
		void createUniformBuffers();
		void updateUniformBuffer(uint32_t currentImage, float deltaTime);

	private: // descriptor sets
		void createDescriptorPool();
		void createDescriptorSets();

	private: // swap chain
		VkSwapchainKHR swapChain;
		VkFormat swapChainImageFormat;
		VkExtent2D swapChainExtent;

		std::vector<VkImage> swapChainImages;
		std::vector<VkImageView> swapChainImageViews;

	private: // graphics pipeline
		VkPipeline graphicsPipeline;
		VkDescriptorSetLayout descriptorSetLayout;
		VkPipelineLayout pipelineLayout;
		VkRenderPass renderPass;

	private: // frame buffer
		std::vector<VkFramebuffer> swapChainFramebuffers;

	private: // command pool
		VkCommandPool commandPool;

	private: // command buffer
		std::vector<VkCommandBuffer> commandBuffers;

	private: // semaphores and fences
		std::vector<VkSemaphore> imageAvailableSemaphores;
		std::vector<VkSemaphore> renderFinishedSemaphores;
		std::vector<VkFence> inFlightFences;
		std::vector<VkFence> imagesInFlight;
		const int MAX_FRAMES_IN_FLIGHT = 2;
		size_t currentFrame = 0;

	private: // descriptor sets
		VkDescriptorPool descriptorPool;
		VkDescriptorSet descriptorSets;

		/* - - - - - - - - - - - - - - - - - - - - - - - */
		std::unique_ptr<VulkanBufferAllocator> bufferAllocator;
		std::unique_ptr<VulkanVertexBuffer> vertexBuffer;
		std::unique_ptr<VulkanVertexBuffer> vertexBuffer1;
		std::unique_ptr<VulkanIndexBuffer> indexBuffer;


		/* - - - - - - - - - - - - - - - - - - - - - - - */
		void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
		VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);

		/// depth
		void createDepthResources();
		VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
		VkFormat findDepthFormat();
		bool hasStencilComponent(VkFormat format);
		VkImage depthImage;
		VkDeviceMemory depthImageMemory;
		VkImageView depthImageView;

		/// camera
		CameraController cc;


		// cube test
		std::vector<std::unique_ptr<Cube>> cubes;
	};
}