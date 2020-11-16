#include "pch.h"
#include "Window.h"

namespace Engine
{
	Window::Window(const WindowSpec& spec)
		: windowSpec(spec)
	{
	}

	Window::~Window()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void Window::init()
	{
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(windowSpec.width, windowSpec.height, windowSpec.name.c_str(), nullptr, nullptr);
	}

	void Window::onUpdate()
	{
		if (!glfwWindowShouldClose(window)) 
		{
			glfwPollEvents();
		}
	}
}
