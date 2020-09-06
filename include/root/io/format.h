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

#include <cstring>

namespace root {

template<typename T> 
auto strlen(const T& object) -> u64;

inline auto strlen(const char* str) -> u64 {
    return ::strlen(str);
}

template<typename T>
auto to_string(buffer_writer& dst, const T& object) -> void;

inline auto to_string(buffer_writer& dst, const char* object) -> void {
    dst.write(object, strlen(object));
}

class format {
public:
    explicit format(allocator* alloc = allocator::default_allocator())
    :   m_allocator(alloc) {}

    template<typename T>
    auto build_string(const T& object) -> string {
        u64 len = strlen(object);
        buffer buf(len+1, alignof(i8), m_allocator);
        buffer_stream stream(buf);
        buffer_writer writer(&stream);
        to_string(writer, object);
        to_string(writer, '\0');
        auto str = string(std::move(buf));
        return str;
    }

private:
    allocator*  m_allocator;
};

} // namespace root