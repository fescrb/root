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

#include <root/core/assert.h>

#include <root/core/private/variadric_type_info.h>

#include <utility>

namespace root {

template<typename...> class tuple {
public:
    inline auto operator==(const tuple& other) const {
        return true;
    }
};

template<typename T, typename... Ts> 
class tuple<T, Ts...> {
public:
    inline tuple()
    :   value(), remainder() {}

    inline explicit tuple(const T v, const Ts... vs)
    :   value(v), remainder(vs...) {}

    inline tuple(const tuple<T, Ts...>& other)
    :   value(other.value), remainder(other.remainder) {}

    inline tuple(tuple<T, Ts...>&& other)
    :   value(std::move(other.value)), 
        remainder(std::move(other.remainder)) {}

    inline auto operator==(const tuple<T, Ts...>& other) const -> bool {
        return value == other.value && remainder == other.remainder;
    }

    inline auto operator=(const tuple<T, Ts...>& other) -> tuple<T, Ts...>& {
        if(this != &other) {
            value = other.value;
            remainder = other.remainder;
        }
        return *this;
    }

    inline auto operator=(tuple<T, Ts...>&& other) -> tuple<T, Ts...>& {
        if(this != &other) {
            value = std::move(other.value);
            remainder = std::move(other.remainder);
        }
        return *this;
    }

    template<u64 I>
    inline auto at() -> typename variadric_type_by_index<I, T, Ts...>::type& {
        return remainder.template at<I-1>();
    }

    template<>
    inline auto at<0u>() -> T& {
        return value;
    }

    template<u64 I>
    inline auto at() const -> typename variadric_type_by_index<I, T, Ts...>::type {
        return remainder.template at<I-1>();
    }

    template<>
    inline auto at<0u>() const -> T {
        return value;
    }

private:
    T value;
    tuple<Ts...> remainder;
};

template<u64 I, typename T, typename... Ts>
auto get(const tuple<T, Ts...>& t) -> decltype(t.template at<I>()) {
    return t.template at<I>();
}

} // namespace root