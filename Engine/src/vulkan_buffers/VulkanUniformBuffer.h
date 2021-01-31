#pragma once

#include "VulkanBufferAllocator.h"

namespace Engine
{
	class VulkanUniformBuffer
	{
	public:
		VulkanUniformBuffer() = default;
		~VulkanUniformBuffer() = default;

		void createUniformBuffer(const std::unique_ptr<VulkanBufferAllocator>& bufferAlloc, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);

		VkBuffer getUniformBuffer() const;
		VkDeviceMemory getUniformBufferMemory() const;

	private:
		VkBuffer uniformBuffer = nullptr;
		VkDeviceMemory uniformBufferMemory = nullptr;
	};
}