#include "pch.h"
#include "Window.h"

namespace Engine
{
	static void GLFWErrorCallback(int error, const char* description)
	{
		std::cout << error << description;
	}

	Window::Window(const WindowSpec& spec)
		: windowSpec(spec)
	{
		setVSync(true);
	}

	Window::~Window()
	{
		glfwDestroyWindow(window);
		//glfwTerminate();
	}

	void Window::init()
	{
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(windowSpec.width, windowSpec.height, windowSpec.name.c_str(), nullptr, nullptr);
		glfwSetWindowUserPointer(window, &windowSpec);

		glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);

		glfwSetErrorCallback(GLFWErrorCallback);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
			{
				WindowSpec& data = *(WindowSpec*)glfwGetWindowUserPointer(window);
				data.width = width;
				data.height = height;
		
				WindowResizeEvent event(width, height);
				data.eventCallback(event);
			});
		
		glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
			{
				WindowSpec& data = *(WindowSpec*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.eventCallback(event);
			});
		
		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scan_code, int action, int mods)
			{
				WindowSpec& data = *(WindowSpec*)glfwGetWindowUserPointer(window);
		
				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent event(key);
						data.eventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						data.eventCallback(event);
						break;
					}
				}
			});
		
		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowSpec& data = *(WindowSpec*)glfwGetWindowUserPointer(window);
		
				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(button);
						data.eventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(button);
						data.eventCallback(event);
						break;
					}
				}
			});
		
		glfwSetScrollCallback(window, [](GLFWwindow* window, double x_offset, double y_offset)
			{
				WindowSpec& data = *(WindowSpec*)glfwGetWindowUserPointer(window);
		
				MouseScrollEvent event((float)x_offset, (float)y_offset);
				data.eventCallback(event);
			});
		
		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x_pos, double y_pos)
			{
				WindowSpec& data = *(WindowSpec*)glfwGetWindowUserPointer(window);
		
				MouseMoveEvent event((float)x_pos, (float)y_pos);
				data.eventCallback(event);
			});
		
		glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int key_code)
			{
				WindowSpec& data = *(WindowSpec*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(key_code);
				data.eventCallback(event);
			});
	}

	void Window::onUpdate()
	{
		if (!glfwWindowShouldClose(window)) 
		{
			glfwPollEvents();
		}
	}

	void Window::framebufferResizeCallback(GLFWwindow* window, int width, int height)
	{
		auto app = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
		app->framebufferResized = true;
	}

	GLFWwindow* Window::getWindow() const
	{
		return window;
	}

	void Window::setVSync(bool activate)
	{
		if (activate)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		windowSpec.vSync = activate;
	}
}
