#include "pch.h"
#include "Application.h"

namespace Engine
{
	Application* Application::appInstance = nullptr;

	Application::Application()
	{
		Engine::WindowSpec ws("Space Debris", 800, 600);
		window = std::make_shared<Window>(ws);
		window->init();
		window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));

		vulkanContext = std::make_unique<VulkanContext>();
		vulkanContext->initSurfaceAndDevices(window);
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

	void Application::run()
	{
		while (running)
		{
			timer.onUpdate((float)glfwGetTime());

			for (const auto& layer : layerStack.getAllLayers())
			{
				layer->onUpdate(timer.getDeltaTime());
				layer->onRender();
			}

			window->onUpdate();
			vulkanContext->onUpdate(timer.getDeltaTime());
		}

		vulkanContext->onShutDown();
		//vkDeviceWaitIdle(vulkanContext->getLogicalDevice());
	}

	void Application::onEvent(Event& event)
	{
		vulkanContext->onEvent(event);

		EventDispatcher dispatcher(event);
		dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::shutdown, this, std::placeholders::_1));

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
		layerStack.addLayer(layer);
	}

	bool Application::shutdown(WindowCloseEvent event)
	{
		running = false;
		return false;
	}
}
