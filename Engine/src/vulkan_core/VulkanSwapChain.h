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
		void createSyncObjects1();

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
		uint32_t imageIndex;
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
		uint32_t currentFrame = 0;

	private: // descriptor sets
		VkDescriptorPool descriptorPool;

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

		//imgui /* ------------------------------------ Dear Im Gui ----------------------------------------------- */
		VkRenderPass imguiRenderPass;
		void createImGuiRenderPass();

		VkDescriptorPool imguiPool;
		
		VkCommandBuffer beginSingleTimeCommands() 
		{
			VkCommandBufferAllocateInfo allocInfo{};
			allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
			allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
			allocInfo.commandPool = commandPool;
			allocInfo.commandBufferCount = 1;

			VkCommandBuffer commandBuffer;
			vkAllocateCommandBuffers(logicalDeviceHandle, &allocInfo, &commandBuffer);

			VkCommandBufferBeginInfo beginInfo{};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

			vkBeginCommandBuffer(commandBuffer, &beginInfo);

			return commandBuffer;
		}

		void endSingleTimeCommands(VkCommandBuffer commandBuffer) 
		{
			vkEndCommandBuffer(commandBuffer);

			VkSubmitInfo submitInfo{};
			submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			submitInfo.commandBufferCount = 1;
			submitInfo.pCommandBuffers = &commandBuffer;

			vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
			vkQueueWaitIdle(graphicsQueue);

			vkFreeCommandBuffers(logicalDeviceHandle, commandPool, 1, &commandBuffer);
		}

		VkCommandPool imguiCommandPool;
		std::vector<VkCommandBuffer> cmdBuffer;
		std::vector<VkFramebuffer> imguiFrameBuffers;

		void createCommandPoolImgui()
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
			

			cmdBuffer.resize(swapChainFramebuffers.size());

			VkCommandBufferAllocateInfo commandBufferAllocateInfo = {};
			commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
			commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
			commandBufferAllocateInfo.commandPool = imguiCommandPool;
			commandBufferAllocateInfo.commandBufferCount = static_cast<uint32_t>(cmdBuffer.size());
			vkAllocateCommandBuffers(logicalDeviceHandle, &commandBufferAllocateInfo, cmdBuffer.data());

			{
				imguiFrameBuffers.resize(swapChainFramebuffers.size());

				VkImageView attachment[1];
				VkFramebufferCreateInfo info = {};
				info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
				info.renderPass = imguiRenderPass;
				info.attachmentCount = 1;
				info.pAttachments = attachment;
				info.width = swapChainExtent.width;
				info.height = swapChainExtent.height;
				info.layers = 1;

				for (uint32_t i = 0; i < static_cast<uint32_t>(swapChainFramebuffers.size()); i++)
				{
					//ImGui_ImplVulkanH_Frame* fd = &wd->Frames[i];
					attachment[0] = swapChainImageViews[i];// fd->BackbufferView;
					vkCreateFramebuffer(logicalDeviceHandle, &info, nullptr, &imguiFrameBuffers[i]);
				}
			}
		}

		// semaphores and fences
		//std::vector<VkSemaphore> imageAvailableSemaphores1;
		//std::vector<VkSemaphore> renderFinishedSemaphores1;
		//std::vector<VkFence> inFlightFences1;
		//std::vector<VkFence> imagesInFlight1;
		//const int MAX_FRAMES_IN_FLIGHT1 = 2;
		//size_t currentFrame1 = 0;

		void frameRender(ImDrawData* draw_data)
		{
			//VkSemaphore image_acquired_semaphore = imageAvailableSemaphores[currentFrame];// wd->FrameSemaphores[wd->SemaphoreIndex].ImageAcquiredSemaphore;
			//VkSemaphore render_complete_semaphore = renderFinishedSemaphores[currentFrame];// wd->FrameSemaphores[wd->SemaphoreIndex].RenderCompleteSemaphore;
			//vkAcquireNextImageKHR(logicalDeviceHandle, swapChain, UINT64_MAX, image_acquired_semaphore, VK_NULL_HANDLE, &currentFrame);

			//ImGui_ImplVulkanH_Frame* fd = &wd->Frames[wd->FrameIndex];
			{
				//vkWaitForFences(logicalDeviceHandle, 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);    // wait indefinitely instead of periodically checking
				//vkResetFences(logicalDeviceHandle, 1, &inFlightFences[currentFrame]);
			}

			{
				vkResetCommandPool(logicalDeviceHandle, imguiCommandPool, 0);
				VkCommandBufferBeginInfo info = {};
				info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
				info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
				vkBeginCommandBuffer(cmdBuffer[imageIndex], &info);
			}

			{
				VkClearValue color = { 0.0f, 0.0f, 0.0f, 1.0f };
				VkRenderPassBeginInfo info = {};
				info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
				info.renderPass = imguiRenderPass;
				info.framebuffer = imguiFrameBuffers[imageIndex];
				info.renderArea.extent.width = swapChainExtent.width;
				info.renderArea.extent.height = swapChainExtent.height;
				info.clearValueCount = 1;
				info.pClearValues = &color;
				vkCmdBeginRenderPass(cmdBuffer[imageIndex], &info, VK_SUBPASS_CONTENTS_INLINE);
			}

			// Record Imgui Draw Data and draw funcs into command buffer
			ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), cmdBuffer[imageIndex]);

			// Submit command buffer
			vkCmdEndRenderPass(cmdBuffer[imageIndex]);
			vkEndCommandBuffer(cmdBuffer[imageIndex]);

		}
	};
}
