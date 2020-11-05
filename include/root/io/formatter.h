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

#include <root/io/writer.h>
#include <root/memory/allocator.h>
#include <root/core/string.h>
#include <root/io/private/format_string.h>

#include <cstring>

namespace root {

template<typename T> 
auto strlen(const T& object, const string_view& format_args = string_view()) -> u64;

template<typename T>
auto format_to(buffer_writer& dst, const T& object, const string_view& format_args = string_view()) -> void;

template<typename T> 
inline auto strlen(T* const& object, const string_view& format_args = string_view()) -> u64 {
    return strlen(reinterpret_cast<u64>(object), format_args);
}

template<typename T> 
inline auto format_to(buffer_writer& dst, T* const& object, const string_view& format_args = string_view()) -> void {
    return format_to(dst, reinterpret_cast<u64>(object), format_args);
}

template<int N> 
inline auto strlen(char const (&object)[N], const string_view& = string_view()) -> u64 {
    const u64 len = strlen(reinterpret_cast<const char*>(&object));
    return len < (N - 1) ? len : N - 1; 
}

template<int N> 
inline auto format_to(buffer_writer& dst, char const (&object)[N], const string_view& = string_view()) -> void {
    const u64 len = strlen(reinterpret_cast<const char*>(&object));
    dst.write(object, len < (N - 1) ? len : N - 1);
}

template<> 
inline auto strlen<const char>(const char* const& object, const string_view&) -> u64 {
    return ::strlen(object);
}

template<> 
inline auto format_to<const char>(buffer_writer& dst, const char* const& object, const string_view&) -> void {
    dst.write(object, strlen(object));
}

template<> 
inline auto strlen<char>(char* const& object, const string_view&) -> u64 {
    return ::strlen(object);
}

template<> 
inline auto format_to<char>(buffer_writer& dst, char* const& object, const string_view&) -> void {
    dst.write(object, strlen(object));
}

template<>
inline auto strlen<string_view>(const string_view& object, const string_view& format_args) -> u64 {
    return object.size();
}

template<typename... Args>
constexpr auto strlen(const format_string& fmt, Args... args) -> u64 {
    return 0;
}

template<typename T, typename... Args>
constexpr auto strlen(const format_string& fmt, const T& object, Args... args) -> u64 {
    auto placeholder_end = find(fmt.begin(), fmt.end(), '}');
    root_assert(placeholder_end != fmt.end());
    u64 t_size = strlen<T>(string_view(fmt.begin(), ++placeholder_end), object);
    return t_size + strlen<Args...>(string_view(placeholder_end, fmt.end()), args...);
}

template<typename T>
constexpr auto strlen(const format_string& fmt, const T& object) -> u64 {
    auto placeholder_start = find(fmt.begin(), fmt.end(), '{');
    auto placeholder_end = find(placeholder_start, fmt.end(), '}');
    root_assert(placeholder_end != fmt.end());
    u64 pre_placeholder_size = placeholder_start - fmt.begin();
    u64 post_placeholder_size = (fmt.end() - placeholder_end) - 1; // Get rid of }
    string_view format_args(++placeholder_start, placeholder_end);
    return pre_placeholder_size + post_placeholder_size + strlen(object, format_args);
}

template<>
constexpr auto strlen<>(const format_string& fmt) -> u64 {
    return fmt.size();
}

template<>
constexpr auto strlen<char const*>(const format_string& fmt, char const* const& object) -> u64 {
    return strlen<string_view>(fmt, string_view(object));
}

template<typename... Args>
inline auto format_to(buffer_writer& dst, const format_string& fmt, Args... args) -> void {}

template<typename T, typename... Args>
inline auto format_to(buffer_writer& dst, const format_string& fmt, const T& object, Args... args) -> void {
    auto placeholder_end = find(fmt.begin(), fmt.end(), '}');
    root_assert(placeholder_end != fmt.end());
    format_to<T>(dst, string_view(fmt.begin(), ++placeholder_end), object);
    format_to<Args...>(dst, string_view(placeholder_end, fmt.end()), args...);
}

template<typename T>
inline auto format_to(buffer_writer& dst, const format_string& fmt, const T& object) -> void {
    auto placeholder_start = find(fmt.begin(), fmt.end(), '{');
    auto placeholder_end = find(placeholder_start, fmt.end(), '}');
    root_assert(placeholder_end != fmt.end());
    format_to(dst, string_view(fmt.begin(), placeholder_start));
    string_view format_args(++placeholder_start, placeholder_end);
    format_to(dst, object, format_args);
    format_to(dst, string_view(++placeholder_end, fmt.end()));
}

template<>
inline auto format_to<>(buffer_writer& dst,const format_string& fmt) -> void {
    if(fmt.size()) dst.write(fmt.data(), fmt.size());
}

class formatter {
public:
    explicit formatter(allocator* alloc = allocator::default_allocator())
    :   m_allocator(alloc) {}

    template<typename T>
    auto to_string(const T& object) -> string {
        u64 len = strlen(object);
        buffer buf(len+1, alignof(i8), m_allocator);
        buffer_stream stream(buf);
        buffer_writer writer(&stream);
        format_to(writer, object);
        format_to(writer, '\0');
        auto str = string(std::move(buf));
        return str;
    }

    template<typename... Args>
    auto format(const format_string& fmt, Args... args) -> string {
        u64 len = strlen(fmt, args...);
        buffer buf(len+1, alignof(i8), m_allocator);
        buffer_stream stream(buf);
        buffer_writer writer(&stream);
        format_to(writer, fmt, args...);
        format_to(writer, '\0');
        auto str = string(std::move(buf));
        return str;
    }

protected:
    allocator*  m_allocator;
};

} // namespace root