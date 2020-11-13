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

#include <root/graphics/device.h>
#include <root/graphics/swapchain.h>
#include <root/io/log.h>

namespace root {

namespace graphics {

class pipeline_layout {
public:
    pipeline_layout(const device& dev, const VkViewport& vp, const VkRect2D& sc);

    // Makes a pipeline with a swapchain target
    pipeline_layout(const device& dev, const swapchain& sw) 
    :   pipeline_layout(dev, sw.viewport(), sw.scissor()) {}

    const VkViewport viewport;
    const VkRect2D scissor;
    VkPipelineViewportStateCreateInfo viewport_state;
    VkPipelineMultisampleStateCreateInfo multisampling_info;
    VkPipelineColorBlendAttachmentState color_blend_attachment;
    VkPipelineColorBlendStateCreateInfo color_blend_state;

    inline auto handle() const -> VkPipelineLayout {
        return m_handle;
    }

    ~pipeline_layout();

private:
    VkPipelineLayout m_handle; 
    VkDevice m_device_handle;
    allocator* m_alloc;
};

} // namespace graphics

} // namespace root