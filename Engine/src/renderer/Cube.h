#pragma once

#include "vulkan/vulkan.h"
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{
	struct Cube
	{
		UniformBufferObject ubo;
		
		//glm::vec3 position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 rotation = { 90.0f, 90.0f, 90.0f };

		VkDescriptorSet descriptorSet;
		std::vector<VkBuffer> uniformBuffer;
		std::vector<VkDeviceMemory> uniformBuffersMemory;
	};
}
