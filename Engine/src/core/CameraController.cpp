#include "pch.h"
#include "CameraController.h"

#include "core/Window.h"

Engine::CameraController::CameraController()
{
	viewData.cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
	viewData.cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	viewData.cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	//direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	//direction.y = sin(glm::radians(pitch));
	//direction.z = -1.0f;
	//viewData.cameraFront = glm::normalize(direction);

	camera = std::make_unique<Camera>(viewData);
}

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

	

	camera->onUpdateViewMatrix(viewData);
}

void Engine::CameraController::onEvent(Event& event)
{
	Engine::KeyPressedEvent& e = (Engine::KeyPressedEvent&)event;
	
	float help = 100.0f; // delta time in future

	// move
	if (e.getKeyCode() == EN_KEY_Q)
	{
		viewData.cameraPos -= moveSpeed * viewData.cameraFront * help;
	}

	if (e.getKeyCode() == EN_KEY_E)
	{
		viewData.cameraPos += moveSpeed * viewData.cameraFront * help;
	}

	if (e.getKeyCode() == EN_KEY_W)
	{
		viewData.cameraPos -= moveSpeed * viewData.cameraUp * help;
	}

	if (e.getKeyCode() == EN_KEY_S)
	{
		viewData.cameraPos += moveSpeed * viewData.cameraUp * help;
	}
		
	if (e.getKeyCode() == EN_KEY_A)
	{
		viewData.cameraPos += glm::normalize(glm::cross(viewData.cameraFront, viewData.cameraUp)) * moveSpeed * help;
	}

	if (e.getKeyCode() == EN_KEY_D)
	{
		viewData.cameraPos -= glm::normalize(glm::cross(viewData.cameraFront, viewData.cameraUp)) * moveSpeed * help;
	}

	// rot
	if (e.getKeyCode() == EN_KEY_LEFT)
	{
		yaw += rotationSpeed;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		//.z = sin(glm::radians(yaw))* cos(glm::radians(pitch));
		viewData.cameraFront = glm::normalize(direction);
	}

	if (e.getKeyCode() == EN_KEY_RIGHT)
	{
		yaw -= rotationSpeed;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		//direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		viewData.cameraFront = glm::normalize(direction);
	}

	if (e.getKeyCode() == EN_KEY_UP)
	{
		pitch -= rotationSpeed;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		//direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		viewData.cameraFront = glm::normalize(direction);
	}

	if (e.getKeyCode() == EN_KEY_DOWN)
	{
		pitch += rotationSpeed;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		//direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		viewData.cameraFront = glm::normalize(direction);
	}
}
