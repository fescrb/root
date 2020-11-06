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

#include <root/core/assert.h>
#include <root/core/primitives.h>

#include <type_traits>

namespace root {

enum class error : u64 {
    NO_ERROR = 0,
    UNKNOWN_ERROR = 1,
    DEAD_OBJECT = 2,
    INVALID_OPERATION = 3,
    NOT_FOUND = 4
};

template<typename T>
struct value_or_error final {
    static_assert(!std::is_reference<T>::value, "This class must hold a copy of the value");
    static_assert(!std::is_same<T,bool>::value, "We won't store booleans");
    static_assert(!std::is_same<T,error>::value, "We won't store errors");

    inline value_or_error(const T v) 
    :   m_value(v), m_error(error::NO_ERROR) {}
    
    inline value_or_error(const error e) 
    :   m_value(), m_error(e) {}

    template<typename O>
    inline auto operator==(const O v) const {
        root_assert(has_value());
        return m_value == v;
    }

    template<typename O>
    inline auto operator!=(const O v) const {
        root_assert(has_value());
        return m_value != v;
    }

    template<typename O>
    inline auto operator<(const O v) const {
        root_assert(has_value());
        return m_value < v;
    }

    template<typename O>
    inline auto operator<=(const O v) const {
        root_assert(has_value());
        return m_value <= v;
    }

    template<typename O>
    inline auto operator>(const O v) const {
        root_assert(has_value());
        return m_value > v;
    }

    template<typename O>
    inline auto operator>=(const O v) const {
        root_assert(has_value());
        return m_value >= v;
    }

    template<>
    inline auto operator==<error>(const error e) const {
        return m_error == e;
    }

    inline auto has_value() const -> bool {
        return m_error == error::NO_ERROR;
    }

    inline auto value_or(const T v) const -> T {
        return has_value() ? m_value : v;
    }

    inline auto value() const -> T {
        root_assert(has_value());
        return m_value;
    }

    inline auto error() const -> error {
        root_assert(!has_value());
        return m_error;
    }

    inline operator T() const {
        return value();
    }

    inline explicit operator bool() const {
        return has_value();
    }

private:
    T m_value;
    enum error m_error;
};

} // namespace root