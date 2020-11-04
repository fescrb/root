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
#include <type_traits>

#include <utility>

namespace root {

template <typename T>
class array_slice {
public:
    using element_type = T; 

    constexpr inline array_slice() noexcept
    :   m_data(nullptr) , m_first(0), m_last(0) { } 

    constexpr inline array_slice(T* data, const u64& first, const u64& last) noexcept
    :   m_data(data), m_first(first), m_last(last) {}

    constexpr inline array_slice(array_slice&& other) noexcept
    :   m_data(std::move(other.m_data)),
        m_first(std::move(other.m_first)),
        m_last(std::move(other.m_last)) {}

    constexpr inline array_slice(const array_slice& other) noexcept
    :   m_data(other.m_data),
        m_first(other.m_first),
        m_last(other.m_last) {
    }

    constexpr inline auto operator=(const array_slice& other) noexcept -> array_slice& {
        m_data = other.m_data;
        m_first = other.m_first;
        m_last = other.m_last;
        return *this;
    }

    constexpr auto operator=(array_slice&& other) noexcept -> array_slice& {
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

    constexpr auto size() const noexcept -> u64 {
        return m_last - m_first;
    }

    constexpr auto data() const noexcept -> const T* {
        return m_data + m_first;
    }

    constexpr auto data() noexcept -> T* {
        return m_data + m_first;
    }

    inline operator const T*() const {
        return data();
    }

    inline operator T*() {
        return data();
    }
    

    /****
     * const methods
     ** */

    template<typename I>
    inline auto operator[](const I& index) const -> T {
        root_assert(index < size());
        return m_data[index + m_first];
    }

    template<typename I>
    inline auto offset(const I& extra_offset) const -> array_slice<const T> {
        root_assert(m_first + extra_offset < size());
        return array_slice(m_data, static_cast<u64>(m_first + extra_offset), m_last);
    } 

    template<typename I1, typename I2>
    inline auto range(const I1& start, const I2& end) const -> array_slice<const T> {
        root_assert(start + m_first < size());
        root_assert(end + m_first <= size());
        return array_slice(m_data, static_cast<u64>(m_first+start), static_cast<u64>(m_first+end));
    }   

    template<typename I>
    inline auto limit(const I& new_limit) const -> array_slice<const T> {
        root_assert(new_limit <= size());
        return array_slice(m_data, m_first, new_limit);
    }

    template<typename I>
    inline auto operator+(const I& extra_offset) const -> array_slice<const T> {
        return offset(extra_offset);
    }

    /***
     * Mutable methods
     * */

    template<typename I>
    inline auto operator[](const I& index) -> T& {
        root_assert(index < size());
        return m_data[index + m_first];
    }

    template<typename I>
    inline auto offset(const I& extra_offset) -> array_slice<T> {
        root_assert(m_first + extra_offset < size());
        return array_slice<T>(m_data, static_cast<u64>(m_first + extra_offset), m_last);
    } 

    template<typename I1, typename I2>
    inline auto range(const I1& start, const I2& end) -> array_slice<T> {
        root_assert(start + m_first < size());
        root_assert(end + m_first <= size());
        return array_slice<T>(m_data, static_cast<u64>(m_first+start), static_cast<u64>(m_first+end));
    }   

    template<typename I>
    inline auto limit(const I& new_limit) -> array_slice<T> {
        root_assert(new_limit <= size());
        return array_slice<T>(m_data, m_first, new_limit);
    }

    template<typename I>
    inline auto operator+(const I& extra_offset) -> array_slice<T> {
        return offset(extra_offset);
    }

    class iterator;

    using mutable_slice = array_slice<std::remove_const_t<T>>;
    using mutable_iterator = typename mutable_slice::iterator;
    using const_slice = array_slice<std::add_const_t<T>>;
    using const_iterator = typename const_slice::iterator;

    class iterator final {
    public:
        constexpr iterator() noexcept = default;
        constexpr iterator(const iterator& other) noexcept = default;
        constexpr iterator(iterator&& other) noexcept = default;

        constexpr auto operator<=(const mutable_iterator& other) const noexcept -> bool {
            root_assert(m_data == other.data);
            return m_index <= other.m_index;
        }
        
        constexpr auto operator<=(const const_iterator& other) const noexcept -> bool {
            root_assert(m_data == other.data);
            return m_index <= other.m_index;
        }

        constexpr auto operator==(const mutable_iterator& other) const noexcept -> bool {
            root_assert(m_data == other.data);
            return m_index == other.m_index;
        }

        constexpr auto operator==(const const_iterator& other) const noexcept -> bool {
            root_assert(m_data == other.data);
            return m_index == other.m_index;
        }

        constexpr auto operator!=(const mutable_iterator& other) const noexcept -> bool {
            return !operator==(other);
        }

        constexpr auto operator!=(const const_iterator& other) const noexcept -> bool {
            return !operator==(other);
        }

        constexpr auto operator-(const mutable_iterator& other) const noexcept -> i64 {
            return m_index - other.m_index;
        }

        constexpr auto operator-(const const_iterator& other) const noexcept -> i64 {
            return m_index - other.m_index;
        }

        constexpr auto operator++() noexcept -> iterator& {
            m_index++;
            return *this;
        }

        constexpr auto operator++(int) noexcept -> iterator {
            iterator copy = *this;
            m_index++;
            return copy;
        }

        constexpr auto operator--() noexcept -> iterator& {
            m_index--;
            return *this;
        }

        constexpr auto operator--(int) noexcept -> iterator {
            iterator copy = *this;
            m_index--;
            return copy;
        }

        constexpr auto operator*() noexcept -> T& {
            return m_data[m_index];
        } 

        constexpr operator const_iterator() {
            return const_iterator(static_cast<std::add_const_t<T>>(m_data), m_index);
        }

        friend class array_slice<std::remove_const_t<T>>;
        friend class array_slice<std::add_const_t<T>>;
        friend class array_slice<std::remove_const_t<T>>::iterator;
        friend class array_slice<std::add_const_t<T>>::iterator;

    private:
        constexpr iterator(T* data, i64 index) 
        :   m_data(data), m_index(index) {}

        T* m_data;
        i64 m_index;
    }; 

    constexpr array_slice(const iterator& start, const iterator& end)
    :   m_data(start.m_data), m_first(start.m_index), m_last(end.m_index) {
        root_assert(start.m_data == end.m_data);
    }

    constexpr auto begin() const noexcept -> const_iterator {
        return const_iterator(m_data, m_first);
    }

    constexpr auto begin() noexcept -> iterator {
        return iterator(m_data, m_first);
    }

    constexpr auto end() const noexcept -> const_iterator {
        return const_iterator(m_data, m_last);
    }

    constexpr auto end() noexcept -> iterator {
        return iterator(m_data, m_last);
    }

    constexpr auto offset(const iterator& it) const -> const_slice {
        root_assert(m_first + it.m_index < size());
        return const_slice(m_data, static_cast<u64>(m_first + it.m_index), m_last);
    }

    constexpr auto offset(const iterator& it) -> array_slice {
        root_assert(m_first + it.m_index < size());
        return array_slice(m_data, static_cast<u64>(m_first + it.m_index), m_last);
    }

protected:
    T* m_data;
    u64 m_first;
    u64 m_last;
};

template<typename iterator_t, typename T>
constexpr auto find(const iterator_t& first, const iterator_t& end, const T& target) -> iterator_t {
    root_assert(first <= end);
    iterator_t location = first;    
    while(location != end) {
        if (*location == target) return location;
        ++location;
    }
    return location;
}

template<typename iterator_t, typename T>
constexpr auto count(const iterator_t& first, const iterator_t& end, const T& target) -> u64 {
    root_assert(first <= end);
    iterator_t it = first;  
    u64 count = 0;  
    while(it != end) {
        if (*it == target) count++;
        ++it;
    }
    return count;
}

template<typename iterator_t>
constexpr auto distance(const iterator_t& first, const iterator_t& end) -> u64 {
    if(first <= end) return end - first;
    return first - end;
}

} // namespace root