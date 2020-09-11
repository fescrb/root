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

#include <root/core/array_view.h>

namespace root {

class string_view : public array_view<i8> {
public:
    inline string_view() { clear(); } 

    inline string_view(char* data, const u64& first, const u64& last)
    :   array_view(data, first, last) {}

    inline string_view(string_view&& other) 
    :   array_view(std::move(other)) {}

    inline string_view(const string_view& other)
    :   array_view(other) {}

    inline string_view(array_view<i8>&& other) 
    :   array_view(std::move(other)) {}

    inline string_view(const array_view<i8>& other)
    :   array_view(other) {}
    
    auto operator=(const string_view& other) -> array_view& {
        return array_view<char>::operator=(other);
    }

    auto operator=(array_view&& other) -> array_view& {
        return array_view<char>::operator=(std::move(other));
    }

    template<typename I>
    inline auto offset(const I& extra_offset) const -> string_view {
        root_assert(m_first + extra_offset < size());
        return string_view(m_data, static_cast<u64>(m_first + extra_offset), m_last);
    } 

    template<typename I1, typename I2>
    inline auto range(const I1& start, const I2& end) const -> string_view {
        root_assert(start + m_first < size());
        root_assert(end + m_first <= size());
        return string_view(m_data, static_cast<u64>(m_first+start), static_cast<u64>(m_first+end));
    }   

    template<typename I>
    inline auto limit(const I& new_limit) const -> string_view {
        root_assert(new_limit <= size());
        return string_view(m_data, m_first, new_limit);
    }

    template<typename I>
    inline auto operator+(const I& extra_offset) const -> string_view {
        return offset(extra_offset);
    }

};

} // namespace root