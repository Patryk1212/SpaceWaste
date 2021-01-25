#pragma once

#include "Camera.h"
#include "events+input/Event.h"

namespace Engine
{
	class CameraController
	{
	public:
		CameraController()
		{
			float yaw = -20;
			float pitch = 34;
			direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
			direction.y = sin(glm::radians(pitch));
			direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
			cameraFront = glm::normalize(direction);
		}

		~CameraController() = default;

		void onUpdate(float deltaTime);
		void onEvent(Event& event);

		Camera getCamera() const { return camera; }

	private:
		glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		float cameraSpeed = 0.001f;

		glm::vec3 direction;

	private:
		Camera camera;
	};
}