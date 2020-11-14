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

#include <root/graphics/shader_module.h>

#include <root/io/log.h>

namespace root {

namespace graphics {

shader_module::shader_module(const device& d,const buffer& buf) {
    VkShaderModuleCreateInfo create_info;
    create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    create_info.pNext = nullptr;
    create_info.flags = 0;
    create_info.codeSize = buf.size();
    create_info.pCode = reinterpret_cast<uint32_t*>(buf.data());

    VkResult res = vkCreateShaderModule(d.handle(), &create_info, nullptr, &handle);

    if(res != VK_SUCCESS) {
        log::e("shader_module", "vkCreateShaderModule failed with {}", res);
    }
}

} // namespace graphics

} // namespace root