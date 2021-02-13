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
		void createImGuiRenderPass();

		VkCommandPool imguiCommandPool;
		VkDescriptorPool imguiPool;
		VkRenderPass imguiRenderPass;
		
		//VkDescriptorSet descriptorSets;

		std::vector<VkCommandBuffer> cmdBuffer;

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
		}

		// semaphores and fences
		std::vector<VkSemaphore> imageAvailableSemaphores1;
		std::vector<VkSemaphore> renderFinishedSemaphores1;
		std::vector<VkFence> inFlightFences1;
		std::vector<VkFence> imagesInFlight1;
		const int MAX_FRAMES_IN_FLIGHT1 = 2;
		size_t currentFrame1 = 0;


		void FrameRender(ImDrawData* draw_data)
		{
			vkWaitForFences(logicalDeviceHandle, 1, &inFlightFences1[currentFrame], VK_TRUE, UINT64_MAX);

			uint32_t imageIndex;
			VkResult result = vkAcquireNextImageKHR(logicalDeviceHandle, swapChain, UINT64_MAX, imageAvailableSemaphores1[currentFrame], VK_NULL_HANDLE, &imageIndex);

			if (result == VK_ERROR_OUT_OF_DATE_KHR)
			{
				recreateSwapChain();
				return;
			}
			else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
			{
				throw std::runtime_error("failed to acquire swap chain image!");
			}

			if (imagesInFlight1[imageIndex] != VK_NULL_HANDLE)
			{
				vkWaitForFences(logicalDeviceHandle, 1, &imagesInFlight1[imageIndex], VK_TRUE, UINT64_MAX);
			}
			imagesInFlight1[imageIndex] = inFlightFences1[currentFrame];


			vkResetCommandPool(logicalDeviceHandle, imguiCommandPool, 0);
			VkCommandBufferBeginInfo info = {};
			info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
			vkBeginCommandBuffer(cmdBuffer[imageIndex], &info);

			{	
				VkRenderPassBeginInfo info = {};
				info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
				info.renderPass = imguiRenderPass;
				info.framebuffer = swapChainFramebuffers[imageIndex];
				info.renderArea.extent = swapChainExtent;		

				std::array<VkClearValue, 2> clearValues{};
				clearValues[0].color = { 0.0f, 0.0f, 0.0f, 1.0f };
				clearValues[1].depthStencil = { 1.0f, 0 };

				info.clearValueCount = static_cast<uint32_t>(clearValues.size());
				info.pClearValues = clearValues.data();
				vkCmdBeginRenderPass(cmdBuffer[imageIndex], &info, VK_SUBPASS_CONTENTS_INLINE);
			}
		
			// Record dear imgui primitives into command buffer
			ImGui_ImplVulkan_RenderDrawData(draw_data, cmdBuffer[imageIndex]);
		
		
			// Submit command buffer
			vkCmdEndRenderPass(cmdBuffer[imageIndex]);
			
				VkSubmitInfo submitInfo{};
				submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

				VkSemaphore waitSemaphores[] = { imageAvailableSemaphores1[currentFrame] };
				VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
				submitInfo.waitSemaphoreCount = 1;
				submitInfo.pWaitSemaphores = waitSemaphores;
				submitInfo.pWaitDstStageMask = waitStages;

				submitInfo.commandBufferCount = 1;
				submitInfo.pCommandBuffers = &cmdBuffer[imageIndex];

				VkSemaphore signalSemaphores[] = { renderFinishedSemaphores1[currentFrame] };
				submitInfo.signalSemaphoreCount = 1;
				submitInfo.pSignalSemaphores = signalSemaphores;

				//vkResetFences(logicalDeviceHandle, 1, &inFlightFences1[currentFrame]);

				//VkPipelineStageFlags wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
				//VkSubmitInfo info = {};
				//info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
				//info.waitSemaphoreCount = 1;
				//info.pWaitSemaphores = &imageAvailableSemaphores1;
				//info.pWaitDstStageMask = &wait_stage;
				//info.commandBufferCount = 1;
				//info.pCommandBuffers = &cmdBuffer[imageIndex];
				//info.signalSemaphoreCount = 1;
				//info.pSignalSemaphores = &renderFinishedSemaphores1;

				vkEndCommandBuffer(cmdBuffer[imageIndex]);

				vkResetFences(logicalDeviceHandle, 1, &inFlightFences1[currentFrame]);

				if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, inFlightFences1[currentFrame]) != VK_SUCCESS)
				{
					throw std::runtime_error("failed to submit draw command buffer!");
				}
			

			// present 
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
		
			//currentFrame1 = (currentFrame1 + 1) % MAX_FRAMES_IN_FLIGHT1;
			//wd->SemaphoreIndex = (wd->SemaphoreIndex + 1) % wd->ImageCount; // Now we can use the next set of semaphores
		}
	};
}
