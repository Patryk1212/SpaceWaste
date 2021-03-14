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

		void addNewLayer(std::unique_ptr<Layer>& layer);

		inline static Application& get() { return *appInstance; }
		inline Window& getWindow() { return *window; }
		inline std::shared_ptr<Window> getWindows() { return window; }

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
		std::unique_ptr<CameraController> cameraController;
	};

	Application* createApplication();
}
