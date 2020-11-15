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

#include <root/graphics/graphics.h>

#include <root/io/path.h>
#include <root/graphics/instance.h>
#if !defined(ROOT_ANDROID)
#include <root/graphics/window.h>
#endif
#include <root/graphics/surface.h>
#include <root/graphics/device.h>
#include <root/graphics/swapchain.h>

namespace root {

namespace graphics {

auto init(allocator* alloc) -> void {
    if (!instance::get()) 
        instance::set(alloc->make_strong<instance>());
    // TODO: give the name of the binary
#if !defined(ROOT_ANDROID)
    if (!window::get_default()) 
        window::set_default(alloc->make_strong<window>(640u, 480u, path::binary_name()));
    if (!surface::get_default()) 
        surface::set_default(alloc->make_strong<surface>(instance::get(), window::get_default()));
#endif
    if (!device::get_default()) 
        device::set_default(device::auto_select_device(instance::get(), surface::get_default()));
    if (!swapchain::get_default())
        swapchain::set_default(alloc->make_strong<swapchain>(device::get_default(),surface::get_default()));
}

} // namespace graphics

} // namespace root