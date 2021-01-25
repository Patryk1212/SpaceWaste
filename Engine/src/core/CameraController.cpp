#include "pch.h"
#include "CameraController.h"

#include "core/Window.h"

void Engine::CameraController::onUpdate(float deltaTime)
{
	//if (Input::isKeyPressed(EN_KEY_A))
		//cameraPosition += cameraSpeed * cameraFront * deltaTime; // to
	//else if (Input::isKeyPressed(EN_KEY_D))
		//cameraPosition -= cameraSpeed * cameraFront * deltaTime; // from
	
	//if (Input::isKeyPressed(EN_KEY_S))
		//cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltaTime; // left
	//else if (Input::isKeyPressed(EN_KEY_W))
		//cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltaTime; // right

	camera.update(cameraFront);
	camera.updateCameraPos(cameraPosition);
}

void Engine::CameraController::onEvent(Event& event)
{
	EventDispatcher dispatcher(event);

	if (event.getEventType() == Engine::EventType::KEY_PRESSED)
	{
		cameraPosition += cameraSpeed * cameraFront;
	}
}
