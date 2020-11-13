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

#include <root/graphics/shader.h>
#include <root/graphics/vertex_input.h>
#include <root/graphics/input_assembly.h>
#include <root/graphics/pipeline_layout.h>
#include <root/graphics/raster.h>
#include <root/graphics/renderpass.h>

#include <root/io/log.h>

namespace root {

class pipeline {
public:
    pipeline(const device& dev, 
             const array_slice<shader>& shaders, 
             const vertex_input& vi,
             const input_assembly& ia,
             const pipeline_layout& pl,
             const raster& r,
             const renderpass& rp,
             allocator* alloc = allocator::get_default())
    :   m_handle(VK_NULL_HANDLE),
        m_device_handle(dev.handle),
        m_alloc(alloc) {
        VkGraphicsPipelineCreateInfo pipeline_create;
        pipeline_create.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        pipeline_create.pNext = nullptr;
        pipeline_create.flags = 0;
        pipeline_create.stageCount = shaders.size();
        VkPipelineShaderStageCreateInfo *shader_info = reinterpret_cast<VkPipelineShaderStageCreateInfo*>(
            m_alloc->malloc(
                sizeof(VkPipelineShaderStageCreateInfo)*shaders.size(), 
                alignof(VkPipelineShaderStageCreateInfo)
            )
        );
        for(u32 i = 0; i < shaders.size(); i++) {
            shader_info[i] = shaders[i].info;
        }
        pipeline_create.pStages = shader_info;
        pipeline_create.pVertexInputState = &vi.info;
        pipeline_create.pInputAssemblyState = &ia.info;
        pipeline_create.pTessellationState = nullptr;
        pipeline_create.pViewportState = &pl.viewport_state;
        pipeline_create.pRasterizationState = &r.info;
        pipeline_create.pMultisampleState = &pl.multisampling_info;
        pipeline_create.pDepthStencilState = nullptr;
        pipeline_create.pColorBlendState = &pl.color_blend_state;
        pipeline_create.pDynamicState = nullptr;
        pipeline_create.layout = pl.handle();
        pipeline_create.renderPass = rp.handle();
        pipeline_create.subpass = 0;
        pipeline_create.basePipelineHandle = VK_NULL_HANDLE;
        pipeline_create.basePipelineIndex = -1;

        VkResult res = vkCreateGraphicsPipelines(m_device_handle, VK_NULL_HANDLE, 1, &pipeline_create, nullptr, &m_handle);

        if(res != VK_SUCCESS) {
            log::e("pipeline", "vkCreateGraphicsPipelines failed with {}", res);
            abort();
        }

        // Cleanup
        m_alloc->free(shader_info);
    }

    inline auto handle() const -> VkPipeline {
        return m_handle;
    }

    ~pipeline() {
        if(m_handle != VK_NULL_HANDLE) {
            vkDestroyPipeline(m_device_handle, m_handle, nullptr);
        }
    }

private:
    VkPipeline m_handle;
    VkDevice m_device_handle;
    allocator* m_alloc;
};

} // namespace root