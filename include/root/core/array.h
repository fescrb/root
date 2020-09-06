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

#include <utility>
#include <initializer_list>

#include <root/core/assert.h>
#include <root/core/buffer.h>
#include <root/memory/allocator.h>

namespace root {

template<typename T>
class array {
public:
    inline array()
    :   m_length(0),
        m_allocator(0),
        m_data(0) {}

    explicit inline array(const std::initializer_list<T>& init_l, allocator* alloc = allocator::default_allocator())
    :   m_length(init_l.size()), 
        m_allocator(alloc) {
        m_data = reinterpret_cast<T*>(alloc->malloc(sizeof(T) * init_l.size(), alignof(T)));
        T* data_iter = m_data;
        for(auto item = init_l.begin(); item != init_l.end(); item++, data_iter++) {
            *data_iter = *item;
        }
    }

    inline array(buffer&& b) 
    :   m_length(b.m_byte_size/sizeof(T)),
        m_allocator(std::move(b.m_allocator)),
        m_data(reinterpret_cast<T*>(b.m_data)) {
        root_assert(b.m_alignment == alignof(T));
        b.clear();
    }

    array(const array&) = delete;
    inline array(array&& other)
    :   m_length(std::move(other.m_length)),
        m_allocator(std::move(other.m_allocator)),
        m_data(std::move(other.m_data)) {
        other.clear();
    }

    auto operator=(const array&) -> array& = delete;
    inline auto operator=(array&& other) -> array& {
        m_length = std::move(other.m_length);
        m_allocator = std::move(other.m_allocator);
        m_data = std::move(other.m_data);
        other.clear();
        return *this;
    }

    explicit inline array(const u64& length, allocator* alloc = allocator::default_allocator())
    :   m_length(length), 
        m_allocator(alloc) {
        m_data = reinterpret_cast<T*>(alloc->malloc(sizeof(T) * length, alignof(T)));
    }

    inline auto operator[](const u64& index) -> T& {
        root_assert(i < m_length);
        return m_data[index];
    }

    inline auto operator[](const u64& index) const -> T {
        root_assert(i < m_length);
        return m_data[index];
    }

    inline auto length() const -> u64 {
        return m_length;
    }

    inline auto raw() const -> T* {
        return m_data;
    }

    inline operator bool() const {
        return m_data && m_allocator && m_length;
    }

    inline operator T*() const {
        return raw();
    }

    inline operator void*() const {
        return reinterpret_cast<void*>(raw());
    }

    ~array() {
        root_assert((m_allocator && m_data && m_length) ^ (!m_allocator && !m_data && !m_length));
        if(m_allocator && m_data && m_length)
            m_allocator->free(m_data, sizeof(T) * m_length, alignof(T));
    }

protected:
    T *m_data;
    u64 m_length;
    allocator* m_allocator;

    inline auto clear() -> void {
        m_data = nullptr;
        m_length = 0;
        m_allocator = nullptr;
    }
};

} // namespace root