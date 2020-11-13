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
#include <root/graphics/device.h>
#include <root/graphics/command_pool.h>
#include <root/graphics/renderpass.h>
#include <root/graphics/framebuffer.h>
#include <root/graphics/pipeline.h>

// TODO: container to allocate/free command buffers in a batch

namespace root {

namespace graphics {

class command_buffer : public vk_handle_container<VkCommandBuffer,command_buffer> {
public:
    command_buffer(const command_pool& pool);

    // Could be const would like a const command_buffer to be immutable
    auto begin() -> void;
    auto start_render_pass(const renderpass& rp, const graphics::framebuffer& fb) -> void;
    auto bind_pipeline(const pipeline& p) -> void;
    auto draw(u32 vertex_count, u32 instance_count, u32 first_vertex, u32 first_instance) -> void;
    auto end_render_pass() -> void;
    auto end() -> void;

    ~command_buffer();

private:
    const command_pool& m_command_pool;
};

} // namespace graphics

} // namespace root