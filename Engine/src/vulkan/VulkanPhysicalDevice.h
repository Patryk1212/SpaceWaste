#pragma once

#include "VulkanSurface.h"

namespace Engine
{
	class VulkanPhysicalDevice
	{
	public:
		VulkanPhysicalDevice(const std::vector<const char*>& deviceExtensions);
		~VulkanPhysicalDevice() = default;

		VkPhysicalDevice getPhysicalDevice() const;

	private:
		void pickPhysicalDevice(const std::vector<const char*>& deviceExtensions);
		bool isDeviceSuitable(VkPhysicalDevice device, const std::vector<const char*>& deviceExtensions);
		int rateDevice(VkPhysicalDevice device);
		bool checkDeviceExtensionSupport(VkPhysicalDevice device, const std::vector<const char*>& deviceExtensions);

	private:
		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	};
}
