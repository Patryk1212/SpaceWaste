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
		glm::vec3 right;

		glm::vec3 direction;
		glm::vec3 rotation;
		float yaw = 0.0f;
		float pitch = 0.0f;
		float rotationSpeed = 1.0f;


		float phi{ 3.14f / 2 }, theta{ 0 };

	private:
		std::unique_ptr<Camera> camera;
	};
}