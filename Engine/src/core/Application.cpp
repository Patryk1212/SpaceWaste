#include "pch.h"
#include "Application.h"

namespace Engine
{
	Application* Application::appInstance = nullptr;

	Application::Application()
	{
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        GLFWwindow* window = glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);

        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

        std::cout << extensionCount << " extensions supported\n";

        glm::mat4 matrix;
        glm::vec4 vec;
        auto test = matrix * vec;

        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
	}

	void Application::run()
	{
		while (true)
		{
			printf("runs");
		}
	}
}