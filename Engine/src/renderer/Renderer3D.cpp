#include "pch.h"
#include "Renderer3D.h"
#include "vulkan_core/VulkanSurface.h"
#include "vulkan_core/VulkanData.h"

namespace Engine
{
	void Renderer3D::init(const std::shared_ptr<Window>& window, const VkPhysicalDevice& physicalDevice, const VkDevice& logicalDevice, const VkQueue& graphicsQueue, const VkQueue& presentQueue)
	{
		/* */
		int stacks = 20;
		int slices = 20;
		const float PI = 3.14f;

		// calculate vertices
		Vertex positions;
		std::vector<Vertex> vert;

		// loop through stacks.
		for (int i = 0; i <= stacks; ++i)
		{
			float V = (float)i / (float)stacks;
			float phi = V * PI;

			// loop through the slices.
			for (int j = 0; j <= slices; ++j)
			{
				float U = (float)j / (float)slices;
				float theta = U * (PI * 2);

				// use spherical coordinates to calculate the positions.
				float x = cos(theta) * sin(phi);
				float y = cos(phi);
				float z = sin(theta) * sin(phi);

				positions.pos.x = x;
				positions.pos.y = y;
				positions.pos.z = z;

				vert.push_back(positions);
			}
		}

		// calculate indices
		std::vector<uint16_t> indices;
		for (int i = 0; i < slices * stacks + slices; ++i)
		{
			indices.push_back(uint16_t(i));
			indices.push_back(uint16_t(i + slices + 1));
			indices.push_back(uint16_t(i + slices));

			indices.push_back(uint16_t(i + slices + 1));
			indices.push_back(uint16_t(i));
			indices.push_back(uint16_t(i + 1));
		}

		/* */

		graphics = new Graphics(window, physicalDevice, logicalDevice, graphicsQueue, presentQueue, indices, vert);
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

	void Renderer3D::recordCommandBuffers(const std::vector<std::shared_ptr<Object>>& objects)
	{
		graphics->createObjectsAndRecord(objects);
	}

	void Renderer3D::updateFrame(const std::vector<std::shared_ptr<Object>>& objects)
	{
		graphics->updateUniformBuffer(objects);
	}

	void Renderer3D::endFrame()
	{
		graphics->endFrame();
	}
}