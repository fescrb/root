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

#include <root/graphics/shader_module.h>

namespace root {

namespace graphics {

struct shader {
    shader(const shader_module& module, 
           VkShaderStageFlagBits stage_flags, 
           const string_view& funcname,
           allocator* alloc = allocator::get_default())
    :   func_name(funcname, alloc),
        info {
            VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            nullptr,
            0,
            stage_flags,
            module.handle,
            func_name.data(),
            nullptr
        } {}

    const string func_name; // TODO this means we cannot copy this. Think about making this a strong_ptr or interned string?
    const VkPipelineShaderStageCreateInfo info;
};

} // namespace graphics

} // namespace root