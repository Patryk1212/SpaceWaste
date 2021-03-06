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

public:
	void PrintPosVel(const cSatellite& sat);

private:
	FileLoader fileLoader;

private:
	std::vector<std::unique_ptr<SpaceObject>> spaceObjects;
};
