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

class buffer_view {
public:
    inline buffer_view() { clear(); } // \TODO unit test

    inline buffer_view(void* b, const u64& o, const u64& l) 
    :  m_buffer(b), m_offset(o), m_limit(l) {}

    inline buffer_view(buffer_view&& other) 
    :   m_buffer(std::move(other.m_buffer)),
        m_offset(std::move(other.m_offset)),
        m_limit(std::move(other.m_limit)) {}

    inline buffer_view(const buffer_view& other)
    :   m_buffer(other.m_buffer),
        m_offset(other.m_offset),
        m_limit(other.m_limit) {
    }

    auto operator=(const buffer_view& other) -> buffer_view& {
        m_buffer = other.m_buffer;
        m_offset = other.m_offset;
        m_limit = other.m_limit;
        return *this;
    }

    auto operator=(buffer_view&& other) -> buffer_view& {
        m_buffer = std::move(other.m_buffer);
        m_offset = std::move(other.m_offset);
        m_limit = std::move(other.m_limit);
        return *this;
    }

    inline auto size() const -> u64 {
        return m_limit - m_offset;
    }

    inline auto data() const -> const void* {
        return reinterpret_cast<void*>(reinterpret_cast<u8*>(m_buffer) + m_offset);
    }

    inline auto data() -> void* {
        return reinterpret_cast<void*>(reinterpret_cast<u8*>(m_buffer) + m_offset);
    }

    inline operator const void*() const {
        return data();
    }

    inline operator void*() {
        return data();
    }

    inline operator bool() const {
        return m_buffer;
    }
    
    template<typename T>
    inline auto offset(const T& extra_offset) const -> buffer_view {
        root_assert(m_offset + extra_offset < size());
        return buffer_view(m_buffer, static_cast<u64>(m_offset + extra_offset), m_limit);
    } 

    template<typename T1, typename T2>
    inline auto range(const T1& start, const T2& end) const -> buffer_view {
        root_assert(start + m_offset < size());
        root_assert(end + m_offset < size());
        return buffer_view(m_buffer, static_cast<u64>(m_offset+start), static_cast<u64>(m_offset+end));
    }   

    template<typename T>
    inline auto limit(const T& new_limit) const -> buffer_view {
        root_assert(new_limit < size());
        return buffer_view(m_buffer, m_offset, new_limit);
    }

    template<typename T>
    inline auto operator+(const T& extra_offset) const -> buffer_view {
        return offset(extra_offset);
    }

    // TODO unit test
    inline auto clear() -> void {
        m_buffer = nullptr; 
        m_offset = 0;
        m_limit = 0;
    }

private:
    void * m_buffer;
    u64 m_offset;
    u64 m_limit;
};
} // namespace root