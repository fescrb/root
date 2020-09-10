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

namespace root {

template <typename T>
class array_view {
public:
    inline array_view() { clear(); } 

    inline array_view(T* data, const u64& first, const u64& last)
    :   m_data(data), m_first(first), m_last(last) {}

    inline array_view(array_view&& other) 
    :   m_data(std::move(other.m_data)),
        m_first(std::move(other.m_first)),
        m_last(std::move(other.m_last)) {}

    inline array_view(const array_view& other)
    :   m_data(other.m_data),
        m_first(other.m_first),
        m_last(other.m_last) {
    }

    auto operator=(const array_view& other) -> array_view& {
        m_data = other.m_data;
        m_first = other.m_first;
        m_last = other.m_last;
        return *this;
    }

    auto operator=(array_view&& other) -> array_view& {
        m_data = std::move(other.m_data);
        m_first = std::move(other.m_first);
        m_last = std::move(other.m_last);
        return *this;
    }

    inline auto clear() noexcept -> void {
        m_data = nullptr;
        m_first = 0;
        m_last = 0;
    } 

    inline auto size() const -> u64 {
        return m_last - m_first;
    }

    inline auto data() const -> const T* {
        return m_data + m_first;
    }

    inline auto data() -> T* {
        return m_data + m_first;
    }

    inline operator const T*() const {
        return data();
    }

    inline operator T*() {
        return data();
    }

    template<typename I>
    inline auto operator[](const I& index) -> T& {
        root_assert(index < size());
        return m_data[index + m_first];
    }

    template<typename I>
    inline auto operator[](const I& index) const -> T {
        root_assert(index < size());
        return m_data[index + m_first];
    }

    template<typename I>
    inline auto offset(const I& extra_offset) const -> array_view {
        root_assert(m_first + extra_offset < size());
        return array_view(m_data, static_cast<u64>(m_first + extra_offset), m_last);
    } 

    template<typename I1, typename I2>
    inline auto range(const I1& start, const I2& end) const -> array_view {
        root_assert(start + m_first < size());
        root_assert(end + m_first < size());
        return array_view(m_data, static_cast<u64>(m_first+start), static_cast<u64>(m_first+end));
    }   

    template<typename I>
    inline auto limit(const I& new_limit) const -> array_view {
        root_assert(new_limit < size());
        return array_view(m_data, m_first, new_limit);
    }

    template<typename I>
    inline auto operator+(const T& extra_offset) const -> array_view {
        return offset(extra_offset);
    }

private:
    T* m_data;
    u64 m_first;
    u64 m_last;
};

} // namespace root