#pragma once

#include "vulkan/vulkan.h"

namespace Engine
{
	class VulkanShader
	{
	public:
		VulkanShader(const VkDevice& logicalDevice, const std::string& path, const std::string& type);
		~VulkanShader() = default;

		void destroy(const VkDevice& logicalDevice);
		VkPipelineShaderStageCreateInfo getShaderInfo();

	private:
		VkShaderModule shaderModule;
		VkPipelineShaderStageCreateInfo shaderInfo;

	private:
		std::vector<char> readFile(const std::string& filename);
		VkShaderModule createShaderModule(const VkDevice& logicalDevice, const std::vector<char>& code);
	};
}