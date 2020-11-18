#pragma once

#include "Window.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

struct QueueFamilyIndices 
{
	std::optional<uint32_t> graphicsFamily;

	bool isComplete()
	{
		return graphicsFamily.has_value();
	}
};

namespace Engine
{
	class Application
	{
	public:
		Application();
		~Application();

		/*----------------------Vulkan-----------------------*/
		void initVulkan();
		void pickPhysicalDevice();
		bool isDeviceSuitable(VkPhysicalDevice device);
		//int rateDevice(VkPhysicalDevice device);
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
		/*--------------------------------------------------*/

		void run();

	private:
		std::unique_ptr<Window> window;

		VkInstance instance;
		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;


	private:
		static Application* appInstance;
	};

	Application* createApplication();
}
