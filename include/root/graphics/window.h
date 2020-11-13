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

#if !defined(ROOT_ANDROID)
struct GLFWwindow;
#endif

#include <root/core/string.h>
#include <root/memory/strong_ptr.h>

namespace root {

namespace graphics {

class window {
public:
    window(const u32 width, const u32 height, const string_view& title, allocator* alloc = allocator::get_default());
    window() = delete;
    window(const window&) = delete;
    inline window(window&& other)
    :   m_handle(std::move(other.m_handle)),
        m_title(std::move(other.m_title)) {
        other.m_handle = nullptr;
    }

    auto operator=(const window&) -> window& = delete;
    inline auto operator=(window&& other) -> window& {
        if (this != &other) {
            m_handle = std::move(other.m_handle);
            m_title = std::move(other.m_title);  
            other.m_handle = nullptr; 
        }
        return *this;
    }

    ~window();

#if !defined(ROOT_ANDROID)
    inline auto handle() const -> GLFWwindow* {
        return m_handle;
    }
#endif

    inline static auto get_default() -> strong_ptr<window>& {
        return m_default_window;
    }

    inline static auto set_default(const strong_ptr<window>& w) -> void {
        m_default_window = w;
    }

private:
    string m_title;
#if !defined(ROOT_ANDROID)
    GLFWwindow* m_handle;
#endif

    static strong_ptr<window> m_default_window;
};

} // namespace graphics

} // namespace root