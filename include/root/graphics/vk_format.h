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

inline constexpr auto to_string(const VkPhysicalDeviceType& type) -> const char*{
    switch(type) {
        case VK_PHYSICAL_DEVICE_TYPE_OTHER:
            return "VK_PHYSICAL_DEVICE_TYPE_OTHER";
        case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
            return "VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU";
        case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
            return "VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU";
        case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
            return "VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU";
        case VK_PHYSICAL_DEVICE_TYPE_CPU:
            return "VK_PHYSICAL_DEVICE_TYPE_CPU";
        default:
            return nullptr;
    }
}

inline constexpr auto to_string(const VkQueueFlagBits& bit) -> const char*{
    switch(bit) {
        case VK_QUEUE_GRAPHICS_BIT:
            return "VK_QUEUE_GRAPHICS_BIT";
        case VK_QUEUE_COMPUTE_BIT:
            return "VK_QUEUE_COMPUTE_BIT";
        case VK_QUEUE_TRANSFER_BIT:
            return "VK_QUEUE_TRANSFER_BIT";
        case VK_QUEUE_SPARSE_BINDING_BIT:
            return "VK_QUEUE_SPARSE_BINDING_BIT";
        case VK_QUEUE_PROTECTED_BIT:
            return "VK_QUEUE_PROTECTED_BIT ";
        default:
            return nullptr;
    }
}

inline constexpr auto to_string(const VkSurfaceTransformFlagBitsKHR& bit) -> const char*{
    switch(bit) {
        case VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR:
            return "VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR";
        case VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR:
            return "VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR";
        case VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR:
            return "VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR";
        case VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR:
            return "VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR";
        case VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_BIT_KHR:
            return "VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_BIT_KHR";
        case VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_90_BIT_KHR:
            return "VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_90_BIT_KHR";
        case VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_180_BIT_KHR:
            return "VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_180_BIT_KHR";
        case VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_270_BIT_KHR:
            return "VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_270_BIT_KHR";
        case VK_SURFACE_TRANSFORM_INHERIT_BIT_KHR:
            return "VK_SURFACE_TRANSFORM_INHERIT_BIT_KHR";
        default:
            return nullptr;
    }
}

} // namespace root