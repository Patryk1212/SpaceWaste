#pragma once

#include "GLFW/glfw3.h"

namespace Engine
{
	class Input
	{
	public:
		Input() = default;
		~Input() = default;
		
		// keyboard
		bool isKeyPressed(int key_code);

		// mouse
		bool isMouseButtonPressed(int button);
		float getMouseX();
		float getMouseY();
		std::pair<float, float> getMousePos();
	};
}
