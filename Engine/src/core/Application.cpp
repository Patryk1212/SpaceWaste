#include "pch.h"
#include "Application.h"

namespace Engine
{
	Application* Application::appInstance = nullptr;

	Application::Application()
	{
		/*Engine::WindowSpec ws("Space Debris", 800, 600);
		window = std::make_shared<Window>(ws);
		window->init();
		window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));

		cameraController = std::make_unique<CameraController>();
		cameraController->init(window);
		
		vulkanContext = std::make_unique<VulkanContext>();
		vulkanContext->initSurfaceAndDevices(window);
		std::cout << "Finish App constructor" << std::endl;*/
	}

	Application::~Application()
	{
		//cleanupSwapChain();
		//
		//vkDestroyDescriptorSetLayout(device, descriptorSetLayout, nullptr);
		//
		//vkDestroyBuffer(device, indexBuffer, nullptr);
		//vkFreeMemory(device, indexBufferMemory, nullptr);
		//
		//vkDestroyBuffer(device, vertexBuffer, nullptr);
		//vkFreeMemory(device, vertexBufferMemory, nullptr);
		//
		//for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) 
		//{
		//	vkDestroySemaphore(device, renderFinishedSemaphores[i], nullptr);
		//	vkDestroySemaphore(device, imageAvailableSemaphores[i], nullptr);
		//	vkDestroyFence(device, inFlightFences[i], nullptr);
		//}
		//
		//vkDestroyCommandPool(device, commandPool, nullptr);
		
		//vkDestroyDevice(device, nullptr); // already in class
		
		//if (enableValidationLayers)
		//{
		//	DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr); // already in class
		//}
		
		//vkDestroySurfaceKHR(instance, surface, nullptr); // already in class
		//vkDestroyInstance(instance, nullptr); // already in class
	}

	void Application::init()
	{
		std::cout << "START INIT" << std::endl << std::endl << std::endl;

		Engine::WindowSpec ws("Space Debris", 800, 600);
		window = std::make_shared<Window>(ws);
		window->init();
		window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));

		cameraController = std::make_unique<CameraController>();
		cameraController->init(window);

		vulkanContext = std::make_unique<VulkanContext>();
		vulkanContext->initSurfaceAndDevices(window);

		for (const auto& layer : layerStack.getAllLayers())
		{
			layer->onAttach();
		}
	}

	void Application::run()
	{
		std::cout << "START RUN" << std::endl << std::endl << std::endl;

		while (running)
		{
			timer.onUpdate((float)glfwGetTime());

			window->onUpdate();
			cameraController->onUpdate();

			Renderer3D::beginFrame();
			
			for (const auto& layer : layerStack.getAllLayers())
			{
				layer->onUpdate(timer.getDeltaTime());
			}

			//Renderer3D::updateFrame(timer.getDeltaTime(), cameraController->getCamera());
			Renderer3D::endFrame();
		}

		Renderer3D::shutDown();
		vulkanContext->onShutDown();
		//vkDeviceWaitIdle(vulkanContext->getLogicalDevice());
	}

	void Application::onEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::shutdown, this, std::placeholders::_1));

		cameraController->onEvent(event);
		
		for (const auto& layer : layerStack.getAllLayers())
		{
			if (layer->onEvent(event)) break;
		}

		// debug only
		//std::cout << event.getNameString() << std::endl;

		//if (event.getEventType() == Engine::EventType::KEY_PRESSED)
		//{
		//	std::cout << "asas" << std::endl;
		//}
	}

	void Application::addNewLayer(std::unique_ptr<Layer>& layer)
	{
		//layer->onAttach();
		layerStack.addLayer(layer);
	}

	bool Application::shutdown(WindowCloseEvent event)
	{
		running = false;
		return false;
	}
}
