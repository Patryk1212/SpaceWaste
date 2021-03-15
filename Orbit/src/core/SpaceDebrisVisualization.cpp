#include "pch.h"
#include "SpaceDebrisVisualization.h"

#include "Layers/MainLayer.h"
#include "Layers/UILayer.h"

SpaceDebrisVisualization::SpaceDebrisVisualization()
{
	std::unique_ptr<Engine::Layer> mainLayer;
	mainLayer = std::make_unique<MainLayer>("MainLayer");
	addNewLayer(mainLayer);

	std::unique_ptr<Engine::Layer> uiLayer;
	uiLayer = std::make_unique<UILayer>("UserInterface");
	addNewLayer(uiLayer);
}
