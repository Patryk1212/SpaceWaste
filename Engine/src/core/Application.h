#pragma once

#include "Window.h"
#include "vulkan/VulkanContext.h"

namespace Engine
{
	class Application
	{
	public:
		Application();
		~Application();

		void run();

	private:
		std::shared_ptr<Window> window;
		std::unique_ptr<VulkanContext> vulkanContext;


	private:
		static Application* appInstance;
	};

	Application* createApplication();
}
