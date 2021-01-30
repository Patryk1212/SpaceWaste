#include "pch.h"
#include "VulkanVertexBuffer.h"

namespace Engine
{
	VulkanVertexBuffer::VulkanVertexBuffer(const std::unique_ptr<VulkanBufferAllocator>& bufferAlloc, const std::vector<Vertex>& vertices)
	{
		VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;

		bufferAlloc->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			stagingBuffer, stagingBufferMemory);

		void* data;
		vkMapMemory(bufferAlloc->getLogicalDeviceHandle(), stagingBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data, vertices.data(), (size_t)bufferSize);
		vkUnmapMemory(bufferAlloc->getLogicalDeviceHandle(), stagingBufferMemory);

		bufferAlloc->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			vertexBuffer, vertexBufferMemory);

		bufferAlloc->copyBuffer(stagingBuffer, vertexBuffer, bufferSize);

		vkDestroyBuffer(bufferAlloc->getLogicalDeviceHandle(), stagingBuffer, nullptr);
		vkFreeMemory(bufferAlloc->getLogicalDeviceHandle(), stagingBufferMemory, nullptr);
	}

	VkBuffer VulkanVertexBuffer::getVertexBuffer() const
	{
		return vertexBuffer;
	}

	VkDeviceMemory VulkanVertexBuffer::getVertexBufferMemory() const
	{
		return vertexBufferMemory;
	}
}
