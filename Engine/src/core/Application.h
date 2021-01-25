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

		inline static Application& get() { return *appInstance; }
		inline Window& getWindow() { return *window; }

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
