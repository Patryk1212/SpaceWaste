#include "pch.h"
#include "VulkanBufferAllocator.h"
#include "VulkanUniformBuffer.h"

namespace Engine
{
	void VulkanUniformBuffer::createUniformBuffer(const std::unique_ptr<VulkanBufferAllocator>& bufferAlloc, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties)
	{
		VkBufferCreateInfo bufferInfo{};
		bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.size = size;
		bufferInfo.usage = usage;
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		if (vkCreateBuffer(bufferAlloc->getLogicalDeviceHandle(), &bufferInfo, nullptr, &uniformBuffer) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create buffer!");
		}
	}

	void VulkanUniformBuffer::bindUBToBufferMemory(const std::unique_ptr<VulkanBufferAllocator>& bufferAlloc, VkDeviceMemory uniformBM, uint64_t offset)
	{
		vkBindBufferMemory(bufferAlloc->getLogicalDeviceHandle(), uniformBuffer, uniformBM, offset);
	}

	VkBuffer VulkanUniformBuffer::getUniformBuffer() const
	{
		return uniformBuffer;
	}
}