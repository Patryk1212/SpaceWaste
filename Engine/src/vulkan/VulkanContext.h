#pragma once

#include "core/Window.h"
#include "VulkanSurface.h"

#include "VulkanDebug.h"
#include "VulkanPhysicalDevice.h"
#include "VulkanLogicalDevice.h"

namespace Engine
{
	class VulkanContext
	{
	public:
		VulkanContext();
		~VulkanContext();

		static VkInstance getInstance() { return instance; }

	public:
		const std::vector<const char*> validationLayers =
		{
			"VK_LAYER_KHRONOS_validation"
		};

		const std::vector<const char*> deviceExtensions =
		{
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};

	private:
		bool checkValidationLayerSupport();
		std::vector<const char*> getRequiredExtensions();

	private:
		inline static VkInstance instance;

		std::unique_ptr<VulkanDebug> debug; // remember to init
		std::unique_ptr<VulkanPhysicalDevice> physicalDevice; // remember to init
		std::unique_ptr<VulkanLogicalDevice> logicalDevice; // remember to init

		std::unique_ptr<VulkanSurface> surface;		
	};
}
