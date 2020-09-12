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

#include <root/core/array.h>
#include <root/graphics/physical_device.h>

namespace root {

auto physical_device::properties() -> VkPhysicalDeviceProperties* {
    if(m_properties == nullptr) {
        m_properties = reinterpret_cast<VkPhysicalDeviceProperties*>(m_alloc->malloc(sizeof(VkPhysicalDeviceProperties), alignof(VkPhysicalDeviceProperties)));
        vkGetPhysicalDeviceProperties(handle, m_properties);
    }
    return m_properties;
}

auto physical_device::memory_properties() -> VkPhysicalDeviceMemoryProperties* {
    if(m_memory_properties == nullptr) {
        m_memory_properties = reinterpret_cast<VkPhysicalDeviceMemoryProperties*>(m_alloc->malloc(sizeof(VkPhysicalDeviceMemoryProperties), alignof(VkPhysicalDeviceMemoryProperties)));
        vkGetPhysicalDeviceMemoryProperties(handle, m_memory_properties);
    }
    return m_memory_properties;
}

auto physical_device::queue_family_properties() -> array<VkQueueFamilyProperties>& {
    if(!m_family_properties) {
        u32 num;
        vkGetPhysicalDeviceQueueFamilyProperties(handle, &num, nullptr);

        array<VkQueueFamilyProperties> props(num, m_alloc);
        vkGetPhysicalDeviceQueueFamilyProperties(handle, &num, props.data());

        m_family_properties = std::move(props);
    }
    return m_family_properties;
}

} // namespace root