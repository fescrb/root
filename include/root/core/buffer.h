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

#include <utility>

namespace root {

inline auto memcpy(void* dst, const void* source, const u64 bytes) -> void {
    for(int i = 0; i < bytes; i++) {
        reinterpret_cast<u8*>(dst)[i] = reinterpret_cast<const u8*>(source)[i];
    }
}

class buffer {
public:
    inline buffer()
    :   m_data(nullptr),
        m_byte_size(0),
        m_alloc(nullptr) {}

    explicit buffer(const u64& byte_size,  allocator* alloc = allocator::default_allocator())
    :   m_byte_size(byte_size),
        m_alloc(alloc) {
        root_assert(byte_size != 0);
        m_data = reinterpret_cast<u8*>(alloc->malloc(byte_size, ALIGNMENT));
    }

    buffer(const buffer& other) = delete;
    
    inline buffer(buffer&& other)
    :   m_data(std::move(other.m_data)),
        m_byte_size(std::move(other.m_byte_size)),
        m_alloc(std::move(other.m_alloc)) {}

    inline auto raw() const -> void* {
        return reinterpret_cast<void*>(m_data);
    }

    inline auto size() const -> u64 {
        return m_byte_size;
    }

    inline auto write(const off64_t dst_offset, const buffer& src, const off64_t src_offset, const u64 bytes) -> void {
        root_assert(src_offset+bytes < src.m_byte_size);
        write(dst_offset, src.raw(), src_offset, bytes);
    }

    inline auto write(const off64_t dst_offset, const void* src, const off64_t src_offset, const u64 bytes) -> void {
        root_assert(dst_offset+bytes < m_byte_size);
        memcpy(m_data+dst_offset, src+src_offset, bytes);
    }

    inline auto abandoned() const -> bool {
        return !m_data || !m_byte_size || !m_alloc; 
    }

    ~buffer() {
        root_assert((m_data && m_alloc && m_byte_size) ^ (!m_data && !m_alloc && !m_byte_size)); 
        if(m_data && m_alloc && m_byte_size) {
            m_alloc->free(m_data, m_byte_size, ALIGNMENT);
        }
    }

private:
    static constexpr u64 ALIGNMENT = 0; // TODO should probably be a conservative aligment

    u8 *m_data;
    u64 m_byte_size;
    allocator* m_alloc;
};

} // namespace root