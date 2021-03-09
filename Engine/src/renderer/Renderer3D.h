#pragma once

#include "cube.h"

#include "core/CameraController.h"

#include "vulkan_buffers/VulkanVertexBuffer.h"
#include "vulkan_buffers/VulkanIndexBuffer.h"
#include "vulkan_core/VulkanSwapChain.h"

namespace Engine
{
	class Renderer3D
	{
	public:
		static void init(const std::shared_ptr<Window>& window, const VkPhysicalDevice& physicalDevice, const VkDevice& logicalDevice, const VkQueue& graphicsQueue, const VkQueue& presentQueue);
		static void shutDown();



		static void beginFrame();
		static void updateFrame(float deltaTime, const std::unique_ptr<Camera>& camera);
		static void endFrame();



	private:
		inline static VulkanSwapChain* swapchain;

		// command buffers
	};
}