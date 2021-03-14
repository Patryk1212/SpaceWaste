#include "pch.h"
#include "Renderer3D.h"
#include "vulkan_core/VulkanSurface.h"
#include "vulkan_core/VulkanData.h"

namespace Engine
{
	void Renderer3D::init(const std::shared_ptr<Window>& window, const VkPhysicalDevice& physicalDevice, const VkDevice& logicalDevice, const VkQueue& graphicsQueue, const VkQueue& presentQueue)
	{
		graphics = new Graphics(window, physicalDevice, logicalDevice, graphicsQueue, presentQueue);
	}

	void Renderer3D::shutDown()
	{
		graphics->onShutDown();
		delete graphics;
	}

	void Renderer3D::beginFrame()
	{
		graphics->startFrame();
	}

	void Renderer3D::recordCommandBuffers(const std::vector<std::unique_ptr<Object>>& objects)
	{
		graphics->createObjectsAndRecord(objects);
	}

	void Renderer3D::updateFrame(float deltaTime, const std::unique_ptr<Camera>& camera)
	{
		graphics->updateFrame(deltaTime, camera);
	}

	void Renderer3D::updateFrame(const std::vector<std::unique_ptr<Object>>& objects)
	{
		graphics->updateUniformBuffer(objects);
	}

	void Renderer3D::endFrame()
	{
		graphics->endFrame();
	}
}