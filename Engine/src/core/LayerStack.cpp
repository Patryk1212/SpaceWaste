#include "pch.h"
#include "LayerStack.h"

namespace Engine
{
	void LayerStack::addLayer(std::unique_ptr<Layer>& layer)
	{
		layers.emplace_back(std::move(layer));
	}

	std::vector<std::unique_ptr<Layer>>& LayerStack::getAllLayers()
	{
		return layers;
	}
}