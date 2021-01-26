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

		void initSurfaceAndDevices(const std::shared_ptr<Window>& window);

		void onUpdate(float deltaTime);
		void onEvent(Event& event); // temp
		void onShutDown();

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
		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

	private:
		inline static VkInstance instance;

		std::unique_ptr<VulkanDebug> debug;
		
		std::unique_ptr<VulkanSurface> surface;
		std::unique_ptr<VulkanPhysicalDevice> physicalDevice;
		std::unique_ptr<VulkanLogicalDevice> logicalDevice;

	};
}
