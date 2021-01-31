#include "pch.h"
#include "VulkanIndexBuffer.h"

namespace Engine
{
	VulkanIndexBuffer::VulkanIndexBuffer(const std::unique_ptr<VulkanBufferAllocator>& bufferAlloc, const std::vector<uint16_t>& indices)
	{
		count = indices.size();

		VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;
		bufferAlloc->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			stagingBuffer, stagingBufferMemory);

		void* data;
		vkMapMemory(bufferAlloc->getLogicalDeviceHandle(), stagingBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data, indices.data(), (size_t)bufferSize);
		vkUnmapMemory(bufferAlloc->getLogicalDeviceHandle(), stagingBufferMemory);

		bufferAlloc->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			indexBuffer, indexBufferMemory);

		bufferAlloc->copyBuffer(stagingBuffer, indexBuffer, bufferSize);

		vkDestroyBuffer(bufferAlloc->getLogicalDeviceHandle(), stagingBuffer, nullptr);
		vkFreeMemory(bufferAlloc->getLogicalDeviceHandle(), stagingBufferMemory, nullptr);
	}

	VkBuffer VulkanIndexBuffer::getIndexBuffer() const
	{
		return indexBuffer;
	}

	VkDeviceMemory VulkanIndexBuffer::getIndexBufferMemory() const
	{
		return indexBufferMemory;
	}

	uint32_t VulkanIndexBuffer::getCount() const
	{
		return count;
	}
}