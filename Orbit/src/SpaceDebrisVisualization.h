#pragma once

#include <Engine.h>
#include <core/EntryPoint.h>

class SpaceDebrisVisualization : public Engine::Application
{
public:
	SpaceDebrisVisualization();
	~SpaceDebrisVisualization() = default;
};

Engine::Application* Engine::createApplication()
{
	return new SpaceDebrisVisualization();
}
