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
#include <root/graphics/renderpass.h>

namespace root {

class framebuffer : public vk_handle_container<VkFramebuffer,framebuffer> {
public:
    framebuffer(const device& dev, 
                const renderpass& rp, 
                const array_slice<VkImageView>& attachments, 
                VkExtent3D dimensions, 
                allocator* alloc = allocator::default_allocator());

    framebuffer(const device& dev, 
                const renderpass& rp, 
                const array_slice<VkImageView>& attachments, 
                VkExtent2D dimensions, 
                allocator* alloc = allocator::default_allocator())
    :   framebuffer(dev, rp, attachments, {dimensions.width, dimensions.height, 1}, alloc) {}

    framebuffer(const framebuffer&) = delete;
    framebuffer(framebuffer&& other) 
    :   vk_handle_container(std::move(other)),
        m_device_handle(std::move(other.m_device_handle)),
        m_alloc(std::move(other.m_alloc)) {
        other.m_device_handle = VK_NULL_HANDLE;
        other.m_alloc = nullptr;
    }

    inline auto operator=(framebuffer&& other) -> framebuffer& {
        if(&other != this) {
            m_handle = std::move(other.m_handle);
            m_device_handle = std::move(other.m_device_handle);
            m_alloc = std::move(other.m_alloc);
            other.m_handle = VK_NULL_HANDLE;
            other.m_device_handle = VK_NULL_HANDLE;
            other.m_alloc = nullptr;

        }
        return *this;
    }


    ~framebuffer();

private:
    VkDevice m_device_handle;
    allocator* m_alloc;
};

} // namespace root