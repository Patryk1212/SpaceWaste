#include "pch.h"
#include "Camera.h"

namespace Engine
{
	Camera::Camera(const ViewMatrixData& vData)
	{
		proj = glm::perspective(glm::radians(projData.fov), projData.aspectRatio, projData.near, projData.far);
		proj[1][1] *= -1;
		onUpdateViewMatrix(vData,1,1);
	}

	void Camera::onUpdateViewMatrix(const ViewMatrixData& data, float phi, float theta)
	{
		viewData = data;

		float DistanceToOrigin = viewData.cameraPos.z;
		
		float x = DistanceToOrigin * sin(phi) * cos(theta);
		float y = DistanceToOrigin * cos(phi);
		float z = DistanceToOrigin * sin(phi) * sin(theta);

		glm::vec3 orbit = { x, y, z };

		viewData.cameraPos = orbit;
		
		//view = glm::lookAt(viewData.cameraPos, viewData.cameraPos + viewData.cameraFront, viewData.cameraUp);
		view = glm::lookAt(orbit, glm::vec3(0, 0, 0) /*target*/ , viewData.cameraUp);
	}
}
