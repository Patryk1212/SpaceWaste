#pragma once

#include "GLFW/glfw3.h"
#include "KeyCodes.h"

namespace Engine
{
	class Input
	{
	public:
		Input() = default;
		~Input() = default;

		// keyboard
		static bool isKeyPressed(int key_code);

		// mouse
		static bool isMouseButtonPressed(int button);
		static float getMouseX();
		static float getMouseY();
		static std::pair<float, float> getMousePos();
	};
}
