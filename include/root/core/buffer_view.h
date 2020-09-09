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

#include <root/core/primitives.h>
#include <root/core/assert.h>

#include <utility>
#include <cstring>

namespace root {

struct buffer_view {
    inline buffer_view(void* b, const u64& o, const u64& l) 
    :  buffer(b), offset(o), cutoff(l) {}

    inline buffer_view(buffer_view&& other) 
    :   buffer(std::move(other.buffer)),
        offset(std::move(other.offset)),
        cutoff(std::move(other.cutoff)) {}

    inline buffer_view(const buffer_view& other)
    :   buffer(other.buffer),
        offset(other.offset),
        cutoff(other.cutoff) {}

    auto operator=(const buffer_view&) -> buffer_view& = delete;
    auto operator=(buffer_view&&) -> buffer_view& = delete;

    inline auto size() const -> u64 {
        return cutoff - offset;
    }

    inline auto data() const -> void* {
        return reinterpret_cast<void*>(reinterpret_cast<u8*>(buffer) + offset);
    }

    inline operator const void*() const {
        return data();
    }

    inline operator void*() {
        return data();
    }

    inline operator bool() const {
        return data();
    }
    
    template<typename T>
    inline auto at(const T& extra_offset) const -> buffer_view {
        root_assert(offset + extra_offset < size());
        return buffer_view(buffer, static_cast<u64>(offset + extra_offset), cutoff);
    } 

    template<typename T1, typename T2>
    inline auto range(const T1& start, const T2& end) const -> buffer_view {
        root_assert(start + offset < size());
        root_assert(end + offset < size());
        return buffer_view(buffer, static_cast<u64>(offset+start), static_cast<u64>(offset+end));
    }   

    template<typename T>
    inline auto limit(const T& new_limit) const -> buffer_view {
        root_assert(new_limit < size());
        return buffer_view(buffer, offset, new_limit);
    }

    template<typename T>
    inline auto operator+(const T& extra_offset) const -> buffer_view {
        return at(extra_offset);
    }

    void * const buffer;
    const u64 offset;
    const u64 cutoff;
};
} // namespace root