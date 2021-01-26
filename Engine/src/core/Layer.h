#pragma once

#include "events+input/KeyEvent.h"
#include "events+input/MouseEvent.h"

namespace Engine
{
	class Layer
	{
	public:
		Layer(const std::string& layerName);
		virtual ~Layer() = default;

		virtual void onAttach() {}
		virtual void onUpdate(float deltaTime) {}
		virtual void onRender() {}
		virtual bool onEvent(Event& event) { return false; }

		std::string getLayerName() const;

	private:
		std::string name;
	};
}