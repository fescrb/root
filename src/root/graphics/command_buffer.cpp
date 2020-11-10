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

#include <root/graphics/command_buffer.h>

#include <root/graphics/vk_errors.h>

namespace root {

command_buffer::command_buffer(const command_pool& pool)
:   vk_handle_container(),
    m_command_pool(pool) {
    VkCommandBufferAllocateInfo command_buffer_info;
    command_buffer_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    command_buffer_info.pNext = nullptr;
    command_buffer_info.commandPool = pool.handle();
    command_buffer_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    command_buffer_info.commandBufferCount = 1;

    VkResult res = vkAllocateCommandBuffers(pool.device(), &command_buffer_info, &m_handle);

    if(res != VK_SUCCESS) {
        log::e("command_buffer", "vkAllocateCommandBuffers failed with {}", res);
        abort();
    }
}

auto command_buffer::begin() -> void {
    VkCommandBufferBeginInfo begin_info;
    begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    begin_info.pNext = nullptr;
    begin_info.flags = 0;
    begin_info.pInheritanceInfo = nullptr;

    root_check_vk_result(vkBeginCommandBuffer(m_handle, &begin_info));
}


auto command_buffer::start_render_pass(const renderpass& rp, const framebuffer& fb) -> void {
    // TODO check if were valid before doin this
    VkRenderPassBeginInfo begin_info;
    begin_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    begin_info.pNext = nullptr;
    begin_info.renderPass = rp.handle();
    begin_info.framebuffer = fb.handle();
    // TODO: these two as parameters
    begin_info.renderArea = {{0, 0}, fb.entent()};
    VkClearValue clear_col = {0.0f, 0.0f, 0.0f, 1.0f};
    begin_info.clearValueCount = 1;
    begin_info.pClearValues = &clear_col;

    // Subcommands?
    vkCmdBeginRenderPass(m_handle, &begin_info, VK_SUBPASS_CONTENTS_INLINE);
}

auto command_buffer::bind_pipeline(const pipeline& p) -> void {
    vkCmdBindPipeline(m_handle, VK_PIPELINE_BIND_POINT_GRAPHICS, p.handle());
}

auto command_buffer::draw(u32 vertex_count, u32 instance_count, u32 first_vertex, u32 first_instance) -> void {
    vkCmdDraw(m_handle, vertex_count, instance_count, first_vertex, first_instance);
}

auto command_buffer::end_render_pass() -> void {
    vkCmdEndRenderPass(m_handle);
}

auto command_buffer::end() -> void {
    root_check_vk_result(vkEndCommandBuffer(m_handle));
}

command_buffer::~command_buffer() {
    if(*this) {
        vkFreeCommandBuffers(m_command_pool.device(), m_command_pool.handle(), 1, &m_handle);
    }
}

} // namespace root