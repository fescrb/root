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

namespace graphics {

swapchain::swapchain(const strong_ptr<surface>& s, const strong_ptr<device>& d, allocator* alloc)
:   vk_handle_container(),
    device::dependent(d),
    m_surface(s),
    m_callbacks(alloc),
    m_alloc(alloc) {
    root_assert(s && d && alloc);
    /*
     * Formats
     */

    u32 format_count = 0;
    vkGetPhysicalDeviceSurfaceFormatsKHR(m_device->get_physical_device().handle(), m_surface->handle(), &format_count, nullptr);

    if(format_count == 0) {
        log::e("swapchain", "no formats supported");
        abort();
    }

    array<VkSurfaceFormatKHR> temp_formats = array<VkSurfaceFormatKHR>(format_count);
    vkGetPhysicalDeviceSurfaceFormatsKHR(m_device->get_physical_device().handle(), m_surface->handle(), &format_count, temp_formats.data());

    for(int i = 0; i < temp_formats.size(); i++) {
        log::d("swapchain", "format {}: {}", i, temp_formats[i]);
    }

    m_available_formats = std::move(temp_formats);

    /*
     * Present modes
     */

    uint32_t present_mode_count;
    vkGetPhysicalDeviceSurfacePresentModesKHR(m_device->get_physical_device().handle(), m_surface->handle(), &present_mode_count, nullptr);


    if(present_mode_count == 0) {
        log::e("swapchain", "no present modes supported");
        abort();
    }

    array<VkPresentModeKHR> temp_modes = array<VkPresentModeKHR>(present_mode_count);
    vkGetPhysicalDeviceSurfacePresentModesKHR(m_device->get_physical_device().handle(), m_surface->handle(), &present_mode_count, temp_modes.data());

    for(int i = 0; i < temp_modes.size(); i++) {
        log::d("swapchain", "present mode {}: {}", i, temp_modes[i]);
    }

    m_vailable_present_modes = std::move(temp_modes);

    /*
     * Choose format
     */
    // TODO
    m_surface_format = m_available_formats[0];

    refresh();
}

swapchain::~swapchain() {
    if (*this) {
        vkDestroySwapchainKHR(m_device->handle(), m_handle, m_callbacks);
    }
}

auto swapchain::refresh() -> void {
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_device->get_physical_device().handle(), m_surface->handle(), &m_surface_capabilities);

    log::d("swapchain","surface_capabilities: {}", m_surface_capabilities);

    /*
     * Choose extent
     */
    // TODO: we can do this better?
    m_extent = m_surface_capabilities.maxImageExtent; 

    /*
     * Create swapchain
     */

    VkSwapchainCreateInfoKHR create_info;
    create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    create_info.pNext = nullptr;
    create_info.flags = 0;
    create_info.surface = m_surface->handle();
    create_info.minImageCount = m_surface_capabilities.minImageCount + 1;
    create_info.imageFormat = m_surface_format.format;
    create_info.imageColorSpace = m_surface_format.colorSpace;
    create_info.imageExtent = m_extent;
    create_info.imageArrayLayers = 1;
    create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE; // TODO handle sharing
    create_info.queueFamilyIndexCount = 0; 
    create_info.pQueueFamilyIndices = nullptr;
    create_info.preTransform = m_surface_capabilities.currentTransform; 
    create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    create_info.presentMode = VK_PRESENT_MODE_FIFO_KHR; // This mode is required to be supported
    create_info.clipped = VK_TRUE; // Don't care covered pixels
    create_info.oldSwapchain = m_handle;

    VkResult res = vkCreateSwapchainKHR(m_device->handle(), &create_info, m_callbacks, &m_handle);

    if(res != VK_SUCCESS) {
        log::e("swapchain", "vkCreateSwapchainKHR failed with {}", res);
        abort();
    }

    u32 num_images;
    vkGetSwapchainImagesKHR(m_device->handle(), handle(), &num_images, nullptr);
    array<VkImage> temp_images(num_images, m_alloc);
    vkGetSwapchainImagesKHR(m_device->handle(), handle(), &num_images, temp_images.data());
    
    array<VkImageView> temp_image_views(num_images, m_alloc);
    
    for(int i = 0; i < num_images; i++) {
        VkImageViewCreateInfo view_create_info;
        view_create_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        view_create_info.pNext = nullptr;
        view_create_info.flags = 0;
        view_create_info.image = temp_images[i];
        view_create_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
        view_create_info.format = m_surface_format.format;
        VkComponentMapping components;
        components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        view_create_info.components = components;
        VkImageSubresourceRange subresource_range;
        subresource_range.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        subresource_range.baseMipLevel = 0;
        subresource_range.levelCount = 1;
        subresource_range.baseArrayLayer = 0;
        subresource_range.layerCount = 1;
        view_create_info.subresourceRange = subresource_range;

        res = vkCreateImageView(m_device->handle(), &view_create_info, m_callbacks, &(temp_image_views[i]));

        if (res != VK_SUCCESS) {
            log::e("swapchain", "vkCreateImageView failed with {}", res);
        }
    }

    swapchain_images = std::move(temp_image_views);
}

auto swapchain::acquire(const semaphore& sem, const u64 timeout) -> u32 {
    u32 image_index;
    // TODO: deal with fences
    VkResult res = vkAcquireNextImageKHR(m_device->handle(), handle(), timeout, sem.handle(), VK_NULL_HANDLE, &image_index);
    // TODO: deal with out of date swapchain
    if(res != VK_SUCCESS) {
        log::e("swapchain", "vkAcquireNextImageKHR failed with {}", res);
        abort();
    }
    return image_index;
}

auto swapchain::present(const array_slice<semaphore>& wait_semaphores, const u32 image_index) -> void {
    VkPresentInfoKHR present_info;
    present_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    present_info.pNext = nullptr;
    present_info.waitSemaphoreCount = wait_semaphores.size();
    array<VkSemaphore> semaphores;
    if(wait_semaphores.size()) {
        semaphores = std::move(array<VkSemaphore>(wait_semaphores.size(), m_alloc));
        for(u32 i = 0; i < wait_semaphores.size(); i++) {
            semaphores[i] = wait_semaphores[i].handle();
        }
        present_info.pWaitSemaphores = semaphores.data();
    } else {
        present_info.pWaitSemaphores = nullptr;
    }
    present_info.swapchainCount = 1;
    present_info.pSwapchains = &m_handle;
    present_info.pImageIndices = &image_index;
    present_info.pResults = nullptr;

    VkResult res = vkQueuePresentKHR(m_device->get_present_queue(), &present_info);
    // TODO: deal with out of date swapchain
    if(res != VK_SUCCESS) {
        log::e("swapchain", "vkAcquireNextImageKHR failed with {}", res);
        abort();
    }
}

} // namespace graphics

} // namespace root