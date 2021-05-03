#pragma once

#include <Engine.h>

#include "coreLib.h"
#include "orbitLib.h"

#include "core/FileLoader.h"
#include "core/SpaceObject.h"

class MainLayer : public Engine::Layer
{
public:
	MainLayer(const std::string& name) : Layer(name) {}

	virtual void onAttach() override;
	virtual void onUpdate(float deltaTime) override;
	virtual void passCamera(std::unique_ptr<Engine::CameraController>& cc) override;
	virtual bool onEvent(Engine::Event& event) override;

	virtual void setObserver(std::shared_ptr<Layer>& observer) override;
	virtual void receiveMessage(const Engine::Message& message) override;

private:
	void updateObjectsPosition(float deltaTime);

private:
	void objectsResizeZoom(Engine::Event& event);
	const float ZOOM_IN = 0.95f;
	const float ZOOM_OUT = 1.05f;

private:
	bool running = true;
	int visSpeed = 10;

private:
	std::shared_ptr<Layer> uiLayerHandle;

private:
	FileLoader fileLoader;
	std::unique_ptr<Engine::CameraController> cameraController;

private:
	int currentObjectOnFocus = 0;
	std::vector<std::shared_ptr<Engine::Object>> spaceObjects;
};
