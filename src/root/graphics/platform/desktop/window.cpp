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
#include <GLFW/glfw3.h>
#include <root/graphics/platform/desktop/window.h>
#endif

namespace root {

namespace graphics {

strong_ptr<window> window::m_default_window;

window::window(const u32 width, const u32 height, const string_view& title, allocator* alloc) 
:   m_title(title, alloc) {
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    m_handle = glfwCreateWindow(width, height, m_title.data(), nullptr, nullptr);
}

window::~window() {
    if(m_handle) {
        glfwDestroyWindow(m_handle);
    }
}

} // namespace graphics

} // namespace root