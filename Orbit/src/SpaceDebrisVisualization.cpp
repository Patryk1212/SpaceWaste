#include "pch.h"
#include "SpaceDebrisVisualization.h"

SpaceDebrisVisualization::SpaceDebrisVisualization()
{
	std::unique_ptr<Engine::Layer> mainLayer;
	mainLayer = std::make_unique<Engine::Layer>("Main Layer");

	addNewLayer(mainLayer);
}
