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

#include <root/graphics/framebuffer.h>

#include <root/io/log.h>

namespace root {

namespace graphics {

framebuffer::framebuffer(const device& dev, 
                         const renderpass& rp, 
                         const array_slice<VkImageView>& attachments, 
                         VkExtent3D dimensions, 
                         allocator* alloc) 
:   vk_handle_container(),
    m_device_handle(dev.handle),
    m_extent({dimensions.width, dimensions.height}),
    m_alloc(alloc) {
    VkFramebufferCreateInfo framebuffer_create_info;
    framebuffer_create_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebuffer_create_info.pNext = nullptr;
    framebuffer_create_info.flags = 0;
    framebuffer_create_info.renderPass = rp.handle();
    framebuffer_create_info.attachmentCount = 1;
    framebuffer_create_info.pAttachments = attachments;
    framebuffer_create_info.width = dimensions.width;
    framebuffer_create_info.height = dimensions.height;
    framebuffer_create_info.layers = dimensions.depth;

    VkResult res = vkCreateFramebuffer(m_device_handle, &framebuffer_create_info, nullptr, &m_handle);

    if(res != VK_SUCCESS) {
        log::e("framebuffer", "vkCreateFramebuffer failed with {}", res);
        abort();
    }
}

framebuffer::~framebuffer() {
    if(m_handle != VK_NULL_HANDLE) {
        vkDestroyFramebuffer(m_device_handle, m_handle, nullptr);
    }
}

} // namespace graphics

} // namespace root