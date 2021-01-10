#pragma once

#include "VulkanSurface.h"

namespace Engine
{
	class VulkanSwapChain
	{
	public:
		VulkanSwapChain(const std::unique_ptr<Window>& window, const VkPhysicalDevice& physicalDevice, const VkDevice& logicalDevice);
		~VulkanSwapChain();

	private:
		VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D chooseSwapExtent(const std::unique_ptr<Window>& window, const VkSurfaceCapabilitiesKHR& capabilities);

		void createSwapChain(const std::unique_ptr<Window>& window, const VkPhysicalDevice& physicalDevice, const VkDevice& logicaldevice);
		void createImageViews(const VkDevice& logicaldevice);

	private:
		VkSwapchainKHR swapChain;

		std::vector<VkImage> swapChainImages;
		VkFormat swapChainImageFormat;
		VkExtent2D swapChainExtent;
		std::vector<VkImageView> swapChainImageViews;
	};
}