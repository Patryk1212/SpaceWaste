#pragma once

#include "Layer.h"

namespace Engine
{
	class LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack() = default;

		void addLayer(std::shared_ptr<Layer>& layer);

		const std::vector<std::shared_ptr<Layer>>& getAllLayers() const;

	private:
		std::vector<std::shared_ptr<Layer>> layers;
	};
}