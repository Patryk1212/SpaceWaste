#include "pch.h"
#include "Camera.h"

namespace Engine
{
	Camera::Camera(const ViewMatrixData& vData)
	{
		proj = glm::perspective(glm::radians(projData.fov), projData.aspectRatio, projData.near, projData.far);
		proj[1][1] *= -1;
		onUpdateViewMatrix(vData);
	}

	void Camera::onUpdateViewMatrix(const ViewMatrixData& data)
	{
		viewData = data;
		view = glm::lookAt(viewData.cameraPos, viewData.cameraPos + viewData.cameraFront, viewData.cameraUp);
	}
}
