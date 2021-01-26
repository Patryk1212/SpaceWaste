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
		float moveSpeed = 0.01f;

		glm::vec3 direction;
		float yaw = 0.0f;
		float pitch = 0.0f;
		float rotationSpeed = 1.0f;

	private:
		std::unique_ptr<Camera> camera;
	};
}