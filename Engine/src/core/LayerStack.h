#pragma once

#include "Layer.h"

namespace Engine
{
	class LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack() = default;

		void addLayer(std::unique_ptr<Layer>& layer);

		std::vector<std::unique_ptr<Layer>>& getAllLayers();

	private:
		std::vector<std::unique_ptr<Layer>> layers;
	};
}