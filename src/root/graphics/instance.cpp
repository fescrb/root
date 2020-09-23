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

#if defined(ROOT_LINUX)
#include <GLFW/glfw3.h>
#endif

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

#if defined(ROOT_LINUX)
    // TODO where do I put this?
    if(!glfwInit()) {
        // TODO: handle error
    }

    // TODO only on desktop builds
    uint32_t glfw_ext_count;
    auto glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_ext_count);

    create_info.enabledExtensionCount = glfw_ext_count;
    create_info.ppEnabledExtensionNames = glfw_extensions;
#else
    create_info.enabledExtensionCount = 0;
    create_info.ppEnabledExtensionNames = nullptr;
#endif

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
        devices[i] = std::move(physical_device(phys_devices[i]));
    }

    return devices;
}

} // namespace root