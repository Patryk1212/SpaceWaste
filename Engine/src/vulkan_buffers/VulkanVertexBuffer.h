#pragma once

#include "VulkanBufferAllocator.h"

namespace Engine
{
	class VulkanVertexBuffer
	{
	public:
		VulkanVertexBuffer(const std::unique_ptr<VulkanBufferAllocator>& bufferAlloc, const std::vector<Vertex>& vertices);
		~VulkanVertexBuffer() = default;

		VkBuffer getVertexBuffer() const;
		VkDeviceMemory getVertexBufferMemory() const;

	private:
		VkBuffer vertexBuffer = nullptr;
		VkDeviceMemory vertexBufferMemory = nullptr;
	};
}