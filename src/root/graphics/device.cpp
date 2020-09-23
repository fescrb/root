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

#include <root/core/assert.h>

#include <root/graphics/device.h>

#include <limits>

namespace root {

device::device(physical_device& d) {
    auto& fam_props = d.queue_family_properties();

    constexpr uint32_t FAMILY_INVALID = std::numeric_limits<uint32_t>::max();
    uint32_t m_graphics_family_index = FAMILY_INVALID;

    for(uint32_t i = 0; i < fam_props.size(); i++) {
        if(fam_props.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            m_graphics_family_index = i; 
            break;
        }
    }

    root_assert(m_graphics_family_index != FAMILY_INVALID);

    VkDeviceQueueCreateInfo queue_create;
    queue_create.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_create.pNext = nullptr;
    queue_create.flags = 0;
    queue_create.queueFamilyIndex = m_graphics_family_index;
    queue_create.queueCount = 1;
    float priority = 1.0f;
    queue_create.pQueuePriorities = &priority;

    VkDeviceCreateInfo device_create;
    device_create.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    device_create.pNext = nullptr;
    device_create.flags = 0;
    device_create.queueCreateInfoCount = 1;
    device_create.pQueueCreateInfos = &queue_create;
    device_create.enabledLayerCount = 0;
    device_create.ppEnabledLayerNames = nullptr;
    device_create.enabledExtensionCount = 0; // Must change to swapchain extensions
    device_create.ppEnabledExtensionNames = nullptr;
    device_create.pEnabledFeatures = nullptr; // TODO?

    if(vkCreateDevice(d.handle, &device_create, nullptr, &handle) != VK_SUCCESS) {
        // TODO: handle error
    }
}

auto device::get_graphics_queue() const -> VkQueue {
    VkQueue ret;
    vkGetDeviceQueue(handle, m_graphics_family_index, 0, &ret);
    return ret;
}

} // namespace root