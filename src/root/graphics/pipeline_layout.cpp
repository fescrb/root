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

#include <root/graphics/pipeline_layout.h>

#include <root/io/log.h>

namespace root {

namespace graphics {

pipeline_layout::pipeline_layout(const device& dev, const VkViewport& vp, const VkRect2D& sc) 
:   viewport(vp),
    scissor(sc),
    m_handle(VK_NULL_HANDLE),
    m_device_handle(dev.handle),
    m_alloc(nullptr) {
    viewport_state.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewport_state.pNext = nullptr;
    viewport_state.flags = 0;
    viewport_state.viewportCount = 1;
    viewport_state.pViewports = &viewport;
    viewport_state.scissorCount = 0;
    viewport_state.pScissors = &scissor;
    
    // TODO parameterize
    multisampling_info.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling_info.pNext = nullptr;
    multisampling_info.flags = 0;
    multisampling_info.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    multisampling_info.sampleShadingEnable = VK_FALSE;
    multisampling_info.minSampleShading = 1.0f;
    multisampling_info.pSampleMask = nullptr;
    multisampling_info.alphaToCoverageEnable = VK_FALSE;
    multisampling_info.alphaToOneEnable = VK_FALSE;
    
    // TODO parameterize
    color_blend_attachment.colorWriteMask == VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    color_blend_attachment.blendEnable = VK_FALSE;
    color_blend_attachment.blendEnable = VK_TRUE;
    // Coverage blending
    color_blend_attachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
    color_blend_attachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    color_blend_attachment.colorBlendOp = VK_BLEND_OP_ADD;
    color_blend_attachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    color_blend_attachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    color_blend_attachment.alphaBlendOp = VK_BLEND_OP_ADD;
    // TODO parameterize
    color_blend_state.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    color_blend_state.pNext = nullptr;
    color_blend_state.flags = 0;
    color_blend_state.logicOpEnable = VK_FALSE;
    color_blend_state.logicOp = VK_LOGIC_OP_COPY;
    color_blend_state.attachmentCount = 1;
    color_blend_state.pAttachments = &color_blend_attachment;
    color_blend_state.blendConstants[0] = 0.0f; 
    color_blend_state.blendConstants[1] = 0.0f; 
    color_blend_state.blendConstants[2] = 0.0f; 
    color_blend_state.blendConstants[3] = 0.0f; 
    // TODO deal with dynamic parameters via VkPipelineDynamicStateCreateInfo

    VkPipelineLayoutCreateInfo pipeline_layout_info; 
    pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipeline_layout_info.pNext = nullptr;
    pipeline_layout_info.flags = 0;
    pipeline_layout_info.setLayoutCount = 0; // No uniforms for now
    pipeline_layout_info.pSetLayouts = nullptr; 
    pipeline_layout_info.pushConstantRangeCount = 0; 
    pipeline_layout_info.pPushConstantRanges = nullptr; 

    // TODO use our own allocator
    VkResult res = vkCreatePipelineLayout(m_device_handle, &pipeline_layout_info, nullptr, &m_handle);
    if(res != VK_SUCCESS) {
        log::e("pipeline", "vkCreatePipelineLayout failed with {}", res);
        abort();
    }
}

pipeline_layout::~pipeline_layout() {
    if(m_handle != VK_NULL_HANDLE) {
        vkDestroyPipelineLayout(m_device_handle, m_handle, nullptr);
    }
}

} // namespace graphics

} // namespace root