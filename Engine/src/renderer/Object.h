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

		virtual void onUpdate(float deltaTime, int visSpeed_) {}
		virtual std::string showName() const { return "Base Object"; }
		virtual std::string showFirstTLELine() const { return "Base Object"; }
		virtual std::string showSecondTLELine() const { return "Base Object"; }

		virtual inline glm::vec3 getPos() const { return glm::vec3(1.0f); }
		virtual inline glm::vec3 getScale() const { return glm::vec3(1.0f); }
		virtual inline glm::vec3 getColor() const { return glm::vec3(1.0f); }

		virtual inline void setPos(const glm::vec3& pos_) {}
		virtual inline void setScale(const glm::vec3& scale_) {}
		virtual inline void resize(float scalar) {}
		virtual inline void setColor(const glm::vec3& color_) {}

		virtual bool checkInside(const glm::vec3& point) { return false; }

	public:
		void createUniformBuffer(const std::unique_ptr<VulkanBufferAllocator>& bufferAlloc);
		void bindUBO(int swapchainImage, const std::unique_ptr<VulkanBufferAllocator>& bufferAlloc, VkDeviceMemory uniformBM, uint64_t offset);

		VkBuffer getUniformBuffer(int imageNumber) const;
		UniformBufferObject& getUniformbufferObject();
		VkDescriptorSet& getDescriptorSet();

	private:
		UniformBufferObject ubo;
		VkDescriptorSet descriptorSet = VK_NULL_HANDLE;
		std::vector<std::unique_ptr<VulkanUniformBuffer>> uniformBuffer;
	};

	const std::vector<Vertex> vertices =
	{
			{{-1.0f, -1.0f, -1.0f}},
			{{ 1.0f, -1.0f, -1.0f}},
			{{-1.0f,  1.0f, -1.0f}},
			{{ 1.0f,  1.0f, -1.0f}},

			{{-1.0f, -1.0f,  1.0f}},
			{{ 1.0f, -1.0f,  1.0f}},
			{{-1.0f,  1.0f,  1.0f}},
			{{ 1.0f,  1.0f,  1.0f}},

			{{-1.0f, -1.0f, -1.0f}},
			{{ 1.0f, -1.0f, -1.0f}},
			{{-1.0f, -1.0f, -1.0f}},
			{{-1.0f, -1.0f,  1.0f}},

			{{ 1.0f, -1.0f, -1.0f}},
			{{ 1.0f, -1.0f,  1.0f}}
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
