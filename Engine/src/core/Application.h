#pragma once

#include "Window.h"
#include "Time.h"
#include "vulkan_core/VulkanContext.h"
#include "LayerStack.h"

namespace Engine
{
	class Application
	{
	public:
		Application();
		~Application();

		void run();
		void onEvent(Event& event);

		void addNewLayer(std::unique_ptr<Layer>& layer);

		//inline static Application& get() { return *appInstance; }
		//inline Window& getWindow() { return *window.get(); }

	private:
		bool shutdown(WindowCloseEvent event);

	private:
		static Application* appInstance;
		bool running = true;

	private:
		std::shared_ptr<Window> window;
		std::unique_ptr<VulkanContext> vulkanContext;

	private:
		LayerStack layerStack;
		Time timer;
	};

	Application* createApplication();
}
