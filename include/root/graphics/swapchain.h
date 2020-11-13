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

#pragma once

#include <vulkan/vulkan.h>

#include <root/graphics/vk_handle_container.h>

#include <root/graphics/device.h>
#include <root/graphics/surface.h>
#include <root/graphics/semaphore.h>

namespace root {

namespace graphics {

class swapchain : public vk_handle_container<VkSwapchainKHR,swapchain> {
public:
    swapchain(const surface& s, const device& d, allocator* alloc = allocator::get_default());

    auto refresh(const surface& s, const device& d) -> void;

    inline auto viewport() const -> VkViewport {
        VkViewport vp;
        vp.x = 0.0f, vp.y = 0.0f;
        vp.width = static_cast<f32>(extent.width), vp.height = static_cast<f32>(extent.height);
        vp.minDepth = 0.0f, vp.maxDepth = 1.0f;
        return vp;
    }

    inline auto scissor() const -> VkRect2D {
        VkRect2D sc;
        sc.offset = {0, 0};
        sc.extent = extent;
        return sc;
    }

    // TODO change the timeout if a time data type is made
    auto acquire(const semaphore& sem, const u64 timeout = UINT64_MAX) -> u32;

    auto present(const array_slice<semaphore>& wait_semaphores, const u32 image_index) -> void;

    VkSurfaceCapabilitiesKHR surface_capabilities;
    array<VkSurfaceFormatKHR> formats;
    array<VkPresentModeKHR> present_modes;
    VkFormat format;
    VkExtent2D extent;
    array<VkImageView> swapchain_images; // TODO: Maybe function access?

private:
    const device& m_device;
    allocator* m_alloc;
};

} // namespace graphics

} // namespace root