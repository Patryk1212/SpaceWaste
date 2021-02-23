#pragma once


//#include "core/Application.h"
//#include "core/Window.h"
//#include "GLFW/glfw3.h"
//#include "KeyCodes.h"

//class Window;

namespace Engine
{
	class Input
	{
	public:
		//Input(const std::shared_ptr<Window>& window);
		~Input() = default;

		// keyboard
		bool isKeyPressed(int key_code);

		// mouse
		//bool isMouseButtonPressed(int button);
		//float getMouseX();
		//float getMouseY();
		//std::pair<float, float> getMousePos();

	private:
		//std::shared_ptr<Window> windowHandle;
	};
}
