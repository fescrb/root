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

#include <root/graphics/instance.h>

namespace root {

namespace graphics {

auto init(allocator* alloc) -> void {
    if (!instance::get()) instance::set(alloc->make_strong<instance>());
    if (!window::get_default()) window::set_default(alloc->make_strong<window>(640u, 480u, "Test"));
}

} // namespace graphics

} // namespace root