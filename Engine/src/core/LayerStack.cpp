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

	//const std::unique_ptr<Layer>& LayerStack::getLayerWithTag(const std::string& name) const
	//{
	//	for (const auto& layer : layers)
	//	{
	//		if (layer->getLayerName() == name)
	//		{
	//			return layer;
	//		}
	//	}
	//}
}
