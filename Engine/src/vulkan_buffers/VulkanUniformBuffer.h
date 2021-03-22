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
		void bindUBToBufferMemory(const std::unique_ptr<VulkanBufferAllocator>& bufferAlloc, VkDeviceMemory uniformBM, uint64_t offset);

		VkBuffer getUniformBuffer() const;

	private:
		VkBuffer uniformBuffer = nullptr;
	};
}