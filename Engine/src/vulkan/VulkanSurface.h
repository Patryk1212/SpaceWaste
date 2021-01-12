#pragma once

#include "core/Window.h"
#include "VulkanCore.h"

namespace Engine
{
	class VulkanSurface
	{
	public:
		VulkanSurface(const std::shared_ptr<Window>& window);
		~VulkanSurface();

		static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
		static SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

		static VkSurfaceKHR getSurface();

	private:
		inline static VkSurfaceKHR surface;
	};
}