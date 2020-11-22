#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace Engine
{
	struct WindowSpec
	{
		std::string name = "Test";
		uint32_t width = 800;
		uint32_t height = 600;

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

		GLFWwindow* getWindow() const;

	private:
		GLFWwindow* window = nullptr;
		WindowSpec windowSpec;
	};
}
