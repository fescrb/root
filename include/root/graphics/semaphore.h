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

class semaphore : public vk_handle_container<VkSemaphore,semaphore> {
public:
    semaphore(const device& dev, allocator* alloc = allocator::default_allocator());

    ~semaphore();

private:
    VkDevice m_device_handle;
    allocator* m_alloc;
};

} // namespace root