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

namespace root {

struct raster {
    raster() {
        info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        info.pNext = nullptr;
        info.flags = 0;
        info.depthClampEnable = VK_FALSE;
        info.rasterizerDiscardEnable = VK_FALSE;
        info.polygonMode = VK_POLYGON_MODE_FILL; // TODO allow wireframe (VK_POLYGON_MODE_LINE)
        // TODO: parameterize the following 3
        info.lineWidth = 1.0f; 
        info.cullMode = VK_CULL_MODE_BACK_BIT; 
        info.frontFace = VK_FRONT_FACE_CLOCKWISE;
        
        // No depth bias use for now
        info.depthBiasEnable = VK_FALSE;
        info.depthBiasConstantFactor = 0.0f;
        info.depthBiasClamp = 0.0f; 
        info.depthBiasSlopeFactor = 0.0f; 
    }

    VkPipelineRasterizationStateCreateInfo info;
};

} // namespace root