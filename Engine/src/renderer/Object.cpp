#include "pch.h"
#include "Object.h"

namespace Engine
{
	void Object::createUniformBuffer(const std::unique_ptr<VulkanBufferAllocator>& bufferAlloc)
	{
		std::unique_ptr<VulkanUniformBuffer> tempUniformBuffer;
		tempUniformBuffer = std::make_unique<VulkanUniformBuffer>();

		tempUniformBuffer->createUniformBuffer(bufferAlloc, sizeof(UniformBufferObject), 
				VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		uniformBuffer.emplace_back(std::move(tempUniformBuffer));
	}

	VkBuffer Object::getUniformBuffer(int imageNumber) const
	{
		return uniformBuffer[imageNumber]->getUniformBuffer();
	}

	VkDeviceMemory Object::getUniformBufferMemory(int imageNumber) const
	{
		return uniformBuffer[imageNumber]->getUniformBufferMemory();
	}
}
