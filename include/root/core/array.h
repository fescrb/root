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

#include <initializer_list>

#include <root/core/assert.h>
#include <root/memory/allocator.h>

namespace root {

template<typename T>
class array {
public:
    explicit inline array(const std::initializer_list<T>& init_l, allocator* alloc = allocator::default_allocator())
    :   m_length(init_l.size()), 
        m_allocator(alloc) {
        m_data = reinterpret_cast<T*>(alloc->malloc(sizeof(T) * init_l.size(), alignof(T)));
        T* data_iter = m_data;
        for(auto item = init_l.begin(); item != init_l.end(); item++, data_iter++) {
            *data_iter = *item;
        }
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

    ~array() {
        m_allocator->free(m_data, sizeof(T) * m_length, alignof(T));
    }

protected:
    T *m_data;
    u64 m_length;
    allocator* m_allocator;
};

} // namespace root