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

#include <limits>

#include <root/graphics/vk_handle_container.h>

#include <root/memory/allocator.h>
#include <root/core/array.h>

namespace root {

namespace graphics {

class surface;

class physical_device final : public vk_handle_container<VkPhysicalDevice,physical_device>{
public:
    physical_device() : vk_handle_container() {}

    physical_device(const physical_device& other)
    :   vk_handle_container(other) {}

    physical_device(physical_device&& other)
    :   vk_handle_container(std::move(other)) {}

    auto operator=(const physical_device& other) -> physical_device& {
        m_handle = other.m_handle;
        return *this;
    }
    inline auto operator=(physical_device&& other) -> physical_device& {
        m_handle = std::move(other.m_handle);
        return *this;
    }

    auto properties() const -> VkPhysicalDeviceProperties;
    auto memory_properties() const -> VkPhysicalDeviceMemoryProperties;
    auto queue_family_properties(allocator* alloc = allocator::get_default()) const -> const array<VkQueueFamilyProperties>;
    auto extensions(allocator* alloc = allocator::get_default()) const -> const array<VkExtensionProperties>;

    auto has_graphics_queue() const -> bool;
    auto has_present_queue(const strong_ptr<surface>& s) const -> bool;
    
    auto graphics_queue_family_index() const -> u32;
    auto present_queue_family_index(const strong_ptr<surface>& s) const -> u32;

    auto can_present(const strong_ptr<surface>& s, const u32& family_queue_index) const -> VkBool32;

    static constexpr u32 FAMILY_INVALID = std::numeric_limits<uint32_t>::max();

private:
    explicit physical_device(const VkPhysicalDevice& h);

    friend class instance;
};

} // namespace graphics

} // namespace root