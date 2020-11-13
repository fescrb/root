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

#include <root/graphics/physical_device.h>

#include <root/io/log.h>
#include <root/graphics/surface.h>

namespace root {

namespace graphics {

physical_device::physical_device(const VkPhysicalDevice& h)
:   vk_handle_container(h) {}

auto physical_device::properties() const -> VkPhysicalDeviceProperties {
    VkPhysicalDeviceProperties props;
    vkGetPhysicalDeviceProperties(m_handle, &props);
    return props;
}

auto physical_device::memory_properties()const -> VkPhysicalDeviceMemoryProperties {
    VkPhysicalDeviceMemoryProperties props;
    vkGetPhysicalDeviceMemoryProperties(m_handle, &props);
    return props;
}

auto physical_device::queue_family_properties(allocator* alloc) const -> const array<VkQueueFamilyProperties> {
     u32 num_queues;
    vkGetPhysicalDeviceQueueFamilyProperties(m_handle, &num_queues, nullptr);

    array<VkQueueFamilyProperties> props(num_queues, alloc);
    vkGetPhysicalDeviceQueueFamilyProperties(m_handle, &num_queues, props.data());

    return props;
}

auto physical_device::extensions(allocator* alloc) const -> const array<VkExtensionProperties> {
    u32 num_extensions;
    VkResult res = vkEnumerateDeviceExtensionProperties(m_handle, nullptr, &num_extensions, nullptr);

    if(res != VK_SUCCESS) {
        log::e("physical_device", "vkEnumerateDeviceExtensionProperties failed with {}", res);
        abort();
    }

    array<VkExtensionProperties> extens(num_extensions, alloc);
    res = vkEnumerateDeviceExtensionProperties(m_handle, nullptr, &num_extensions, extens.data());
    
    if(res != VK_SUCCESS) {
        log::e("physical_device", "vkEnumerateDeviceExtensionProperties failed with {}", res);
        abort();
    }

    return extens;
}

auto physical_device::has_graphics_queue() const -> bool {
    return graphics_queue_family_index() != FAMILY_INVALID;
}

auto physical_device::has_present_queue(const strong_ptr<surface>& s) const -> bool {
    return present_queue_family_index(s) != FAMILY_INVALID;
}

auto physical_device::graphics_queue_family_index() const -> u32 {
    auto& fam_props = queue_family_properties();

    for(u32 i = 0; i < fam_props.size(); i++) {
        if(fam_props[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            return i;
        }
    }

    return FAMILY_INVALID;
}

auto physical_device::present_queue_family_index(const strong_ptr<surface>& s) const -> u32 {
    auto& fam_props = queue_family_properties();

    for(u32 i = 0; i < fam_props.size(); i++) {
        if(can_present(s, i)) {
            return i;
        }
    }

    return FAMILY_INVALID;
}

auto physical_device::can_present(const strong_ptr<surface>& s, const u32& family_queue_index) const -> VkBool32 {
    VkBool32 present_support = false;
    vkGetPhysicalDeviceSurfaceSupportKHR(m_handle, family_queue_index, s->handle(), &present_support);
    return present_support;
}

} // namespace graphics

} // namespace root