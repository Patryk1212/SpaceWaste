#pragma once

#include "vulkan/vulkan.h"
#include "vulkan_core/SwapChain.h"
#include "vulkan_buffers/VulkanBufferAllocator.h"

namespace Engine
{
	class VulkanDepthImage
	{
	public:
		VulkanDepthImage(const std::unique_ptr<VulkanBufferAllocator>& bufferAlloc, const VkDevice& logicalDevice, const VkPhysicalDevice& physicalDevice, const SwapChainData& swapChainData);
		~VulkanDepthImage() = default;

		void createDepthResources(const std::unique_ptr<VulkanBufferAllocator>& bufferAlloc, const SwapChainData& swapChainData);
		VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
		VkFormat findDepthFormat();
		bool hasStencilComponent(VkFormat format);

		void createImage(const std::unique_ptr<VulkanBufferAllocator>& bufferAlloc, uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
		VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);

		VkImageView getDepthImageView() const;

	private:
		VkPhysicalDevice physicalDeviceHandle;
		VkDevice logicalDeviceHandle;

	private:
		VkImage depthImage;
		VkDeviceMemory depthImageMemory;
		VkImageView depthImageView;
	};
}