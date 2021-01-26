#pragma once

#include "vulkan/vulkan.h"
#include "vulkan/VulkanUtility.h"

namespace Engine
{
	class VulkanBufferAllocator
	{
	public:
		VulkanBufferAllocator(const VkPhysicalDevice& physicalDevice, const VkDevice& logicalDevice, const VkQueue& graphicsQueue, const VkCommandPool& commandPool);
		~VulkanBufferAllocator() = default;

		void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
		uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
		void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

		VkDevice getLogicalDeviceHandle() const;

	private:
		VkPhysicalDevice physicalDeviceHandle;
		VkDevice logicalDeviceHandle;
		VkQueue graphicsQueueHandle;
		VkCommandPool commandPoolHandle;
	};
}