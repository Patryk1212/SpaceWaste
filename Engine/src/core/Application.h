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
		void onEvent(Event& event);

	private:
		bool shutdown(WindowCloseEvent event);

	private:
		std::shared_ptr<Window> window;
		std::unique_ptr<VulkanContext> vulkanContext;


	private:
		static Application* appInstance;
		bool running = true;
	};

	Application* createApplication();
}
