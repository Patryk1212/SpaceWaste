#include "pch.h"
#include "CameraController.h"

void Engine::CameraController::onUpdate()
{
	static auto startTime = std::chrono::high_resolution_clock::now();

	auto currentTime = std::chrono::high_resolution_clock::now(); // delta time
	float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

	//if (Input::isKeyPressed(EN_KEY_A))
	//	cameraPosition.x += cameraSpeed * time;
	//else if (Input::isKeyPressed(EN_KEY_D))
	//	cameraPosition.x -= cameraSpeed * time;
	//
	//if (Input::isKeyPressed(EN_KEY_S))
	//	cameraPosition.y += cameraSpeed * time;
	//else if (Input::isKeyPressed(EN_KEY_W))
	//	cameraPosition.y -= cameraSpeed * time;
}

void Engine::CameraController::onEvent(Event& event)
{

}
