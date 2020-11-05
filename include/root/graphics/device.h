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

#include <root/graphics/physical_device.h>
#include <root/graphics/surface.h>

namespace root {

class device final {
public:
    device(const physical_device& d, const surface& s);

    static device auto_select_device();

    VkDevice handle;

    auto get_graphics_queue() const -> VkQueue;
    inline auto get_physical_device() const -> const physical_device& {
        return m_physical_device;
    }

private:
    uint32_t m_graphics_family_index;
    const physical_device& m_physical_device;
};

} // namespace root