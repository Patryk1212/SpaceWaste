#include "pch.h"
#include "LayerStack.h"

namespace Engine
{
	void LayerStack::addLayer(std::shared_ptr<Layer>& layer)
	{
		layers.emplace_back(layer);
	}

	const std::vector<std::shared_ptr<Layer>>& LayerStack::getAllLayers() const
	{
		return layers;
	}
}
