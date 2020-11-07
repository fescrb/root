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

#include <root/core/array.h>
#include <root/core/primitives.h>
#include <root/core/string_slice.h>

#include <cstring>

namespace root {

class string : public array<i8> {
public:
    explicit inline string(const char* str, allocator* alloc = allocator::default_allocator()) 
    :   array(strlen(str), alloc) {
        memcpy(m_data, str, m_length * sizeof(i8));
    }

    explicit inline string(const u64& length, allocator* alloc = allocator::default_allocator()) 
    : array(length, alloc) {}

    string(const string&) = delete;
    inline string(string&& other) 
    : array(std::move(other)) {}

    inline string(buffer&& b) 
    :   array(std::move(b)) {}

    template<typename I>
    inline auto offset(const I& off) const -> string_slice {
        root_assert(off < size());
        return string_slice(m_data, static_cast<u64>(off), size());
    } 

    template<typename I1, typename I2>
    inline auto range(const I1& start, const I2& end) const -> string_slice {
        root_assert(start < size());
        root_assert(end <= size());
        return string_slice(m_data, static_cast<u64>(start), static_cast<u64>(end));
    }   

    template<typename I>
    inline auto limit(const I& new_limit) const -> string_slice {
        root_assert(new_limit < size());
        return string_slice(m_data, 0, new_limit);
    }

    template<typename I>
    inline auto operator+(const I& extra_offset) const -> string_slice {
        return offset(extra_offset);
    }

    inline operator string_view&() const {
        return string_view(m_data, 0, m_length);
    }

    inline operator string_slice&() {
        return string_slice(m_data, 0, m_length);
    }
};

} // namespace root