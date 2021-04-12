#include "pch.h"
#include "SpaceDebrisVisualization.h"

#include "Layers/MainLayer.h"
#include "Layers/UILayer.h"

SpaceDebrisVisualization::SpaceDebrisVisualization()
{
	/* create layers */
	std::shared_ptr<Engine::Layer> mainLayer;
	mainLayer = std::make_unique<MainLayer>("MainLayer");

	std::shared_ptr<Engine::Layer> uiLayer;
	uiLayer = std::make_unique<UILayer>("UserInterface");
	
	/* set observers */
	mainLayer->setObserver(uiLayer);
	uiLayer->setObserver(mainLayer);
	
	/* push layers to app*/
	addNewLayer(mainLayer);
	addNewLayer(uiLayer);
}
