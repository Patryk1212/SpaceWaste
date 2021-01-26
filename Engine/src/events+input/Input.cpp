#include "pch.h"
#include "Input.h"
#include "core/Application.h"

namespace Engine
{
	bool Input::isKeyPressed(int key_code)
	{
		//auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getWindow());
		//auto state = glfwGetKey(window, key_code);
		//std::cout << "chuj " << std::endl;
		return true;// state == GLFW_PRESS;// || state == GLFW_REPEAT;
	}

	bool Input::isMouseButtonPressed(int button)
	{
		//auto window = Application::get().getWindow().getWindow();
		//auto state = glfwGetMouseButton(window, button);
		//return state == GLFW_PRESS;
		return true;
	}

	float Input::getMouseX()
	{
		auto [x, y] = getMousePos();
		return x;
	}

	float Input::getMouseY()
	{
		auto [x, y] = getMousePos();
		return y;
	}

	std::pair<float, float> Input::getMousePos()
	{
		//auto window = Application::get().getWindow().getWindow();
		double x_pos = 0, y_pos = 0;
		//glfwGetCursorPos(window, &x_pos, &y_pos);

		return { (float)x_pos, (float)y_pos };
	}
}
