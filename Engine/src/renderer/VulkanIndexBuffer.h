#pragma once

#include "VulkanBufferAllocator.h"

namespace Engine
{
	class VulkanIndexBuffer : protected VulkanBufferAllocator
	{
	public:
		VulkanIndexBuffer(const VkPhysicalDevice& physicalDevice, const VkDevice& logicalDevice, const VkQueue& graphicsQueue, const VkCommandPool& commandPool);
		~VulkanIndexBuffer() = default;

		void createIndexBuffer(const std::vector<uint16_t>& indices);

		VkBuffer getIndexBuffer() const;
		VkDeviceMemory getIndexBufferMemory() const;

	private:
		VkBuffer indexBuffer = nullptr;
		VkDeviceMemory indexBufferMemory = nullptr;
	};
}