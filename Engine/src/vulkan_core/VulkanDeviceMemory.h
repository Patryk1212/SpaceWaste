#pragma once

#include "vulkan/vulkan.h"
#include "vulkan_buffers/VulkanBufferAllocator.h"
#include "renderer/Object.h"

namespace Engine
{
	class VulkanDeviceMemory
	{
	public:
		VulkanDeviceMemory(const std::unique_ptr<VulkanBufferAllocator>& bufferAlloc, const std::vector<std::shared_ptr<Object>>& objects);
		~VulkanDeviceMemory() = default; //proper destroy func needed

		VkDeviceMemory getMemory(int swpachainImage);
		uint64_t getMemoryOffset() const;

	private:
		void bindObjectsUBToMemory(const std::unique_ptr<VulkanBufferAllocator>& bufferAlloc, const std::vector<std::shared_ptr<Object>>& objects);

	private:
		VkMemoryRequirements memRequirements;
		std::vector<VkDeviceMemory> memory;
	};
}