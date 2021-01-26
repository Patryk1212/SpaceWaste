#pragma once

#include "VulkanSurface.h"
#include "VulkanUtility.h"

#include "core/CameraController.h"

namespace Engine
{
	const std::vector<Vertex> vertices = 
	{
			{{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}},
			{{ 1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}},
			{{-1.0f,  1.0f, -1.0f}, {0.0f, 1.0f, 1.0f}},
			{{ 1.0f,  1.0f, -1.0f}, {0.0f, 1.0f, 1.0f}},
	
			{{-1.0f, -1.0f, 1.0f }, {1.0f, 0.0f, 1.0f}},
			{{ 1.0f, -1.0f,  1.0f}, {1.0f, 0.0f, 1.0f}},
			{{ -1.0f, 1.0f,  1.0f}, {1.0f, 0.0f, 1.0f}},
			{{ 1.0f,  1.0f,  1.0f}, {1.0f, 0.0f, 1.0f}},
	
			{{-1.0f, -1.0f, -1.0f}, {1.0f, 0.0f, 1.0f}},
			{{ 1.0f, -1.0f, -1.0f}, {1.0f, 0.0f, 1.0f}},
			{{-1.0f, -1.0f, -1.0f}, {1.0f, 0.0f, 1.0f}},
			{{-1.0f, -1.0f,  1.0f}, {1.0f, 0.0f, 1.0f}},
	
			{{ 1.0f, -1.0f, -1.0f}, {0.0f, 1.0f, 1.0f}},
			{{ 1.0f, -1.0f,  1.0f}, {0.0f, 1.0f, 1.0f}}
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
		void updateUniformBuffer(uint32_t currentImage);

	private: // descriptor sets
		void createDescriptorPool();
		void createDescriptorSets();

	private: // swap chain
		VkSwapchainKHR swapChain;

		std::vector<VkImage> swapChainImages;
		VkFormat swapChainImageFormat;
		VkExtent2D swapChainExtent;
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

	private: // uniform buffers
		std::vector<VkBuffer> uniformBuffers;
		std::vector<VkDeviceMemory> uniformBuffersMemory;

	private: // descriptor sets
		VkDescriptorPool descriptorPool;
		std::vector<VkDescriptorSet> descriptorSets;

		/// 
		VkBuffer vertexBuffer;
		VkDeviceMemory vertexBufferMemory;

		VkBuffer indexBuffer;
		VkDeviceMemory indexBufferMemory;

		void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
		uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
		void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);


		void createVertexBuffer();
		void createIndexBuffer();

		/// camera
		CameraController cc;

	};
}