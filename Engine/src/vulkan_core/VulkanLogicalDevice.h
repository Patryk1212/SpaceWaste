#pragma once

#include "VulkanSurface.h"

#include "renderer/Graphics.h"
#include "renderer/Renderer3D.h"

namespace Engine
{
	class VulkanLogicalDevice
	{
	public:
		VulkanLogicalDevice(const VkPhysicalDevice& physicalDevice, const std::vector<const char*>& validationLayers, const std::vector<const char*>& deviceExtensions);
		~VulkanLogicalDevice() = default;

		void createGraphics(const std::shared_ptr<Window>& window, const VkPhysicalDevice& physicalDevice, const VkDevice& logicalDevice);

		void onShutDown();

		VkDevice getLogicalDevice() const;

	private:
		VkDevice logicaldevice;

		VkQueue graphicsQueue;
		VkQueue presentQueue;
	};
}
