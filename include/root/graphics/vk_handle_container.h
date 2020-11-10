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
#include <utility>

namespace root {

template<typename vk_handle_t, typename subclass_t>
class vk_handle_container {
public:
    inline constexpr vk_handle_container() noexcept 
    :   m_handle(VK_NULL_HANDLE) {}
    inline constexpr vk_handle_container(const vk_handle_container& other) noexcept 
    :   m_handle(other.m_handle) {}
    inline constexpr vk_handle_container(vk_handle_container&& other) noexcept 
    :   m_handle(std::move(other.m_handle)) {
        other.m_handle = VK_NULL_HANDLE;
    }

    inline auto handle() const -> const vk_handle_t& {
        return m_handle;
    }

    inline operator bool() const {
        return m_handle != VK_NULL_HANDLE;
    }

protected:
    inline constexpr vk_handle_container(const subclass_t& other) noexcept
    :   m_handle(other.m_handle) {}

    vk_handle_t m_handle;
};

} // namespace root