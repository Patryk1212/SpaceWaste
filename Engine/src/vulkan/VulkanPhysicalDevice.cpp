#include "pch.h"
#include "VulkanPhysicalDevice.h"

#include "VulkanContext.h"

namespace Engine
{
	VulkanPhysicalDevice::VulkanPhysicalDevice(const std::vector<const char*>& deviceExtensions)
	{
		pickPhysicalDevice(deviceExtensions);
	}

	VkPhysicalDevice VulkanPhysicalDevice::getPhysicalDevice() const
	{
		return physicalDevice;
	}

	void VulkanPhysicalDevice::pickPhysicalDevice(const std::vector<const char*>& deviceExtensions)
	{
		auto instance = VulkanContext::getInstance();

		// find cards that suports vulkan
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

		if (deviceCount == 0)
		{
			throw std::runtime_error("failed to find GPUs with Vulkan support!");
		}

		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());		

		// find the best graphics card available
		std::multimap<int, VkPhysicalDevice> candidates;

		for (const auto& device : devices) 
		{
			int score = 0;

			if (isDeviceSuitable(device, deviceExtensions))
			{
				score = rateDevice(device);
			}
			
			candidates.insert(std::make_pair(score, device));
		}

		// Check if the best candidate is suitable at all
		if (candidates.rbegin()->first > 0) 
		{
			physicalDevice = candidates.rbegin()->second;
		}
		else 
		{
			throw std::runtime_error("failed to find a suitable GPU!");
		}
	}

	bool VulkanPhysicalDevice::isDeviceSuitable(VkPhysicalDevice device, const std::vector<const char*>& deviceExtensions)
	{
		QueueFamilyIndices indices = VulkanSurface::findQueueFamilies(device);

		bool extensionsSupported = checkDeviceExtensionSupport(device, deviceExtensions);

		bool swapChainAdequate = false;
		if (extensionsSupported)
		{
			SwapChainSupportDetails swapChainSupport = VulkanSurface::querySwapChainSupport(device);
			swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
		}

		return indices.isComplete() && extensionsSupported && swapChainAdequate;
	}

	int VulkanPhysicalDevice::rateDevice(VkPhysicalDevice device)
	{
		VkPhysicalDeviceProperties physicalDeviceProperties{};
		VkPhysicalDeviceFeatures physiclaDeviceFeatures{};

		int score = 0;

		// Discrete GPUs have a significant performance advantage
		if (physicalDeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
		{
			score += 1000;
		}

		// Maximum possible size of textures affects graphics quality
		score += physicalDeviceProperties.limits.maxImageDimension2D;

		// Application can't function without geometry shaders
		if (!physiclaDeviceFeatures.geometryShader)
		{
			return 0;
		}

		return score;
	}

	bool VulkanPhysicalDevice::checkDeviceExtensionSupport(VkPhysicalDevice device, const std::vector<const char*>& deviceExtensions)
	{
		uint32_t extensionCount;
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

		std::vector<VkExtensionProperties> availableExtensions(extensionCount);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

		std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

		for (const auto& extension : availableExtensions)
		{
			requiredExtensions.erase(extension.extensionName);
		}

		return requiredExtensions.empty();
	}
}