#include "pch.h"
#include "Application.h"

namespace Engine
{
	Application* Application::appInstance = nullptr;

	Application::Application()
	{
		Engine::WindowSpec ws("Space Debris", 800, 600);
		window = std::make_unique<Window>(ws);
		window->init();
	}

	void Application::run()
	{
		while (true)
		{
			window->onUpdate();
			printf("runs");
		}
	}
}