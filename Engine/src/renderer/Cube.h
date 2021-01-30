#pragma once

#include "vulkan/vulkan.h"
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "vulkan_core/VulkanUtility.h"
#include "vulkan_buffers/VulkanUniformBuffer.h"

namespace Engine
{
	class Cube
	{
	public:
		UniformBufferObject ubo;
		float rotation = 45.0f;

		glm::vec3 scale = { 1.0f, 1.0f, 1.0f };
		glm::vec3 position = { 0.0f, 0.0f, 0.0f };

		VkDescriptorSet descriptorSet; // private

		void createUniformBuffer(const std::unique_ptr<VulkanBufferAllocator>& bufferAlloc);

		VkBuffer getUniformBuffer(int imageNumber) const;
		VkDeviceMemory getUniformBufferMemory(int imageNumber) const;

	private:
		std::vector<std::unique_ptr<VulkanUniformBuffer>> uniformBuffer;
	};
}
