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

class swapchain : public vk_handle_container<VkSwapchainKHR,swapchain>, public device::dependent{
public:
    swapchain(const strong_ptr<device>& d, const strong_ptr<surface>& s, allocator* alloc = allocator::get_default());
    ~swapchain();

    auto refresh() -> void;

    inline auto viewport() const -> VkViewport {
        VkViewport vp;
        vp.x = 0.0f, vp.y = 0.0f;
        vp.width = static_cast<f32>(m_extent.width), vp.height = static_cast<f32>(m_extent.height);
        vp.minDepth = 0.0f, vp.maxDepth = 1.0f;
        return vp;
    }

    inline auto scissor() const -> VkRect2D {
        VkRect2D sc;
        sc.offset = {0, 0};
        sc.extent = m_extent;
        return sc;
    }

    inline auto extent() const -> VkExtent2D {
        return m_extent;
    }

    inline auto surface_format() const -> VkSurfaceFormatKHR {
        return m_surface_format;
    }

    inline static auto get_default() -> strong_ptr<swapchain>& {
        return m_default_swapchain;
    }

    inline static auto set_default(const strong_ptr<swapchain>& sw) -> void {
        m_default_swapchain = sw;
    }

    inline auto get_images() const -> const array<VkImageView>& {
        return m_swapchain_images;
    }

    // TODO change the timeout if a time data type is made
    auto acquire(const semaphore& sem, const u64 timeout = UINT64_MAX) -> u32;

    auto present(const array_slice<semaphore>& wait_semaphores, const u32 image_index) -> void;

    class observer {
    public:
        virtual auto on_swapchain_refreshed(const strong_ptr<swapchain>&) -> void = 0;
    };

private:
    strong_ptr<surface> m_surface;
    VkSurfaceFormatKHR m_surface_format;
    vk_allocation_callbacks m_callbacks;
    VkPresentModeKHR m_present_mode;
    VkExtent2D m_extent;
    VkSurfaceCapabilitiesKHR m_surface_capabilities;
    array<VkSurfaceFormatKHR> m_available_formats;
    array<VkPresentModeKHR> m_vailable_present_modes;
    array<VkImageView> m_swapchain_images;
    allocator* m_alloc;

    static strong_ptr<swapchain> m_default_swapchain;
};

} // namespace graphics

} // namespace root