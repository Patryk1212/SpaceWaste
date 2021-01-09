#pragma once

#include "core/Window.h"
#include "VulkanSurface.h"

#include "vulkan/vulkan.h"

namespace Engine
{
	class VulkanContext
	{
	public:
		VulkanContext() = default;
		~VulkanContext() = default;

		void init();


		static VkInstance getInstance() { return instance; }
	private:
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

		// might be class
	private:
		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, 
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

		void setupDebugMessenger();
		VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
			const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

		// is class
	private:
		void pickPhysicalDevice();
		bool isDeviceSuitable(VkPhysicalDevice device);
		bool checkDeviceExtensionSupport(VkPhysicalDevice device);

		// is class
	private:
		void createLogicalDevice();

		// might be class
	private:
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
		SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

		// might be class
	private:
		void createSurface(std::unique_ptr<Window> window);

	private:
		inline static VkInstance instance;
		VkDebugUtilsMessengerEXT debugMessenger;

		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
		VkDevice logicaldevice;
		
		VkQueue graphicsQueue;
		VkQueue presentQueue;
		
		VkSurfaceKHR surface;

	};
}
