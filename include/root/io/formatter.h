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

inline auto format_to(buffer_writer& dst, const char* object, const string_view& = string_view()) -> void {
    dst.write(object, strlen(object));
}

template<typename... Args>
constexpr auto strlen(const format_string& fmt, Args... args) -> u64 {
    return 0;
}

template<typename T, typename... Args>
constexpr auto strlen(const format_string& fmt, const T& object, Args... args) -> u64 {
    auto placeholder_end = find(fmt.begin(), fmt.end(), '}');
    root_assert(placeholder_end != fmt.end());
    u64 t_size = strlen(string_view(fmt.begin(), ++placeholder_end), object);
    return t_size + strlen(string_view(placeholder_end, fmt.end(), args...));
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

template<typename... Args>
inline auto format_to(buffer_writer& dst, const format_string& fmt, Args... args) -> void {}

template<typename T, typename... Args>
inline auto format_to(buffer_writer& dst, const format_string& fmt, const T& object, Args... args) -> void {
    auto placeholder_end = find(fmt.begin(), fmt.end(), '}');
    root_assert(placeholder_end != fmt.end());
    format_to(dst, string_view(fmt.begin(), ++placeholder_end), object);
    format_to(dst, string_view(placeholder_end, fmt.end(), args...));
}

template<typename T>
inline auto format_to(buffer_writer& dst, const format_string& fmt, const T& object) -> void {
    auto placeholder_start = find(fmt.begin(), fmt.end(), '{');
    auto placeholder_end = find(placeholder_start, fmt.end(), '}');
    root_assert(placeholder_end != fmt.end());
    string_view format_args(++placeholder_start, placeholder_end);
    format_to(dst, string_view(fmt.begin(), --placeholder_start));
    format_to(dst, object, format_args);
    format_to(dst, string_view(++placeholder_end, fmt.end()));
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