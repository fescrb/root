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

#include <root/memory/strong_ptr.h>
#include <root/graphics/vk_handle_container.h>
#include <root/graphics/vk_allocation_callbacks.h>

#include <root/graphics/instance.h>

namespace root {

namespace graphics {

class window;

class surface final : public vk_handle_container<VkSurfaceKHR,surface> {
public:
#if defined(ROOT_ANDROID)
    surface(const strong_ptr<instance>& i /*, android_app**/);
#else
    surface(const strong_ptr<instance>& i, const strong_ptr<window>& w, allocator* alloc = allocator::get_default());
#endif

    ~surface();

    surface() = delete;
    surface(const surface&) = delete;
    inline surface(surface&& other) {
        m_handle = std::move(other.m_handle);
        m_callbacks = std::move(other.m_callbacks);
        m_instance = std::move(other.m_instance);
        other.clear();
    }

    auto operator=(const surface&) -> surface& = delete;
    inline auto operator=(surface&& other) -> surface& {
        if(this != &other) {
            m_handle = std::move(other.m_handle);
            m_callbacks = std::move(other.m_callbacks);
            m_instance = std::move(other.m_instance);
            other.clear();
        }
        return *this;
    }

    static inline auto get_default() -> strong_ptr<surface>& {
        return m_default_surface;
    }

    static inline auto set_default(const strong_ptr<surface>& s) -> void {
        m_default_surface = s;
    }

private:
    vk_allocation_callbacks m_callbacks;
    strong_ptr<instance> m_instance;

    static strong_ptr<surface> m_default_surface;
};

} // namespace graphics

} // namespace root