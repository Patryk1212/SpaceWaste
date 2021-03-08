#pragma once

#include "cube.h"

#include "core/CameraController.h"

#include "vulkan_buffers/VulkanVertexBuffer.h"
#include "vulkan_buffers/VulkanIndexBuffer.h"

namespace Engine
{
	class Renderer3D
	{
	public:
		static void init();
		static void shutDown();


		// start recording command buffers
		// pass objects
		// end recording

		static void beginScene();
		
		static void draw(const CameraController& camera);
		
		static void endScene();


	private:
		

		// command buffers
	};
}