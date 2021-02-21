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

		void createGraphics(const std::shared_ptr<Window>& window, const VkPhysicalDevice& physicalDevice, const VkDevice& logicalDevice);

		void startFrame();
		void updateFrame(float deltaTime, const std::unique_ptr<Camera>& camera);
		void endFrame();

		void onEvent(Event& event);
		void onShutDown();

		VkDevice getLogicalDevice() const;

	private:
		VkDevice logicaldevice;

		VkQueue graphicsQueue;
		VkQueue presentQueue;

		std::unique_ptr<VulkanSwapChain> swapChain; // remember to init
	};
}