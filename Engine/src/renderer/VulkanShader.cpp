#include "pch.h"
#include "VulkanShader.h"

namespace Engine
{
	VulkanShader::VulkanShader(const VkDevice& logicalDevice, const std::string& path, const std::string& type)
	{
		auto shaderCode = readFile(path);

		shaderModule = createShaderModule(logicalDevice, shaderCode);

		shaderInfo = {};
		shaderInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;

		if (type == "fragment")
		{
			shaderInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		}
		else if (type == "vertex")
		{
			shaderInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
		}
		else
		{
			throw std::runtime_error("wrong shader type specified!");
		}

		shaderInfo.module = shaderModule;
		shaderInfo.pName = "main";
	}

	void VulkanShader::destroy(const VkDevice& logicalDevice)
	{
		vkDestroyShaderModule(logicalDevice, shaderModule, nullptr);
	}

	VkPipelineShaderStageCreateInfo VulkanShader::getShaderInfo()
	{
		return shaderInfo;
	}

	std::vector<char> VulkanShader::readFile(const std::string& filename)
	{
		std::ifstream file(filename, std::ios::ate | std::ios::binary);

		if (!file.is_open())
		{
			throw std::runtime_error("failed to open file!");
		}

		size_t fileSize = (size_t)file.tellg();
		std::vector<char> buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize);

		file.close();

		return buffer;
	}

	VkShaderModule VulkanShader::createShaderModule(const VkDevice& logicalDevice, const std::vector<char>& code)
	{
		VkShaderModuleCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = code.size();
		createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

		VkShaderModule shaderModule;
		if (vkCreateShaderModule(logicalDevice, &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create shader module!");
		}

		return shaderModule;
	}
}