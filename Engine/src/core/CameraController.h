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
		void onUpdate(const glm::vec3& newPos);
		bool onEvent(Event& event);

		std::unique_ptr<Camera>& getCamera() { return camera; }
		std::shared_ptr<Window>& getWindowHandle() { return windowHandle; }
		float getCurrentZoom() const;

	private:
		ViewMatrixData viewData;

	private: // rotation
		float phi{ 3.14f / 2 };
		float theta{ 0 };

	private: // mouse movement
		const float SENSITIVITY = 0.001f;
		float lastX;
		float lastY;

	private: // zooming
		float zoomSpeed = 200.f;
		const float MAX_ZOOM = 18500.f;
		const float MIN_ZOOM = 1000.f;

	private:
		std::shared_ptr<Window> windowHandle;
		std::unique_ptr<Camera> camera;

		bool earthInFocus = false;
	};
}