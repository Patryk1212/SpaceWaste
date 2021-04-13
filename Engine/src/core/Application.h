#pragma once

#include "Window.h"
#include "Time.h"
#include "vulkan_core/VulkanContext.h"
#include "LayerStack.h"
#include "events+input/Input.h"

#include "renderer/Renderer3D.h"

namespace Engine
{
	class Application
	{
	public:
		Application();
		~Application();

		void run();
		void onEvent(Event& event);

		void addNewLayer(std::shared_ptr<Layer>& layer);

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
