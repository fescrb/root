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

#include <root/io/log.h>

#include <limits>

namespace root {

device::device(const physical_device& d, const surface& s)
:   handle(VK_NULL_HANDLE),
    m_graphics_family_index(d.graphics_queue_family_index()),
    m_physical_device(d) {
    auto& fam_props = d.queue_family_properties();

    root_assert(m_graphics_family_index != physical_device::FAMILY_INVALID);

    if(d.graphics_queue_family_index() != d.present_queue_family_index(s)) {
        log::e("device", "graphics family differs from present family, we do not handle this currently");
        abort();
    }

    // TODO: handle the graphics queue and the present queue being different

    VkDeviceQueueCreateInfo queue_create;
    queue_create.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_create.pNext = nullptr;
    queue_create.flags = 0;
    queue_create.queueFamilyIndex = m_graphics_family_index;
    queue_create.queueCount = 1;
    float priority = 1.0f;
    queue_create.pQueuePriorities = &priority;

    const char* device_extensions[] = {
        "VK_KHR_swapchain"
    };

    VkDeviceCreateInfo device_create;
    device_create.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    device_create.pNext = nullptr;
    device_create.flags = 0;
    device_create.queueCreateInfoCount = 1;
    device_create.pQueueCreateInfos = &queue_create;
    device_create.enabledLayerCount = 0;
    device_create.ppEnabledLayerNames = nullptr;
    device_create.enabledExtensionCount = 1; 
    device_create.ppEnabledExtensionNames = device_extensions;
    device_create.pEnabledFeatures = nullptr; // TODO?

    VkResult res = vkCreateDevice(d.handle, &device_create, nullptr, &handle);

    if(res != VK_SUCCESS) {
        log::e("device", "vkCreateDevice failed with {}", res);
    }
}

auto device::get_graphics_queue() const -> VkQueue {
    VkQueue ret;
    vkGetDeviceQueue(handle, m_graphics_family_index, 0, &ret);
    return ret;
}

} // namespace root