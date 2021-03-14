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
	virtual bool onEvent(Engine::Event& event) override;

private:
	FileLoader fileLoader;
	// camera here
	std::unique_ptr<Engine::CameraController> cameraController;

private:
	bool xd = true;
	std::vector<std::unique_ptr<Engine::Object>> spaceObjects;
};
