#pragma once

#include "vulkan/vulkan.h"

namespace Engine
{
	class VulkanGraphicsPipeline
	{
	public:
		VulkanGraphicsPipeline();
		~VulkanGraphicsPipeline();

		void createGraphicsPipeline(const VkDevice& logicalDevice, const VkExtent2D& swapChainExtent);

	private:
		VkPipeline graphicsPipeline;
		VkDescriptorSetLayout descriptorSetLayout;
		VkPipelineLayout pipelineLayout;
		VkRenderPass renderPass;
	};
}
