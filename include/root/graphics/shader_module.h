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

#include <root/core/buffer.h>
#include <root/graphics/device.h>
#include <root/asset/asset_manager.h>

#include <vulkan/vulkan.h>

namespace root {

namespace graphics {

class shader_module {
public:
    explicit shader_module(const device& d, const buffer& b);
    explicit shader_module(const device& d, const string_view& asset_id) 
    :   shader_module(d, asset_manager::raw_load(asset_id)) {}

    VkShaderModule handle;
};

} // namespace graphics

} // namespace root