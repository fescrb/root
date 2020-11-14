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

#include <root/graphics/command_pool.h>

#include <root/io/log.h>

namespace root {

namespace graphics {

command_pool::command_pool(const root::graphics::device& dev, allocator* alloc)
:   vk_handle_container(),
    m_device_handle(dev.handle()),
    m_alloc(alloc) {
    VkCommandPoolCreateInfo command_pool_create_info;
    command_pool_create_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    command_pool_create_info.pNext = nullptr;
    command_pool_create_info.flags = 0;
    command_pool_create_info.queueFamilyIndex = dev.graphics_family_index();

    VkResult res = vkCreateCommandPool(m_device_handle, &command_pool_create_info, nullptr, &m_handle);

    if(res != VK_SUCCESS) {
        log::e("command_pool", "vkCreateCommandPool failed with {}", res);
        abort();
    }
}

command_pool::~command_pool() {
    if(*this) {
        vkDestroyCommandPool(m_device_handle, m_handle, nullptr);
    }
}

} // namespace graphics

} // namespace root