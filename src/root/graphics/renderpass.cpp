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

#include <root/graphics/renderpass.h>

#include <root/io/log.h>

namespace root {

namespace graphics {

renderpass::renderpass(const device& d, const attachment& attachment, allocator* alloc)
:   renderpass() {
    m_device_handle = d.handle();
    m_alloc = alloc;

    VkAttachmentReference color_attachment_ref;
    color_attachment_ref.attachment = 0;
    color_attachment_ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass_description;
    subpass_description.flags = 0;
    subpass_description.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass_description.inputAttachmentCount = 0;
    subpass_description.pInputAttachments = nullptr;
    subpass_description.colorAttachmentCount = 1;
    subpass_description.pColorAttachments = &(color_attachment_ref);
    subpass_description.pResolveAttachments = nullptr;
    subpass_description.pDepthStencilAttachment = nullptr;
    subpass_description.preserveAttachmentCount = 0;
    subpass_description.pPreserveAttachments = nullptr;

    VkRenderPassCreateInfo renderpass_info;
    renderpass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderpass_info.pNext = nullptr;
    renderpass_info.flags = 0;
    renderpass_info.attachmentCount = 1;
    renderpass_info.pAttachments = &attachment.description;
    renderpass_info.subpassCount = 1;
    renderpass_info.pSubpasses = &subpass_description;
    // Dependencies not used for now
    renderpass_info.dependencyCount = 0;
    renderpass_info.pDependencies = nullptr;

    // TODO: pass our own allocator
    VkResult res = vkCreateRenderPass(d.handle(), &renderpass_info, nullptr, &m_handle);

    if(res != VK_SUCCESS) {
        log::e("renderpass", "vkCreateRenderPass failed with {}", res);
        abort();
    }
}

renderpass::~renderpass() {
    if(m_handle != VK_NULL_HANDLE) {
        vkDestroyRenderPass(m_device_handle, m_handle, nullptr);
    }
}

} // namespace graphics

} // namespace root