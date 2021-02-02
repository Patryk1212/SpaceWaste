#pragma once

#include "Camera.h"
#include "events+input/Event.h"

namespace Engine
{
	class CameraController
	{
	public:
		CameraController();
		~CameraController() = default;

		void onUpdate(float deltaTime);
		void onEvent(Event& event);

		std::unique_ptr<Camera>& getCamera() { return camera; }

	private:
		ViewMatrixData viewData;
		float moveSpeed = 1.f;
		float zoomSpeed = 0.02f;

		float rotationSpeed = 0.05f;
		float phi{ 3.14f / 2 }, theta{ 0 };

	private:
		std::unique_ptr<Camera> camera;
	};
}