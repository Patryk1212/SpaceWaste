#include "pch.h"
#include "VulkanBufferAllocator.h"
#include "VulkanUniformBuffer.h"

namespace Engine
{
	void VulkanUniformBuffer::createUniformBuffer(const std::unique_ptr<VulkanBufferAllocator>& bufferAlloc, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties)
	{
		bufferAlloc->createBuffer(size, usage, properties, uniformBuffer, uniformBufferMemory);
	}

	VkBuffer VulkanUniformBuffer::getUniformBuffer() const
	{
		return uniformBuffer;
	}

	VkDeviceMemory VulkanUniformBuffer::getUniformBufferMemory() const
	{
		return uniformBufferMemory;
	}
}