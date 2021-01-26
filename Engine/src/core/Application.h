#pragma once

#include "Window.h"
#include "Time.h"
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

		//inline static Application& get() { return *appInstance; }
		//inline Window& getWindow() { return *window.get(); }

	private:
		bool shutdown(WindowCloseEvent event);

	private:
		std::shared_ptr<Window> window;
		std::unique_ptr<VulkanContext> vulkanContext;

	private:
		static Application* appInstance;
		Time timer;
		bool running = true;
	};

	Application* createApplication();
}
