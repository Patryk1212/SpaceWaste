#pragma once

#include "vulkan_core/VulkanUtility.h"

#include <GLFW/glfw3.h>

struct ViewMatrixData
{
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	glm::vec3 cameraCenter{ 0.f, 0.f, 0.f };
};

struct ProjectionMatrixData
{
	float fov = 45.0f;
	float aspectRatio = 1280.0f / 720.0f;
	float near = 0.1f;
	float far = 100000.0f;
};

namespace Engine
{
	class Camera
	{
	public:
		Camera(const ViewMatrixData& vData);
		~Camera() = default;

		void onUpdateViewMatrix(const ViewMatrixData& data, float phi, float theta);

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