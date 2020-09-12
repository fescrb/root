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

#include <root/graphics/instance.h>

namespace root {


instance* instance::m_instance = nullptr;

auto instance::init() -> void {
    VkInstanceCreateInfo create_info;
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.pNext = nullptr;
    create_info.flags = 0;
    create_info.pApplicationInfo = nullptr; // TODO
    create_info.enabledLayerCount = 0;
    create_info.ppEnabledLayerNames = nullptr;
    create_info.enabledExtensionCount = 0;
    create_info.ppEnabledExtensionNames = nullptr;

    VkInstance handle;
    if (vkCreateInstance(&create_info, nullptr, &handle) != VK_SUCCESS) {
        // TODO: handle error
    }
    m_instance = new instance(handle); // TODO: perhaps provide allocator?
}

auto instance::physical_devices(allocator* alloc) const -> array<physical_device> {
    u32 num;
    if (vkEnumeratePhysicalDevices(handle, &num, nullptr) != VK_SUCCESS) {
        // TODO: handle error
    }
    
    VkPhysicalDevice phys_devices[num];
    
    if (vkEnumeratePhysicalDevices(handle, &num, phys_devices) != VK_SUCCESS) {
        // TODO: handle error
    }

    array<physical_device> devices(num, alloc);

    for(int i = 0; i < num; i++) {
        devices[i] = physical_device(phys_devices[i]);
    }

    return devices;
}

} // namespace root