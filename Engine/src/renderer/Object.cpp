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

	void Object::bindUBO(int swapchainImage, const std::unique_ptr<VulkanBufferAllocator>& bufferAlloc, VkDeviceMemory uniformBM, uint64_t offset)
	{
		uniformBuffer[swapchainImage]->bindUBToBufferMemory(bufferAlloc, uniformBM, offset);
	}

	VkBuffer Object::getUniformBuffer(int imageNumber) const
	{
		return uniformBuffer[imageNumber]->getUniformBuffer();
	}

	UniformBufferObject& Object::getUniformbufferObject()
	{
		return ubo;
	}
	
	VkDescriptorSet& Object::getDescriptorSet()
	{
		return descriptorSet;
	}
}
