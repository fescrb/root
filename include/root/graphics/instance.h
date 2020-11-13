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

#include <root/core/array.h>
#include <root/memory/strong_ptr.h>
#include <root/graphics/vk_handle_container.h>
#include <root/graphics/vk_allocation_callbacks.h>
#include <root/graphics/physical_device.h>

namespace root {

namespace graphics {

class instance final : public vk_handle_container<VkInstance,instance> {
public:
    instance(allocator* alloc = allocator::get_default());
    ~instance();

    instance(const instance&) = delete;
    inline instance(instance&& other) {
        m_handle = std::move(other.m_handle);
        m_callbacks = std::move(other.m_callbacks);
        other.clear();
    }

    auto operator=(const instance&) -> instance& = delete;
    inline auto operator=(instance&& other) -> instance& {
        if(this != &other) {
            m_handle = std::move(other.m_handle);
            m_callbacks = std::move(other.m_callbacks);
            other.clear();
        }
        return *this;
    }

    static inline auto get() -> strong_ptr<instance>& {
        return m_instance;
    }

    static inline auto set(const strong_ptr<instance>& i) -> void {
        m_instance = i;
    }

    auto physical_devices() const -> const array<physical_device>&;

private:
    allocator* m_alloc;
    vk_allocation_callbacks m_callbacks;
    array<physical_device> m_physical_devices;
    static strong_ptr<instance> m_instance;
};

} // namespace graphics

} // namespace root