#pragma once

#include "Graphics.h"
#include "Object.h"
#include "core/CameraController.h"

namespace Engine
{
	class Renderer3D
	{
	public:
		static void init(const std::shared_ptr<Window>& window, const VkPhysicalDevice& physicalDevice, const VkDevice& logicalDevice, const VkQueue& graphicsQueue, const VkQueue& presentQueue);
		static void shutDown();

	public:
		static void beginFrame();

		static void recordCommandBuffers(const std::vector<std::unique_ptr<Object>>& objects);

		static void updateFrame(float deltaTime, const std::unique_ptr<Camera>& camera);
		static void updateFrame(const std::vector<std::unique_ptr<Object>>& objects, const std::unique_ptr<Camera>& camera);

		static void endFrame();

	private:
		inline static Graphics* graphics;
	};
}