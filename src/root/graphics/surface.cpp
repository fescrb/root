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

#include <root/graphics/surface.h>

#include <root/graphics/instance.h>
#include <root/io/log.h>

#if !defined(ROOT_ANDROID)
#include <GLFW/glfw3.h>
#endif

namespace root {

namespace graphics {

#if !defined(ROOT_ANDROID)
surface::surface(const strong_ptr<instance>& i, const strong_ptr<window>& w) {
    root_assert(i && w);
    VkResult res = glfwCreateWindowSurface(i->handle(), w->handle(), NULL, &m_handle);
    if(res != VK_SUCCESS) {
        // TODO: error handling
        log::e("surface", "glfwCreateWindowSurface failed with {}", res);
        abort();
    }
}
#endif

} // namespace 

} // namespace root