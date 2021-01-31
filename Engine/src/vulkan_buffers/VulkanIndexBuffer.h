#pragma once

#include "VulkanBufferAllocator.h"

namespace Engine
{
	class VulkanIndexBuffer
	{
	public:
		VulkanIndexBuffer(const std::unique_ptr<VulkanBufferAllocator>& bufferAlloc, const std::vector<uint16_t>& indices);
		~VulkanIndexBuffer() = default;

		VkBuffer getIndexBuffer() const;
		VkDeviceMemory getIndexBufferMemory() const;
		uint32_t getCount() const;

	private:
		VkBuffer indexBuffer = nullptr;
		VkDeviceMemory indexBufferMemory = nullptr;
		uint32_t count = 0;
	};
}