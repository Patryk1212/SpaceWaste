#pragma once

#include "vulkan/vulkan.h"
#include "core/Window.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_vulkan.h"

#include "vulkan_core/SwapChain.h"

namespace Engine
{
	class ImguiLayer
	{
	public:
		ImguiLayer(const std::shared_ptr<Window>& window, const VkDevice& logicalDevice, const VkPhysicalDevice& physicalDevice, const VkQueue& graphicsQueue, const SwapChainData& swapChainData);
		~ImguiLayer() = default;

		void startFrame();
		void endFrame(int imageIndex);

		void onShutDown();

		VkCommandBuffer getCurrentlyUsedCmdBuffer(int imageIndex) const;

	private:
		void initImGui(uint32_t swapChainImagesSize);
		void createImGuiRenderPass(VkFormat swapChainImageFormat);
		void createImGuiCommandPool();
		void createImGuiDescriptorPool();
		void createImGuiCommandBuffers(uint32_t swapChainFramebuffers);
		void createImGuiFrameBuffers(const SwapChainData& swapChainData);

	private:
		VkPhysicalDevice physicalDeviceHandle;
		VkDevice logicalDeviceHandle;
		std::shared_ptr<Window> windowHandle;
		VkQueue graphicsQueueHandle;

	private:
		VkRenderPass imguiRenderPass;
		VkDescriptorPool imguiDescriptorPool;
		VkCommandPool imguiCommandPool;

	private:
		std::vector<VkCommandBuffer> cmdBuffer;
		std::vector<VkFramebuffer> imguiFrameBuffers;

	private:
		VkCommandBufferBeginInfo commandBufferInfo;
		VkRenderPassBeginInfo renderPassInfo;


	private: // to be abstratced 
		VkCommandBuffer beginSingleTimeCommands()
		{
			VkCommandBufferAllocateInfo allocInfo{};
			allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
			allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
			allocInfo.commandPool = imguiCommandPool;
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

			vkQueueSubmit(graphicsQueueHandle, 1, &submitInfo, VK_NULL_HANDLE);
			vkQueueWaitIdle(graphicsQueueHandle);

			vkFreeCommandBuffers(logicalDeviceHandle, imguiCommandPool, 1, &commandBuffer);
		}
	};
}