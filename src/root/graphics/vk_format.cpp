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
auto strlen<VkFormat>(const VkFormat& object, const string_view&) -> u64 {
    return strlen(to_string(object));
}

template<>
auto format_to<VkFormat>(buffer_writer& dst, const VkFormat& object, const string_view&) -> void {
    return format_to(dst, to_string(object));
}


template<>
auto strlen<VkPresentModeKHR>(const VkPresentModeKHR& object, const string_view&) -> u64 {
    return strlen(to_string(object));
}

template<>
auto format_to<VkPresentModeKHR>(buffer_writer& dst, const VkPresentModeKHR& object, const string_view&) -> void {
    return format_to(dst, to_string(object));
}

template<>
auto strlen<VkColorSpaceKHR>(const VkColorSpaceKHR& object, const string_view&) -> u64 {
    return strlen(to_string(object));
}

template<>
auto format_to<VkColorSpaceKHR>(buffer_writer& dst, const VkColorSpaceKHR& object, const string_view&) -> void {
    return format_to(dst, to_string(object));
}

template<>
auto strlen<VkResult>(const VkResult& object, const string_view&) -> u64 {
    return strlen(to_string(object));
}

template<>
auto format_to<VkResult>(buffer_writer& dst, const VkResult& object, const string_view&) -> void {
    return format_to(dst, to_string(object));
}

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

template<typename E, E first, E last> // TODO: can I ensure that E is enum?
struct VkFlagsWrapper {
    VkFlagsWrapper(const VkFlags& v) : value(v) {}
    VkFlags value;
};

template<typename E, E first, E last>
inline auto strlen(const VkFlagsWrapper<E,first,last>& object, const string_view& = string_view()) -> u64 {
    u64 len = 0, num  = 0;
    for(VkFlags bit = first; bit < (last << 1); bit = bit << 1) {
        if(object.value & bit) {
            num++;
            len += strlen(to_string(static_cast<E>(bit)));
        }
    }
    return len + ((num - 1)* strlen(" | "));
}

template<typename E, E first, E last>
inline auto format_to(buffer_writer& dst, const VkFlagsWrapper<E,first,last>& object, const string_view& = string_view()) -> void {
    bool has_printed = false;
    for(u64 bit = first; bit < (last << 1); bit = bit << 1) {
        if(object.value & bit) {
            if (has_printed) format_to(dst, " | ");
            has_printed = true;
            format_to(dst, to_string(static_cast<E>(bit)));
        }
    }
}

using VkQueueFlagWrapper = VkFlagsWrapper<VkQueueFlagBits, VK_QUEUE_GRAPHICS_BIT, VK_QUEUE_PROTECTED_BIT>;

using VkSurfaceTransformFlagWrapper = VkFlagsWrapper<VkSurfaceTransformFlagBitsKHR, VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR, VK_SURFACE_TRANSFORM_INHERIT_BIT_KHR>;

using VkCompositeAlphaFlagWrapper = VkFlagsWrapper<VkCompositeAlphaFlagBitsKHR, VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR, VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR>;

using VkImageUsageFlagWrapper = VkFlagsWrapper<VkImageUsageFlagBits, VK_IMAGE_USAGE_TRANSFER_SRC_BIT, VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT>;

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
auto strlen<VkExtent3D>(const VkExtent3D& object, const string_view&) -> u64 {
    constexpr u64 OPENING_STR_LEN = strlen("{ ");
    constexpr u64 COMMA_STR_LEN = strlen(", ");
    constexpr u64 CLOSING_STR_LEN = strlen("{ ");
    return OPENING_STR_LEN + strlen(object.width) + COMMA_STR_LEN + strlen(object.height) + COMMA_STR_LEN + strlen(object.depth) + CLOSING_STR_LEN;
}


template<>
auto strlen<VkExtent2D>(const VkExtent2D& object, const string_view&) -> u64 {
    constexpr u64 OPENING_STR_LEN = strlen("{ ");
    constexpr u64 COMMA_STR_LEN = strlen(", ");
    constexpr u64 CLOSING_STR_LEN = strlen("{ ");
    return OPENING_STR_LEN + strlen(object.width) + COMMA_STR_LEN + strlen(object.height) + CLOSING_STR_LEN;
}

template<>
auto format_to<VkExtent2D>(buffer_writer& dst, const VkExtent2D& object, const string_view&) -> void {
    format_to(dst, "{ ");
    format_to(dst, object.width);
    format_to(dst, ", ");
    format_to(dst, object.height);
    format_to(dst, " }");
}

template<>
auto strlen<VkQueueFamilyProperties>(const VkQueueFamilyProperties& object, const string_view&) -> u64 {
    constexpr u64 QUEUE_FLAGS_STR_LEN = strlen("{ queueFlags: ");
    u64 queue_flags_len = strlen(VkQueueFlagWrapper(object.queueFlags));
    constexpr u64 QUEUE_COUNT_STR_LEN = strlen(" queueCount: ");
    u64 queue_count_len = strlen(object.queueCount);
    constexpr u64 TIMESTAMP_VALID_BITS_STR_LEN = strlen(" timestampValidBits: ");
    u64 timestamp_valid_bits_len = strlen(object.timestampValidBits);
    constexpr u64 MIN_IMAGE_TRANSFER_GRANULARITY_STR_LEN = strlen(" minImageTransferGranularity: ");
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

template<>
auto strlen<VkSurfaceCapabilitiesKHR>(const VkSurfaceCapabilitiesKHR& object, const string_view&) -> u64 {
    constexpr u64 MIN_IMAGE_COUNT_STR_LEN = strlen("{ minImageCount: ");
    u64 min_image_count_len = strlen(object.minImageCount);
    constexpr u64 MAX_IMAGE_COUNT_STR_LEN = strlen(" maxImageCount: ");
    u64 max_image_count_len = strlen(object.maxImageCount);
    constexpr u64 CURRENT_EXTENT_STR_LEN = strlen(" currentExtent: ");
    u64 current_extent_len = strlen(object.currentExtent);
    constexpr u64 MIN_IMAGE_EXTENT_STR_LEN = strlen(" minImageExtent: ");
    u64 min_image_extent_len = strlen(object.minImageExtent);
    constexpr u64 MAX_IMAGE_EXTENT_STR_LEN = strlen(" maxImageExtent: ");
    u64 max_image_extent_len = strlen(object.maxImageExtent);
    constexpr u64 MAX_IMAGE_ARRAY_LAYERS_STR_LEN = strlen(" maxImageArrayLayers: ");
    u64 max_image_array_layers_len = strlen(object.maxImageArrayLayers);
    constexpr u64 SUPPORTED_TRANSFORMS_STR_LEN = strlen(" supportedTransforms: ");
    u64 supported_transforms_len = strlen(VkSurfaceTransformFlagWrapper(object.supportedTransforms));
    constexpr u64 CURRENT_TRANSFORM_STR_LEN = strlen(" currentTransform: ");
    u64 current_transform_len = strlen(to_string(object.currentTransform));
    constexpr u64 SUPPORTED_COMPOSITE_ALPHA_STR_LEN = strlen(" supportedCompositeAlpha: ");
    u64 supported_composite_alpha_len = strlen(VkCompositeAlphaFlagWrapper(object.supportedCompositeAlpha));
    constexpr u64 SUPPORTED_USAGE_FLAGS_STR_LEN = strlen(" supportedUsageFlags: ");
    u64 supported_usage_flags_len = strlen(VkImageUsageFlagWrapper(object.supportedUsageFlags));
    constexpr u64 CLOSING_STR_LEN = strlen(" }");
    return MIN_IMAGE_COUNT_STR_LEN + min_image_count_len + 
           MAX_IMAGE_COUNT_STR_LEN + max_image_count_len +
           CURRENT_EXTENT_STR_LEN + current_extent_len + 
           MIN_IMAGE_EXTENT_STR_LEN + min_image_extent_len + 
           MAX_IMAGE_EXTENT_STR_LEN + max_image_extent_len + 
           MAX_IMAGE_ARRAY_LAYERS_STR_LEN + max_image_array_layers_len +
           SUPPORTED_TRANSFORMS_STR_LEN + supported_transforms_len +
           CURRENT_TRANSFORM_STR_LEN + current_transform_len +
           SUPPORTED_COMPOSITE_ALPHA_STR_LEN + supported_composite_alpha_len +
           SUPPORTED_USAGE_FLAGS_STR_LEN + supported_usage_flags_len +
           CLOSING_STR_LEN;
}

template<>
auto format_to<VkSurfaceCapabilitiesKHR>(buffer_writer& dst, const VkSurfaceCapabilitiesKHR& object, const string_view&) -> void {
    format_to(dst, "{ minImageCount: ");
    format_to(dst, object.minImageCount);
    format_to(dst, " maxImageCount: ");
    format_to(dst, object.maxImageCount);
    format_to(dst, " currentExtent: ");
    format_to(dst, object.currentExtent);
    format_to(dst, " minImageExtent: ");
    format_to(dst, object.minImageExtent);
    format_to(dst, " maxImageExtent: ");
    format_to(dst, object.maxImageExtent);
    format_to(dst, " maxImageArrayLayers: ");
    format_to(dst, object.maxImageArrayLayers);
    format_to(dst, " supportedTransforms: ");
    format_to(dst, VkSurfaceTransformFlagWrapper(object.supportedTransforms));
    format_to(dst, " currentTransform: ");
    format_to(dst, to_string(object.currentTransform));
    format_to(dst, " supportedCompositeAlpha: ");
    format_to(dst, VkCompositeAlphaFlagWrapper(object.supportedCompositeAlpha));
    format_to(dst, " supportedUsageFlags: ");
    format_to(dst, VkImageUsageFlagWrapper(object.supportedUsageFlags));
    format_to(dst, " }");
}

template<>
auto strlen<VkSurfaceFormatKHR>(const VkSurfaceFormatKHR& object, const string_view&) -> u64 {
    constexpr u64 FORMAT_STR_LEN = strlen("{ format: ");
    u64 format_len = strlen(object.format);
    constexpr u64 COLOR_SPACE_STR_LEN = strlen(" colorSpace: ");
    u64 color_space_len = strlen(object.colorSpace);
    constexpr u64 CLOSING_STR_LEN = strlen(" }");
    return FORMAT_STR_LEN + format_len +
           COLOR_SPACE_STR_LEN + color_space_len +
           CLOSING_STR_LEN;
}

template<>
auto format_to<VkSurfaceFormatKHR>(buffer_writer& dst, const VkSurfaceFormatKHR& object, const string_view&) -> void {
    format_to(dst, "{ format: ");
    format_to(dst, object.format);
    format_to(dst, " colorSpace: ");
    format_to(dst, object.colorSpace);
    format_to(dst, " }");
}

template<>
auto strlen<VkLayerProperties>(const VkLayerProperties& object, const string_view&) -> u64 {
    constexpr u64 LAYER_NAME_STR_LEN = strlen("{ layerName: ");
    u64 layer_name_len = strlen(object.layerName);
    constexpr u64 SPEC_VERSION_STR_LEN = strlen(" specVersion: ");
    u64 spec_version_len = strlen(object.specVersion);
    constexpr u64 IMPLEMENTATION_VERSION_STR_LEN = strlen(" implementationVersion: ");
    u64 implementation_version_len = strlen(object.implementationVersion);
    constexpr u64 DESCRIPTION_STR_LEN = strlen(" description: ");
    u64 description_len = strlen(object.description);
    constexpr u64 CLOSING_STR_LEN = strlen(" }");
    return LAYER_NAME_STR_LEN + layer_name_len +
           SPEC_VERSION_STR_LEN + spec_version_len +
           IMPLEMENTATION_VERSION_STR_LEN + implementation_version_len +
           DESCRIPTION_STR_LEN + description_len +
           CLOSING_STR_LEN;
}

template<>
auto format_to<VkLayerProperties>(buffer_writer& dst, const VkLayerProperties& object, const string_view&) -> void {
    format_to(dst, "{ layerName: ");
    format_to(dst, object.layerName);
    format_to(dst, " specVersion: ");
    format_to(dst, object.specVersion);
    format_to(dst, " implementationVersion: ");
    format_to(dst, object.implementationVersion);
    format_to(dst, " description: ");
    format_to(dst, object.description);
    format_to(dst, " }");
}

// TODO: VkPhysicalDeviceLimits
// TODO: VkPhysicalDeviceSparseProperties


} // namespace root