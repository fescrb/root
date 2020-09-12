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


} // namespace root