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

#include <root/graphics/semaphore.h>

#include <root/graphics/vk_errors.h>

namespace root {

namespace graphics {

semaphore::semaphore(const device& dev, allocator* alloc)
:   m_device_handle(dev.handle()),
    m_alloc(alloc) {
    VkSemaphoreCreateInfo semaphore_info;
    semaphore_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    semaphore_info.pNext = nullptr;
    semaphore_info.flags = 0;

    root_check_vk_result(vkCreateSemaphore(m_device_handle, &semaphore_info, nullptr, &m_handle));
}

semaphore::~semaphore() {
    if(*this) {
        vkDestroySemaphore(m_device_handle, m_handle, nullptr);
    }
}

} // namespace graphics

} // namespace root