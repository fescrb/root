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
#include <root/core/array_slice.h>

namespace root {

template<typename T>
class array {
public:
    using element_type = T;

    constexpr array() noexcept
    :   m_length(0),
        m_allocator(0),
        m_data(0) {}

    explicit inline array(const std::initializer_list<T>& init_l, allocator* alloc = allocator::get_default())
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

    explicit inline array(const u64& length, allocator* alloc = allocator::get_default())
    :   m_length(length), 
        m_allocator(alloc) {
        m_data = reinterpret_cast<T*>(alloc->malloc(sizeof(T) * length, alignof(T)));
    }

    template<typename I, typename = std::enable_if_t<std::is_integral_v<I>>>
    inline auto operator[](const I& index) const -> std::add_const_t<T>& {
        root_assert(index < m_length);
        return m_data[index];
    }

    template<typename I, typename = std::enable_if_t<std::is_integral_v<I>>>
    inline auto operator[](const I& index) -> T& {
        root_assert(index < m_length);
        return m_data[index];
    }

    inline auto size() const -> u64 {
        return m_length;
    }

    
    inline auto data() const -> const T* {
        return m_data;
    }

    inline auto data() -> T* {
        return m_data;
    }

    inline operator const T*() const {
        return data();
    }

    inline operator T*() {
        return data();
    }

    inline operator array_slice<const T>() const {
        return array_slice<const T>(m_data, 0, m_length);
    }

    inline operator array_slice<T>() {
        return array_slice<T>(m_data, 0, m_length);
    }

    ~array() {
        root_assert((m_allocator && m_data && m_length) ^ (!m_allocator && !m_data && !m_length));
        if(m_allocator && m_data && m_length)
            m_allocator->free(m_data);
    }

    template<typename I>
    inline auto offset(const I& off) const -> array_slice<T> {
        root_assert(off < size());
        return array_slice<T>(m_data, static_cast<u64>(off), size());
    } 

    template<typename I1, typename I2>
    inline auto range(const I1& start, const I2& end) const -> array_slice<T> {
        root_assert(start < size());
        root_assert(end <= size());
        return array_slice<T>(m_data, static_cast<u64>(start), static_cast<u64>(end));
    }   

    template<typename I>
    inline auto limit(const I& new_limit) const -> array_slice<T> {
        root_assert(new_limit < size());
        return array_slice<T>(m_data, 0, new_limit);
    }

    template<typename I>
    inline auto operator+(const I& extra_offset) const -> array_slice<T> {
        return offset(extra_offset);
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