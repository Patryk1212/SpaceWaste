#include "pch.h"
#include "MainLayer.h"

void MainLayer::onAttach()
{
	// download data
	// calculate info
	// create objects
}

void MainLayer::onUpdate(float deltaTime)
{
	// update objects' scale etc

	cameraController.onUpdate(deltaTime);
}

void MainLayer::onRender()
{
}

bool MainLayer::onEvent(Engine::Event& event)
{
	cameraController.onEvent(event);

	return true;
}

std::unique_ptr<Engine::Camera>& MainLayer::getCamera()
{
	return cameraController.getCamera();
}
