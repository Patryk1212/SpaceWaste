#include "pch.h"
#include "CameraController.h"

namespace Engine
{
	CameraController::CameraController()
	{
		viewData.cameraPos = glm::vec3(0.0f, 0.0f, 8750.0f);
		viewData.cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		viewData.cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

		camera = std::make_unique<Camera>(viewData);
	}

	void CameraController::init(const std::shared_ptr<Window>& window)
	{
		windowHandle = window;
	}

	void CameraController::onUpdate()
	{
		if (windowHandle->isMouseButtonPressed(0))
		{
			float xoffset = windowHandle->getMouseX() - lastX;
			float yoffset = lastY - windowHandle->getMouseY();
			lastX = windowHandle->getMouseX();
			lastY = windowHandle->getMouseY();

			xoffset *= SENSITIVITY;
			yoffset *= SENSITIVITY;

			phi += yoffset;
			if (phi < 0.5f) phi = 0.5f;
			if (phi > 2.5f) phi = 2.5f;

			theta += xoffset;
		}
		else
		{
			lastX = windowHandle->getMouseX();
			lastY = windowHandle->getMouseY();
		}

		camera->onUpdateViewMatrix(viewData, phi, theta);
	}

	bool CameraController::onEvent(Event& event)
	{
		MouseScrollEvent& e = (MouseScrollEvent&)event;

		if (e.getEventType() == EventType::MOUSE_SCROLLED && viewData.cameraPos.z < MAX_ZOOM && viewData.cameraPos.z > MIN_ZOOM)
		{
			viewData.cameraPos += zoomSpeed * viewData.cameraFront * e.getYOffest();

			if (viewData.cameraPos.z >= MAX_ZOOM) viewData.cameraPos.z = MAX_ZOOM - 0.1f;
			if (viewData.cameraPos.z <= MIN_ZOOM) viewData.cameraPos.z = MIN_ZOOM + 0.1f;

			zoomSpeed = viewData.cameraPos.z / 25.f;

			return true;
		}

		return false;
	}

	float CameraController::getCurrentZoom() const
	{
		return viewData.cameraPos.z;
	}
}
