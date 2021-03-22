#pragma once

#include "vulkan_core/VulkanUtility.h"

#include "vulkan_buffers/VulkanUniformBuffer.h"
#include "vulkan_buffers/VulkanVertexBuffer.h"
#include "vulkan_buffers/VulkanIndexBuffer.h"

namespace Engine
{
	class Object
	{
	public:
		Object() = default;
		~Object() = default;

		inline void setPosition(const glm::vec3& pos) { position = pos; position /= 10;}
		inline void setScale(const glm::vec3& scale_) { scale = scale_; }

		virtual std::string showName() const { return "Base Object"; }
		virtual std::string showFirstTLELine() const { return "Base Object"; }
		virtual std::string showSecondTLELine() const { return "Base Object"; }

	public:
		void createUniformBuffer(const std::unique_ptr<VulkanBufferAllocator>& bufferAlloc);
		void bindUBO(int swapchainImage, const std::unique_ptr<VulkanBufferAllocator>& bufferAlloc, VkDeviceMemory uniformBM, uint64_t offset);

		VkBuffer getUniformBuffer(int imageNumber) const;
		VkDeviceMemory getUniformBufferMemory(int imageNumber) const;

	public: // private
		glm::vec3 scale = { 5.0f, 5.0f, 5.0f };
		glm::vec3 position = { 0.0f, 0.0f, 0.0f };
		float rotation = 0.0f;

	public: // private
		UniformBufferObject ubo;
		VkDescriptorSet descriptorSet;

	private:
		std::vector<std::unique_ptr<VulkanUniformBuffer>> uniformBuffer;
	};

	const std::vector<Vertex> vertices =
	{
			{{-1.0f, -1.0f, -1.0f}, {0.6f, 0.75f, 0.9f}},
			{{ 1.0f, -1.0f, -1.0f}, {0.13f, 0.3f, 0.4f}},
			{{-1.0f,  1.0f, -1.0f}, {0.6f, 0.75f, 0.9f}},
			{{ 1.0f,  1.0f, -1.0f}, {0.13f, 0.3f, 0.4f}},

			{{-1.0f, -1.0f,  1.0f}, {1.13f, 0.3f, 0.4f}},
			{{ 1.0f, -1.0f,  1.0f}, {1.6f, 0.75f, 0.9f}},
			{{-1.0f,  1.0f,  1.0f}, {1.13f, 0.3f, 0.4f}},
			{{ 1.0f,  1.0f,  1.0f}, {1.6f, 0.75f, 0.9f}},

			{{-1.0f, -1.0f, -1.0f}, {1.f, 1.f, 0.4f}},
			{{ 1.0f, -1.0f, -1.0f}, {1.f, 1.f, 0.9f}},
			{{-1.0f, -1.0f, -1.0f}, {1.f, 1.f, 0.4f}},
			{{-1.0f, -1.0f,  1.0f}, {1.f, 1.f, 0.9f}},

			{{ 1.0f, -1.0f, -1.0f}, {0.13f, 0.3f, 0.4f}},
			{{ 1.0f, -1.0f,  1.0f}, {0.6f, 0.75f, 0.9f}}
	};

	const std::vector<Vertex> vertices1 =
	{
			{{-1.0f, -1.0f, -1.0f}, {0.3f, 0.5f, 0.1f}},
			{{ 1.0f, -1.0f, -1.0f}, {0.16f, 0.36f, 0.58f}},
			{{-1.0f,  1.0f, -1.0f}, {0.3f, 0.5f, 0.1f}},
			{{ 1.0f,  1.0f, -1.0f}, {0.16f, 0.36f, 0.58f}},

			{{-1.0f, -1.0f,  1.0f}, {0.3f, 0.5f, 0.1f}},
			{{ 1.0f, -1.0f,  1.0f}, {0.16f, 0.36f, 0.58f}},
			{{-1.0f,  1.0f,  1.0f}, {0.3f, 0.5f, 0.1f}},
			{{ 1.0f,  1.0f,  1.0f}, {0.16f, 0.36f, 0.58f}},

			{{-1.0f, -1.0f, -1.0f}, {0.3f, 0.5f, 0.1f}},
			{{ 1.0f, -1.0f, -1.0f}, {0.16f, 0.36f, 0.58f}},
			{{-1.0f, -1.0f, -1.0f}, {0.3f, 0.5f, 0.1f}},
			{{-1.0f, -1.0f,  1.0f}, {0.16f, 0.36f, 0.58f}},

			{{ 1.0f, -1.0f, -1.0f}, {0.16f, 0.36f, 0.58f}},
			{{ 1.0f, -1.0f,  1.0f}, {0.3f, 0.5f, 0.1f}}
	};

	const std::vector<uint16_t> indices =
	{
		0,2,1,   2,3,1,
		4,8,5,   5,8,9,
		2,6,3,   3,6,7,
		4,5,7,   4,7,6,
		2,10,11, 2,11,6,
		12,3,7,  12,7,13
	};
}
