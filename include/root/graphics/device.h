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
#include <root/graphics/physical_device.h>
#include <root/graphics/surface.h>

namespace root {

namespace graphics {

class device final : public vk_handle_container<VkDevice,device> {
public:
    /*
     * TODO: allow making & selecting a device without a target surface
     */
    device(const physical_device& phys_d, 
           const strong_ptr<surface>& target_surface, 
           allocator* alloc = allocator::get_default());

    ~device();

    device() = delete;
    device(const device&) = delete;
    inline device(device&& other) {
        m_handle = std::move(other.m_handle);
        m_callbacks = std::move(other.m_callbacks);
        m_graphics_family_index = std::move(other.m_graphics_family_index);
        m_present_family_index = std::move(other.m_present_family_index);
        m_physical_device = std::move(other.m_physical_device);
    }

    auto operator=(const device&) -> device& = delete; 
    auto operator=(device&& other) -> device& {
        if (this != &other) {
            m_handle = std::move(other.m_handle);
            m_callbacks = std::move(other.m_callbacks);
            m_graphics_family_index = std::move(other.m_graphics_family_index);
            m_present_family_index = std::move(other.m_present_family_index);
            m_physical_device = std::move(other.m_physical_device);
            other.clear();
        }
        return *this;
    } 

    static auto auto_select_device(const strong_ptr<instance>& i, 
                                   const strong_ptr<surface>& target_surface, 
                                   allocator* alloc = allocator::get_default()) -> strong_ptr<device>;

    auto get_graphics_queue() const -> VkQueue;
    auto get_present_queue() const -> VkQueue;
    
    inline auto get_physical_device() const -> const  physical_device& {
        return m_physical_device;
    }

    inline auto graphics_family_index() const -> u32 {
        return m_graphics_family_index;
    }

    inline auto present_family_index() const -> u32 {
        return m_present_family_index;
    }

    static inline auto get_default() -> strong_ptr<device>& {
        return m_default_device;
    }

    static inline auto set_default(const strong_ptr<device>& d) -> void {
        m_default_device = d;
    }

    inline auto wait_idle() const -> void {
        vkDeviceWaitIdle(m_handle);
    }

    class dependent {
    public:
        inline auto get_device() const -> const strong_ptr<device>& {
            return m_device;
        }

    protected:
        dependent() = delete;
        dependent(const dependent&) = default;
        dependent(dependent&&) = default;
        inline dependent(const strong_ptr<root::graphics::device>& dev) 
        : m_device(dev) {}

        inline auto operator=(const dependent& other) -> dependent& {
            if (this != &other) {
                m_device = other.m_device;
            }
            return *this;
        }

        inline auto operator=(dependent&& other) -> dependent& {
            if (this != &other) {
                m_device = std::move(other.m_device);
            }
            return *this;
        }


        strong_ptr<root::graphics::device> m_device;
    };

private:
    vk_allocation_callbacks m_callbacks;
    u32 m_graphics_family_index;
    u32 m_present_family_index;
    physical_device m_physical_device;

    static strong_ptr<device> m_default_device;
};

} // namespace graphics

} // namespace root