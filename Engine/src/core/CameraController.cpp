#include "pch.h"
#include "CameraController.h"

#include "core/Window.h"

Engine::CameraController::CameraController()
{
	viewData.cameraPos = glm::vec3(0.0f, 0.0f, 70.0f);
	viewData.cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	viewData.cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	//direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	//direction.y = sin(glm::radians(pitch));
	//direction.z = -1.0f;
	//viewData.cameraFront = glm::normalize(direction);

	rotation = { 1.0f, 1.0f, 1.0f };
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

	direction.x = -cos(glm::radians(rotation.x)) * sin(glm::radians(rotation.y));
	direction.y = sin(glm::radians(rotation.x));
	direction.z = -1;

	viewData.cameraFront = glm::normalize(direction);
	//right = glm::normalize(glm::cross(viewData.cameraFront, viewData.cameraUp));
	//viewData.cameraUp = glm::normalize(glm::cross(right, viewData.cameraFront));

	camera->onUpdateViewMatrix(viewData, phi, theta);
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
	//// works 


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
	float rotSpped = 0.1f;
	if (e.getKeyCode() == EN_KEY_LEFT)
	{
		theta += rotSpped;
		//rotation.y -= rotSpped;
	}

	if (e.getKeyCode() == EN_KEY_RIGHT)
	{
		theta -= rotSpped;
		//rotation.y += rotSpped;
	}

	if (e.getKeyCode() == EN_KEY_UP)
	{
		phi += rotSpped;
	}

	if (e.getKeyCode() == EN_KEY_DOWN)
	{		
		//rotation.x += rotSpped;
		phi -=  rotSpped;
	}
}
