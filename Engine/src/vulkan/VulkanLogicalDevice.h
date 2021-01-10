#pragma once

#include "VulkanSurface.h"
#include "VulkanSwapChain.h"

namespace Engine
{
	class VulkanLogicalDevice
	{
	public:
		VulkanLogicalDevice(const VkPhysicalDevice& physicalDevice, const std::vector<const char*>& validationLayers, const std::vector<const char*>& deviceExtensions);
		~VulkanLogicalDevice();

		VkDevice getLogicalDevice() const;

	private:
		VkDevice logicaldevice;

		VkQueue graphicsQueue;
		VkQueue presentQueue;

		std::unique_ptr<VulkanSwapChain> swapChain; // remember to init
	};
}