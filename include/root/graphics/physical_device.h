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

#include <root/memory/allocator.h>

namespace root {

class physical_device final {
public:
    explicit physical_device(const VkPhysicalDevice& h)
    :   handle(h),
        m_properties(nullptr),
        m_memory_properties(nullptr) {}

    VkPhysicalDevice handle;

    auto properties() -> VkPhysicalDeviceProperties*;
    auto memory_properties() -> VkPhysicalDeviceMemoryProperties*;
    auto queue_family_properties(allocator* alloc = allocator::default_allocator()) -> array<VkQueueFamilyProperties>&;

private:
    VkPhysicalDeviceProperties *m_properties;
    VkPhysicalDeviceMemoryProperties *m_memory_properties;
    array<VkQueueFamilyProperties> m_family_properties;
};

} // namespace root