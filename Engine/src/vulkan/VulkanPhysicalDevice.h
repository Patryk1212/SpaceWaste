#pragma once

#include "VulkanSurface.h"

namespace Engine
{
	class VulkanPhysicalDevice
	{
	public:


	private:
		void pickPhysicalDevice();
		bool isDeviceSuitable(VkPhysicalDevice device);
		int rateDevice(VkPhysicalDevice device);
		bool checkDeviceExtensionSupport(VkPhysicalDevice device);

		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device); // maybe static 
		SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device); // maybe static

	private:
		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	};
}