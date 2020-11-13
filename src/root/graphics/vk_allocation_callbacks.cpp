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

#include <root/graphics/vk_allocation_callbacks.h>

#include <root/core/assert.h>

#include <cstring>

namespace root {

namespace graphics {

auto vk_alloc(void* user_data, size_t size, size_t alignment, VkSystemAllocationScope) -> void* {
    root_assert(user_data != nullptr);
    return reinterpret_cast<allocator*>(user_data)->malloc(size, alignment);
}

auto vk_free(void* user_data, void* ptr) -> void {
    if (ptr != nullptr) {
        root_assert(user_data != nullptr);
        reinterpret_cast<allocator*>(user_data)->free(ptr);
    }
}

auto vk_realloc(void* user_data, void* original_ptr, size_t size, size_t alignment, VkSystemAllocationScope scope) -> void* {
    void* new_mem = vk_alloc(user_data, size, alignment, scope);
    memcpy(new_mem, original_ptr, size);
    vk_free(user_data, original_ptr);
    return new_mem;
}

vk_allocation_callbacks::vk_allocation_callbacks(allocator* alloc)
:   m_callbacks() {
    m_callbacks.pUserData = alloc;
    m_callbacks.pfnAllocation = vk_alloc;
    m_callbacks.pfnFree = vk_free;
    m_callbacks.pfnReallocation = vk_realloc;
    m_callbacks.pfnInternalAllocation = nullptr;
    m_callbacks.pfnInternalFree = nullptr;
}

} // namespace graphics

} // namespace root