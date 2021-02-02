#pragma once

#include "vulkan/vulkan.h"
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
