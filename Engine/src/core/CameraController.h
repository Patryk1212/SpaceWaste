#pragma once

#include "Window.h"
#include "Camera.h"

namespace Engine
{
	class CameraController
	{
	public:
		CameraController();
		~CameraController() = default;

		void init(const std::shared_ptr<Window>& window);
		void onUpdate();
		void onEvent(Event& event);

		std::unique_ptr<Camera>& getCamera() { return camera; }

	private:
		ViewMatrixData viewData;
		float zoomSpeed = 200.f;

		float phi{ 3.14f / 2 };
		float theta{ 0 };

		float sensitivity = 0.001f;
		float lastX;
		float lastY;

	private:
		std::shared_ptr<Window> windowHandle;
		std::unique_ptr<Camera> camera;
	};
}