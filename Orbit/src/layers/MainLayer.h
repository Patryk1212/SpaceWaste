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
	virtual void onRender() override;
	virtual void passCamera(std::unique_ptr<Engine::CameraController>& cc) override;
	virtual bool onEvent(Engine::Event& event) override;

private:
	void updateObjectsPosition();

private:
	FileLoader fileLoader;
	std::unique_ptr<Engine::CameraController> cameraController;

private:
	std::vector<std::unique_ptr<Engine::Object>> spaceObjects;
};
