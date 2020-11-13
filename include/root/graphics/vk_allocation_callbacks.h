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

namespace graphics {

class vk_allocation_callbacks {
public:
    vk_allocation_callbacks() : m_callbacks() {
        m_callbacks.pUserData = nullptr;
    }

    vk_allocation_callbacks(allocator* alloc);

    inline operator const VkAllocationCallbacks*() const {
        if (!m_callbacks.pUserData) return nullptr;
        return &m_callbacks;
    }    

protected:
    VkAllocationCallbacks m_callbacks;
};

} // namespace graphics

} // namespace root