/*
 * Copyright (C) 2020  Fernando Escribano Macias 
 *
 * This file is part of the Root Engine.
 * 
 * The Root Engine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * The Root Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with The Root Engine.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <root/graphics/swapchain.h>

#include <root/io/log.h>

namespace root {

swapchain::swapchain(const surface& s, const device& d, allocator* alloc)
:   handle(VK_NULL_HANDLE),
    m_alloc(alloc) {
    refresh(s, d);
}

auto swapchain::refresh(const surface& s, const device& d) -> void {
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(d.get_physical_device().handle, s.handle, &surface_capabilities);

    log::d("swapchain","surface_capabilities: {}", surface_capabilities);

    /*
     * Formats
     */

    u32 format_count = 0;
    vkGetPhysicalDeviceSurfaceFormatsKHR(d.get_physical_device().handle, s.handle, &format_count, nullptr);

    if(format_count == 0) {
        log::e("swapchain", "no formats supported");
        abort();
    }

    array<VkSurfaceFormatKHR> temp_formats = array<VkSurfaceFormatKHR>(format_count);
    vkGetPhysicalDeviceSurfaceFormatsKHR(d.get_physical_device().handle, s.handle, &format_count, temp_formats.data());

    for(int i = 0; i < temp_formats.size(); i++) {
        log::d("swapchain", "format {}: {}", i, temp_formats[i]);
    }

    formats = std::move(temp_formats);

    /*
     * Present modes
     */

    uint32_t present_mode_count;
    vkGetPhysicalDeviceSurfacePresentModesKHR(d.get_physical_device().handle, s.handle, &present_mode_count, nullptr);


    if(present_mode_count == 0) {
        log::e("swapchain", "no present modes supported");
        abort();
    }

    array<VkPresentModeKHR> temp_modes = array<VkPresentModeKHR>(present_mode_count);
    vkGetPhysicalDeviceSurfacePresentModesKHR(d.get_physical_device().handle, s.handle, &present_mode_count, temp_modes.data());

    for(int i = 0; i < temp_modes.size(); i++) {
        log::d("swapchain", "present mode {}: {}", i, temp_modes[i]);
    }

    present_modes = std::move(temp_modes);

    /*
     * Choose extent
     */
    // TODO: we can do this better?
    VkExtent2D chosen_extent = surface_capabilities.maxImageExtent; 

    /*
     * Choose format
     */
    // TODO
    VkSurfaceFormatKHR surface_format = formats[0];

    /*
     * Create swapchain
     */

    VkSwapchainCreateInfoKHR create_info;
    create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    create_info.surface = s.handle;
    create_info.minImageCount = surface_capabilities.minImageCount;
    create_info.imageFormat = surface_format.format;
    create_info.imageColorSpace = surface_format.colorSpace;
    create_info.imageExtent = chosen_extent;
    create_info.imageArrayLayers = 1;
    create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE; // TODO handle sharing
    create_info.queueFamilyIndexCount = 0; 
    create_info.pQueueFamilyIndices = nullptr;
    create_info.preTransform = surface_capabilities.currentTransform; 
    create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    create_info.presentMode = VK_PRESENT_MODE_FIFO_KHR; // This mode is required to be supported
    create_info.clipped = VK_TRUE; // Don't care covered pixels
    create_info.oldSwapchain = handle;

    VkResult res = vkCreateSwapchainKHR(d.handle, &create_info, nullptr, &handle);

    if(res != VK_SUCCESS) {
        log::e("swapchain", "vkCreateSwapchainKHR failed with {}", res);
        abort();
    }
}

} // namespace root