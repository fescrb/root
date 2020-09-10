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

#include <root/memory/allocator.h>
#include <root/core/primitives.h>
#include <root/core/assert.h>
#include <root/core/buffer_view.h>

#include <utility>
#include <cstring>

namespace root {

class buffer {
public:
    inline buffer()
    :   m_data(nullptr),
        m_byte_size(0),
        m_allocator(nullptr) {}

    explicit buffer(const u64& byte_size, const u64& alignment = 1, allocator* alloc = allocator::default_allocator())
    :   m_byte_size(byte_size),
        m_allocator(alloc),
        m_alignment(alignment) {
        root_assert(byte_size != 0);
        m_data = reinterpret_cast<u8*>(alloc->malloc(byte_size, alignment));
    }

    buffer(const buffer& other) = delete;
    inline buffer(buffer&& other)
    :   m_data(std::move(other.m_data)),
        m_byte_size(std::move(other.m_byte_size)),
        m_alignment(std::move(other.m_alignment)),
        m_allocator(std::move(other.m_allocator)) {
        other.clear();
    }

    inline auto operator=(const buffer& other) -> buffer& = delete;
    inline auto operator=(buffer&& other) -> buffer&{
        m_data = std::move(other.m_data);
        m_byte_size = std::move(other.m_byte_size);
        m_alignment = std::move(other.m_alignment);
        m_allocator = std::move(other.m_allocator);
        other.clear();
        return *this;
    }

    inline auto data() const -> void* {
        return reinterpret_cast<void*>(m_data);
    }

    inline auto size() const -> u64 {
        return m_byte_size;
    }

    // TODO: write a named function equivalent
    inline operator bool() const {
        return m_data && m_byte_size && m_allocator; 
    }

    inline operator void*() const {
        return data();
    }

    ~buffer() {
        root_assert((m_data && m_allocator && m_byte_size) ^ (!m_data && !m_allocator && !m_byte_size)); 
        if(m_data && m_allocator && m_byte_size) {
            m_allocator->free(m_data, m_byte_size, m_alignment);
        }
        m_data = nullptr;
        m_allocator = nullptr;
        m_byte_size = 0;
        m_alignment = 0;
    }

    template<typename T>
    inline auto offset(const T& offset) const -> buffer_view {
        root_assert(offset < m_byte_size);
        return buffer_view(reinterpret_cast<void*>(m_data), static_cast<u64>(offset), m_byte_size);
    } 

    // TODO ensure that T is unsigned
    template<typename T>
    inline auto operator+(const T& offset) const -> buffer_view {
        return buffer::offset(offset);
    }

    template<typename T1, typename T2>
    inline auto range(const T1& start, const T2& end) const -> buffer_view {
        root_assert(start < m_byte_size);
        root_assert(end < m_byte_size);
        return buffer_view(reinterpret_cast<void*>(m_data), static_cast<u64>(start), static_cast<u64>(end));
    }

    template<typename T>
    inline auto limit(const T& size) const -> buffer_view {
        root_assert(size < m_byte_size);
        return buffer_view(reinterpret_cast<void*>(m_data), static_cast<u64>(0), static_cast<u64>(size));
    }

    inline operator buffer_view() const {
        return buffer_view(reinterpret_cast<void*>(m_data), static_cast<u64>(0), m_byte_size);
    }

private:
    u8 *m_data;
    u64 m_byte_size;
    u64 m_alignment;
    allocator* m_allocator;

    template<typename T>
    friend class array;

    inline auto clear() -> void {
        m_data = nullptr;
        m_byte_size = 0;
        m_alignment = 0;
        m_allocator = nullptr;
    }
};
} // namespace root