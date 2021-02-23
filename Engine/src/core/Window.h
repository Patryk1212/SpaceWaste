#pragma once

#include "vulkan/vulkan.h"
#include <GLFW/glfw3.h>

#include "events+input/WindowEvent.h"
#include "events+input/KeyEvent.h"
#include "events+input/MouseEvent.h"

namespace Engine
{
	using EventCallbackFn = std::function<void(Event&)>; // returns void, takes event ref

	struct WindowSpec
	{
		std::string name = "Test";
		uint32_t width = 800;
		uint32_t height = 600;

		EventCallbackFn eventCallback;
		bool vSync = false;

		WindowSpec(const std::string& name_, uint32_t width_, uint32_t height_)
			: name(name_), width(width_), height(height_) {}
	};

	class Window
	{
	public:
		Window(const WindowSpec& spec);
		~Window();

		void init();
		void onUpdate();

		inline void setEventCallback(const EventCallbackFn& callback) { windowSpec.eventCallback = callback; }
		static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

		GLFWwindow* getWindow() const;

		bool framebufferResized = false;

		bool isKeyPressed(int key_code)
		{
			//auto window = static_cast<GLFWwindow*>(windowHandle->getWindow());
			//auto window = Application::get().getWindow().getWindow();
			auto state = glfwGetKey(window, key_code);
			std::cout << "chuj " << std::endl;
			return true;// state == GLFW_PRESS;// || state == GLFW_REPEAT;
		}

	private:
		GLFWwindow* window = nullptr;
		WindowSpec windowSpec;
		
	private:
		void setVSync(bool activate);

	};
}
