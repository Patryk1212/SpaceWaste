#pragma once

#include "events+input/Message.h"
#include "events+input/KeyEvent.h"
#include "events+input/MouseEvent.h"
#include "core/CameraController.h"

namespace Engine
{
	class Layer
	{
	public:
		Layer(const std::string& layerName);
		virtual ~Layer() = default;

		virtual void onAttach() {}
		virtual void onUpdate(float deltaTime) {}
		virtual void passCamera(std::unique_ptr<CameraController>& cc) {}
		virtual bool onEvent(Event& event) { return false; }

		virtual void setObserver(std::shared_ptr<Layer>& observer) {}
		virtual void receiveMessage(const Engine::Message& message) {}

		std::string getLayerName() const;

	private:
		std::string name;
	};
}