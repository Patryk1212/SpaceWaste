#pragma once

#include "VulkanBufferAllocator.h"

namespace Engine
{
	class VulkanVertexBuffer : protected VulkanBufferAllocator
	{
	public:
		VulkanVertexBuffer(const VkPhysicalDevice& physicalDevice, const VkDevice& logicalDevice, const VkQueue& graphicsQueue, const VkCommandPool& commandPool);
		~VulkanVertexBuffer() = default;

		void createVertexBuffer(const std::vector<Vertex>& vertices);

		VkBuffer getVertexBuffer() const;
		VkDeviceMemory getVertexBufferMemory() const;

	private:
		VkBuffer vertexBuffer = nullptr;
		VkDeviceMemory vertexBufferMemory = nullptr;
	};
}