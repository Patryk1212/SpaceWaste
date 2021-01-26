#include "pch.h"
#include "VulkanIndexBuffer.h"

namespace Engine
{
	VulkanIndexBuffer::VulkanIndexBuffer(const VkPhysicalDevice& physicalDevice, const VkDevice& logicalDevice, const VkQueue& graphicsQueue, const VkCommandPool& commandPool)
		: VulkanBufferAllocator(physicalDevice, logicalDevice, graphicsQueue, commandPool)
	{
	}

	void VulkanIndexBuffer::createIndexBuffer(const std::vector<uint16_t>& indices)
	{
		VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;
		createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			stagingBuffer, stagingBufferMemory);

		void* data;
		vkMapMemory(getLogicalDeviceHandle(), stagingBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data, indices.data(), (size_t)bufferSize);
		vkUnmapMemory(getLogicalDeviceHandle(), stagingBufferMemory);

		createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			indexBuffer, indexBufferMemory);

		copyBuffer(stagingBuffer, indexBuffer, bufferSize);

		vkDestroyBuffer(getLogicalDeviceHandle(), stagingBuffer, nullptr);
		vkFreeMemory(getLogicalDeviceHandle(), stagingBufferMemory, nullptr);
	}

	VkBuffer VulkanIndexBuffer::getIndexBuffer() const
	{
		return indexBuffer;
	}

	VkDeviceMemory VulkanIndexBuffer::getIndexBufferMemory() const
	{
		return indexBufferMemory;
	}
}