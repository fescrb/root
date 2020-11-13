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

#if !defined(ROOT_ANDROID)
#if defined(ROOT_WIN)
//#include <windows.h>
#endif 
#include <GLFW/glfw3.h>
#endif

#include <root/graphics/instance.h>

#include <root/io/log.h>

namespace root {

namespace graphics {

strong_ptr<instance> instance::m_instance;

instance::instance(allocator* alloc)
:   m_alloc(alloc),
    m_callbacks(alloc)  {
    VkInstanceCreateInfo create_info;
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.pNext = nullptr;
    create_info.flags = 0;
    create_info.pApplicationInfo = nullptr; // TODO

#if defined(ROOT_DEBUG)
    u32 num_layer_properties;
    vkEnumerateInstanceLayerProperties(&num_layer_properties, nullptr);
    array<VkLayerProperties> layer_properties(num_layer_properties);
    vkEnumerateInstanceLayerProperties(&num_layer_properties, layer_properties.data());

    for(int i = 0; i < num_layer_properties; i++) {
        log::d("instance", "Instance Layer Properties {}: {}", i, layer_properties[i]);
    }

    const char* instance_layers[] = {
        "VK_LAYER_LUNARG_standard_validation"
    };

    create_info.enabledLayerCount = 1;
    create_info.ppEnabledLayerNames = instance_layers;

#else
    create_info.enabledLayerCount = 0;
    create_info.ppEnabledLayerNames = nullptr;
#endif

#if !defined(ROOT_ANDROID)
    // TODO: Move this to a different location. Ensure that it cannot be called more than once.
    if(glfwInit() != GLFW_TRUE) {
        log::e("instance", "glfwInit failed");
        abort();
    }

    if(glfwVulkanSupported() != GLFW_TRUE) {
        log::e("instance", "glfwVulkanSupported returned false");
        abort();
    }

    uint32_t glfw_ext_count;
    auto glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_ext_count);

    for(int i = 0; i < glfw_ext_count; i++) {
        log::d("instance", "glfw_extension[{}]: {}", i, glfw_extensions[i]);
    }

    create_info.enabledExtensionCount = glfw_ext_count;
    create_info.ppEnabledExtensionNames = glfw_extensions;
#else
    create_info.enabledExtensionCount = 0;
    create_info.ppEnabledExtensionNames = nullptr;
#endif

    VkInstance handle;
    VkResult res = vkCreateInstance(&create_info, m_callbacks, &m_handle);
    if (res != VK_SUCCESS) {
        log::e("instance", "vkCreateInstance failed with {}", res);
        abort();
    }

    u32 num;
    res = vkEnumeratePhysicalDevices(m_handle, &num, nullptr);
    if (res != VK_SUCCESS) {
        log::e("instance", "vkEnumeratePhysicalDevices failed with {}", res);
        abort();
    }
    
    array<VkPhysicalDevice> phys_devices(num, m_alloc);
    
    res = vkEnumeratePhysicalDevices(m_handle, &num, phys_devices.data());
    if (res != VK_SUCCESS) {
        log::e("instance", "vkEnumeratePhysicalDevices failed with {}", res);
        abort();
    }

    array<physical_device> devices(num, m_alloc);

    for(int i = 0; i < num; i++) {
        devices[i] = physical_device(phys_devices[i]);
    }

    m_physical_devices = std::move(devices);
}

instance::~instance() {
    if(*this) {
        vkDestroyInstance(m_handle, m_callbacks);
    }
}

auto instance::physical_devices() const -> const array<physical_device>& {
    return m_physical_devices;
}

} // namespace graphics

} // namespace root