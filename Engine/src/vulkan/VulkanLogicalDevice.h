#pragma once

#include "VulkanSurface.h"

namespace Engine
{
	class VulkanLogicalDevice
	{
	public:
		VulkanLogicalDevice() = default;
		~VulkanLogicalDevice() = default;

		void createLogicalDevice();
	private:
		VkDevice logicaldevice;
	};
}