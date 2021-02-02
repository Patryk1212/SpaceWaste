#include "pch.h"
#include "VulkanLogicalDevice.h"

namespace Engine
{
	VulkanLogicalDevice::VulkanLogicalDevice(const VkPhysicalDevice& physicalDevice, const std::vector<const char*>& validationLayers, const std::vector<const char*>& deviceExtensions)
	{
		QueueFamilyIndices indices = VulkanSurface::findQueueFamilies(physicalDevice);

		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };

		float queuePriority = 1.0f;
		for (uint32_t queueFamily : uniqueQueueFamilies)
		{
			VkDeviceQueueCreateInfo queueCreateInfo{};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = queueFamily;
			queueCreateInfo.queueCount = 1;
			queueCreateInfo.pQueuePriorities = &queuePriority;
			queueCreateInfos.push_back(queueCreateInfo);
		}

		VkPhysicalDeviceFeatures deviceFeatures{};

		VkDeviceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

		createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
		createInfo.pQueueCreateInfos = queueCreateInfos.data();

		createInfo.pEnabledFeatures = &deviceFeatures;

		createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
		createInfo.ppEnabledExtensionNames = deviceExtensions.data();

		if (enableValidationLayers)
		{
			createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
			createInfo.ppEnabledLayerNames = validationLayers.data();
		}
		else
		{
			createInfo.enabledLayerCount = 0;
		}

		if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &logicaldevice) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create logical device!");
		}

		vkGetDeviceQueue(logicaldevice, indices.graphicsFamily.value(), 0, &graphicsQueue);
		vkGetDeviceQueue(logicaldevice, indices.presentFamily.value(), 0, &presentQueue);
	}

	VulkanLogicalDevice::~VulkanLogicalDevice()
	{
		//vkDestroyDevice(logicaldevice, nullptr);
	}

	void VulkanLogicalDevice::createGraphics(const std::shared_ptr<Window>& window, const VkPhysicalDevice& physicalDevice, const VkDevice& logicalDevice)
	{
		swapChain = std::make_unique<VulkanSwapChain>(window, physicalDevice, logicalDevice, graphicsQueue, presentQueue);
	}

	void VulkanLogicalDevice::onUpdate(float deltaTime)
	{
		swapChain->onUpdate(deltaTime);
	}

	void VulkanLogicalDevice::onEvent(Event& event)
	{
		swapChain->onEvent(event);
	}

	void VulkanLogicalDevice::onShutDown()
	{
		swapChain->onShutDown();
		vkDestroyDevice(logicaldevice, nullptr);
	}

	VkDevice VulkanLogicalDevice::getLogicalDevice() const
	{
		return logicaldevice;
	}
}