#include "pch.h"
#include "VulkanDeviceMemory.h"

namespace Engine
{
	VulkanDeviceMemory::VulkanDeviceMemory(const std::unique_ptr<VulkanBufferAllocator>& bufferAlloc, const std::vector<std::unique_ptr<Object>>& objects)
	{
		VkDeviceMemory tempBufferMemory1 = nullptr;
		VkDeviceMemory tempBufferMemory2 = nullptr;
		VkDeviceMemory tempBufferMemory3 = nullptr;

		vkGetBufferMemoryRequirements(bufferAlloc->getLogicalDeviceHandle(), objects[0]->getUniformBuffer(0), &memRequirements);

		VkMemoryAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize = memRequirements.size * objects.size();
		allocInfo.memoryTypeIndex = bufferAlloc->findMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		if (vkAllocateMemory(bufferAlloc->getLogicalDeviceHandle(), &allocInfo, nullptr, &tempBufferMemory1) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to allocate 1st buffer memory!");
		}
		memory.emplace_back(tempBufferMemory1);

		if (vkAllocateMemory(bufferAlloc->getLogicalDeviceHandle(), &allocInfo, nullptr, &tempBufferMemory2) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to allocate 2nd buffer memory!");
		}
		memory.emplace_back(tempBufferMemory2);

		if (vkAllocateMemory(bufferAlloc->getLogicalDeviceHandle(), &allocInfo, nullptr, &tempBufferMemory3) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to allocate 3rd buffer memory!");
		}
		memory.emplace_back(tempBufferMemory3);

		bindObjectsUBToMemory(bufferAlloc, objects);
	}

	VkDeviceMemory VulkanDeviceMemory::getMemory(int swpachainImage)
	{
		return memory[swpachainImage];
	}

	uint64_t VulkanDeviceMemory::getMemoryOffset() const
	{
		return memRequirements.alignment;
	}

	void VulkanDeviceMemory::bindObjectsUBToMemory(const std::unique_ptr<VulkanBufferAllocator>& bufferAlloc, const std::vector<std::unique_ptr<Object>>& objects)
	{
		uint64_t offset = 0;
		for (size_t i = 0; i < 3; i++) // swapChainData.swapChainImages.size() instead of 3
		{
			for (const auto& cube : objects)
			{
				cube->bindUBO(i, bufferAlloc, memory[i], offset);
				offset += memRequirements.alignment;
			}

			offset = 0;
		}
	}
}