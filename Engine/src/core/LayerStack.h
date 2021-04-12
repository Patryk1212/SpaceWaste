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
		//const std::unique_ptr<Layer>& getLayerWithTag(const std::string& name) const;

	private:
		std::vector<std::shared_ptr<Layer>> layers;
	};
}