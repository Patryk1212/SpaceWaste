#pragma once

#include "vulkan/VulkanUtility.h"
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>

namespace Engine
{
	class Camera
	{
	public:
		Camera()
		{
			view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

			/*view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(0.0f, 1.0f, 0.0f));*/
		}
		~Camera() = default;

		const glm::mat4& getProjectionMatrix() const { return ubo.proj; }
		const glm::mat4& getViewMatrix() const { return ubo.view; }
		const glm::mat4& getViewProjectionMatrix() const { return ubo.proj; }

	private:
		UniformBufferObject ubo;

		// walking camera
		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

		glm::mat4 view;

		//// tutorial
		//glm::vec3 position = { 0.0f, 0.0f , 0.0f };
		//glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
		//glm::vec3 cameraDirection = glm::normalize(position - cameraTarget);
		//
		//glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		//glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
		//
		//glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

		
		
	};
}