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

#include <vulkan/vulkan.h>

#include <root/core/array.h>
#include <root/graphics/physical_device.h>

namespace root {
namespace graphics {

class instance final {
public:

    static auto init() -> void;

    static inline auto get() -> instance* {
        return m_instance;
    }

    auto physical_devices(allocator* alloc = allocator::default_allocator()) const -> array<physical_device>;

    VkInstance handle;

private:
    inline instance(const VkInstance& h)
    :   handle(h) {}

    static instance* m_instance;
};

} // namespace graphics
} // namespace root