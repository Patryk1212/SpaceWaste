#pragma once

#include "vulkan/vulkan.h"

namespace Engine
{
	class VulkanBuffer
	{
	public:
		VulkanBuffer() = default;
		~VulkanBuffer() = default;

		void createVertexBuffer();
		void createIndexBuffer();

	private:
		void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
		uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
		void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);	

	private:
		VkBuffer vertexBuffer;
		VkDeviceMemory vertexBufferMemory;
	};
}