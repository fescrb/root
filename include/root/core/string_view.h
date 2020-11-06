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

#include <root/core/array_slice.h>

namespace root {

inline constexpr auto strlen(const char* str) noexcept -> u64 {
    return str[0] != '\0' ? 1 + strlen(str+1) : 0;
}

class string_view : public array_slice<const i8> {
public:
    constexpr string_view() noexcept : array_slice<const i8>() { }

    constexpr string_view(const i8* data, const u64& first, const u64& last) noexcept
    :   array_slice<const i8>(data, first, last) {}

    constexpr string_view(const i8* data) noexcept
    :   array_slice<const i8>(data, 0, strlen(data)) {}

    constexpr string_view(string_view&& other) noexcept
    :   array_slice<const i8>(std::move(other)) {}

    constexpr string_view(const string_view& other) noexcept
    :   array_slice<const i8>(other) {}

    constexpr string_view(array_slice<const i8>&& other) noexcept
    :   array_slice<const i8>(std::move(other)) {}

    constexpr string_view(const array_slice<const i8>& other) noexcept
    :   array_slice<const i8>(other) {}

    constexpr string_view(const iterator& begin, const iterator& end) noexcept
    :   array_slice<const i8>(begin, end) {}
    
    constexpr string_view(const reverse_iterator& begin, const reverse_iterator& end) noexcept
    :   array_slice<const i8>(begin, end) {}

    auto operator=(const string_view& other) -> string_view& {
        array_slice<const i8>::operator=(other);
        return *this;
    }

    auto operator=(string_view&& other) -> string_view& {
        array_slice<const i8>::operator=(std::move(other));
        return *this;
    }

    constexpr auto operator==(const string_view& other) const -> bool {
        if(size() != other.size()) return false;
        for(int i = 0; i < size(); i++) {
            if(m_data[i] != other[i]) return false;
        }
        return true;
    }

    constexpr auto operator!=(const string_view& other) const -> bool {
        return !operator==(other);
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

inline constexpr auto strlen(const string_view& str) noexcept -> u64 {
    return str.size();
}


} // namespace root