#include "pch.h"
#include "Layer.h"

namespace Engine
{
	Layer::Layer(const std::string& layerName)
		: name(layerName)
	{
	}

	std::string Layer::getLayerName() const
	{
		return name;
	}
}