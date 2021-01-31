#pragma once

#include "vulkan_core/VulkanUtility.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>

struct ViewMatrixData
{
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
};

struct ProjectionMatrixData
{
	float fov = 45.0f;
	float aspectRatio = 800.0f / 600.0f; // take this from app
	float near = 0.1f;
	float far = 1000.0f;
};

namespace Engine
{
	class Camera
	{
	public:
		Camera(const ViewMatrixData& vData);
		~Camera() = default;

		void onUpdateViewMatrix(const ViewMatrixData& data);

		const glm::mat4& getProjectionMatrix() const { return proj; }
		const glm::mat4& getViewMatrix() const { return view; }

	private:
		alignas(16) glm::mat4 proj;
		alignas(16) glm::mat4 view;

	private:
		ViewMatrixData viewData;
		ProjectionMatrixData projData;
	};
}