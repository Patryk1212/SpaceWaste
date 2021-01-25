#pragma once

#include "Camera.h"
#include "events+input/Event.h"

namespace Engine
{
	class CameraController
	{
	public:
		CameraController();
		~CameraController();

		void onUpdate();
		void onEvent(Event& event);

	private:
		float cameraSpeed = 10.0f;

	private:
		Camera camera;
	};
}