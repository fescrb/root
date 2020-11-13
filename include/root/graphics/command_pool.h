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

#include <root/graphics/vk_handle_container.h>
#include <root/graphics/device.h>

namespace root {

namespace graphics {

class command_pool : public vk_handle_container<VkCommandPool, command_pool> {
public:
    // TODO: take into account present/compute pools?
    command_pool(const device& dev, allocator* alloc = allocator::get_default());

    ~command_pool();

    inline auto device() const -> VkDevice {
        return m_device_handle;
    }

public:
    VkDevice m_device_handle;
    allocator* m_alloc;
};

} // namespace graphics

} // namespace root