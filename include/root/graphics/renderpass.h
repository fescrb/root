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

#include <root/memory/allocator.h>
#include <root/graphics/attachment.h>
#include <root/graphics/device.h>

namespace root {

class renderpass final {
public:
    inline renderpass() 
    :   m_handle(VK_NULL_HANDLE), 
        m_device_handle(VK_NULL_HANDLE), 
        m_alloc(nullptr) {}

    renderpass(const renderpass&) = delete;
    inline renderpass(renderpass&& other)
    :   m_handle(std::move(other.m_handle)),
        m_alloc(std::move(other.m_alloc)) {
        other.m_handle = VK_NULL_HANDLE;
        other.m_alloc = nullptr;
    }
    // TODO: 
    // * subpass class
    // * Create renderpasses out of initializer lists
    renderpass(const device& d, const attachment& attachment, allocator* alloc = allocator::default_allocator());

    inline auto handle() const -> VkRenderPass {
        return m_handle;
    }

    // TODO: release renderpass on destructor
    ~renderpass();

    inline operator bool() const {
        return m_handle != VK_NULL_HANDLE;
    }

private:
    VkRenderPass m_handle;
    VkDevice m_device_handle;
    allocator* m_alloc;
};

} // namespace root