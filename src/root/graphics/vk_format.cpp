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

#include <root/io/format.h>
#include <root/graphics/vk_format.h>

#include <vulkan/vulkan.h>

namespace root {

template<>
auto strlen<VkPhysicalDeviceType>(const VkPhysicalDeviceType& object, const string_view&) -> u64 {
    return strlen(to_string(object));
}

template<>
auto format_to<VkPhysicalDeviceType>(buffer_writer& dst, const VkPhysicalDeviceType& object, const string_view&) -> void {
    return format_to(dst, to_string(object));
}

template<>
auto strlen<VkPhysicalDeviceProperties>(const VkPhysicalDeviceProperties & object, const string_view&) -> u64 {
    constexpr u64 API_VERSION_STR_LEN = strlen("{ apiVersion: ");
    u64 api_ver_len = strlen(object.apiVersion);
    constexpr u64 DRIVER_VERSION_STR_LEN = strlen(" driverVersion: ");
    u64 driver_ver_len = strlen(object.driverVersion);
    constexpr u64 VENDOR_ID_STR_LEN = strlen(" vendorID: ");
    u64 vendor_id_len = strlen(object.vendorID);
    constexpr u64 DEVICE_TYPE_STR_LEN = strlen(" deviceType: ");
    u64 device_type_len = strlen(object.deviceType);
    constexpr u64 DEVICE_NAME_STR_LEN = strlen(" deviceName: ");
    u64 device_name_len = strlen(object.deviceName);
    constexpr u64 CLOSING_STR_LEN = strlen(" }");
    return API_VERSION_STR_LEN + api_ver_len + 
           DRIVER_VERSION_STR_LEN + driver_ver_len +
           VENDOR_ID_STR_LEN + vendor_id_len +
           DEVICE_TYPE_STR_LEN + device_type_len +
           DEVICE_NAME_STR_LEN + device_name_len +
           CLOSING_STR_LEN;
}

template<>
auto format_to<VkPhysicalDeviceProperties>(buffer_writer& dst, const VkPhysicalDeviceProperties & object, const string_view&) -> void {
    format_to(dst, "{ apiVersion: ");
    format_to(dst, object.apiVersion);
    format_to(dst, " driverVersion: ");
    format_to(dst, object.driverVersion);
    format_to(dst, " vendorID: ");
    format_to(dst, object.vendorID);
    format_to(dst, " deviceType: ");
    format_to(dst, object.deviceType);
    format_to(dst, " deviceName: ");
    format_to(dst, object.deviceName);
    format_to(dst, " }");
}

template<>
auto strlen<VkQueueFlagBits>(const VkQueueFlagBits& object, const string_view&) -> u64 {
    return strlen(to_string(object));
}

template<>
auto format_to<VkQueueFlagBits>(buffer_writer& dst, const VkQueueFlagBits& object, const string_view&) -> void {
    return format_to(dst, to_string(object));
}

struct VkQueueFlagWrapper {
    VkQueueFlagWrapper(const VkQueueFlags& v) : value(v){}
    VkQueueFlags value = 0;
};

template<>
auto strlen<VkQueueFlagWrapper>(const VkQueueFlagWrapper& object, const string_view&) -> u64 {
    u64 len = 0, num  = 0;
    if(object.value & VK_QUEUE_GRAPHICS_BIT) {
        num++; 
        len += strlen(to_string(VK_QUEUE_GRAPHICS_BIT));
    }
    if(object.value & VK_QUEUE_COMPUTE_BIT) {
        num++; 
        len += strlen(to_string(VK_QUEUE_COMPUTE_BIT));
    }
    if(object.value & VK_QUEUE_TRANSFER_BIT) {
        num++; 
        len += strlen(to_string(VK_QUEUE_TRANSFER_BIT));
    }
    if(object.value & VK_QUEUE_SPARSE_BINDING_BIT) {
        num++; 
        len += strlen(to_string(VK_QUEUE_SPARSE_BINDING_BIT));
    }
    if(object.value & VK_QUEUE_SPARSE_BINDING_BIT) {
        num++; 
        len += strlen(to_string(VK_QUEUE_SPARSE_BINDING_BIT));
    }
    return len + (num * strlen(" | "));
}

template<>
auto format_to<VkQueueFlagWrapper>(buffer_writer& dst, const VkQueueFlagWrapper& object, const string_view&) -> void {
    bool has_printed = false;
    for(u64 bit = 1; bit < (VK_QUEUE_SPARSE_BINDING_BIT << 1); bit = bit << 1) {
        if(object.value & bit) {
            if (has_printed) format_to(dst, " | ");
            has_printed = true;
            format_to(dst, static_cast<VkQueueFlagBits>(bit));
        }
    }
}

template<>
auto strlen<VkExtent3D>(const VkExtent3D& object, const string_view&) -> u64 {
    constexpr u64 OPENING_STR_LEN = strlen("{ ");
    constexpr u64 COMMA_STR_LEN = strlen(", ");
    constexpr u64 CLOSING_STR_LEN = strlen("{ ");
    return OPENING_STR_LEN + strlen(object.width) + COMMA_STR_LEN + strlen(object.height) + COMMA_STR_LEN + strlen(object.depth) + CLOSING_STR_LEN;
}

template<>
auto format_to<VkExtent3D>(buffer_writer& dst, const VkExtent3D& object, const string_view&) -> void {
    format_to(dst, "{ ");
    format_to(dst, object.width);
    format_to(dst, ", ");
    format_to(dst, object.height);
    format_to(dst, ", ");
    format_to(dst, object.depth);
    format_to(dst, " }");
}

template<>
auto strlen<VkQueueFamilyProperties>(const VkQueueFamilyProperties& object, const string_view&) -> u64 {
    constexpr u64 QUEUE_FLAGS_STR_LEN = strlen("{ queueFlags: ");
    u64 queue_flags_len = strlen(VkQueueFlagWrapper(object.queueFlags));
    constexpr u64 QUEUE_COUNT_STR_LEN = strlen("{ queueCount: ");
    u64 queue_count_len = strlen(object.queueCount);
    constexpr u64 TIMESTAMP_VALID_BITS_STR_LEN = strlen("{ timestampValidBits: ");
    u64 timestamp_valid_bits_len = strlen(object.timestampValidBits);
    constexpr u64 MIN_IMAGE_TRANSFER_GRANULARITY_STR_LEN = strlen("{ minImageTransferGranularity: ");
    u64 min_image_transfer_granularity_len = strlen(object.minImageTransferGranularity);
    constexpr u64 CLOSING_STR_LEN = strlen(" }");
    return QUEUE_FLAGS_STR_LEN + queue_flags_len + 
           QUEUE_COUNT_STR_LEN + queue_count_len +
           TIMESTAMP_VALID_BITS_STR_LEN + timestamp_valid_bits_len + 
           MIN_IMAGE_TRANSFER_GRANULARITY_STR_LEN + min_image_transfer_granularity_len + 
           CLOSING_STR_LEN;
}

template<>
auto format_to<VkQueueFamilyProperties>(buffer_writer& dst, const VkQueueFamilyProperties& object, const string_view&) -> void {
    format_to(dst, "{ queueFlags: ");
    format_to(dst, VkQueueFlagWrapper(object.queueFlags));
    format_to(dst, " queueCount: ");
    format_to(dst, object.queueCount);
    format_to(dst, " timestampValidBits: ");
    format_to(dst, object.timestampValidBits);
    format_to(dst, " minImageTransferGranularity: ");
    format_to(dst, object.minImageTransferGranularity);
    format_to(dst, " }");
}

// TODO: VkPhysicalDeviceLimits
// TODO: VkPhysicalDeviceSparseProperties


} // namespace root