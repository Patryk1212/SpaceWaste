#include "pch.h"
#include "Application.h"

namespace Engine
{
	Application* Application::appInstance = nullptr;

	Application::Application()
	{
		Engine::WindowSpec ws("Space Debris", 1280, 720);
		window = std::make_shared<Window>(ws);
		window->init();
		window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));

		vulkanContext = std::make_unique<VulkanContext>();
		vulkanContext->initSurfaceAndDevices(window);
	}

	Application::~Application()
	{}

	void Application::run()
	{
		while (running)
		{
			timer.onUpdate((float)glfwGetTime());
			window->onUpdate();

			Renderer3D::beginFrame();
			
			for (const auto& layer : layerStack.getAllLayers())
			{
				layer->onUpdate(timer.getDeltaTime());
			}

			Renderer3D::endFrame();
		}

		Renderer3D::shutDown();
		vulkanContext->onShutDown();
	}

	void Application::onEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::shutdown, this, std::placeholders::_1));

		for (const auto& layer : layerStack.getAllLayers())
		{
			if (!layer->onEvent(event))
			{
				running = false;
			}
		}
	}

	void Application::addNewLayer(std::shared_ptr<Layer>& layer)
	{
		if (layer->getLayerName() == "MainLayer")
		{
			std::unique_ptr<CameraController> cameraController; 
			cameraController = std::make_unique<CameraController>();
			cameraController->init(window);
			layer->passCamera(cameraController);
		}
		
		layer->onAttach();
		layerStack.addLayer(layer);
	}

	bool Application::shutdown(WindowCloseEvent event)
	{
		running = false;
		return false;
	}
}
