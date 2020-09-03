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

#include <root/core/primitives.h>

namespace root {

enum class error : u64 {
    NO_ERROR = 0,
    UNKNOWN_ERROR = 1,
    DEAD_OBJECT = 2,
    INVALID_OPERATION = 3
};

// TODO: disable value_or_error<error>
// Maybe allow/disallow ref types?
// Disallow bools?
template<typename T>
struct value_or_error final {
    inline value_or_error(const T v) 
    :   value(v), error(error::NO_ERROR) {}
    
    inline value_or_error(const error e) 
    :   value(), error(e) {}

    template<typename O>
    inline auto operator==(const O v) const {
        return valid() && value == v;
    }

    template<typename O>
    inline auto operator<(const O v) const {
        return valid() && value < v;
    }

    template<typename O>
    inline auto operator<=(const O v) const {
        return valid() && value <= v;
    }

    template<typename O>
    inline auto operator>(const O v) const {
        return valid() && value > v;
    }

    template<>
    inline auto operator==<error>(const error e) const {
        return error == e;
    }

    inline auto valid() const -> bool {
        return error == error::NO_ERROR;
    }

    inline operator bool() const {
        return valid();
    }

    T value;
    error error;
};

} // namespace root