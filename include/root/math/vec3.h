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

#include <cmath>

#include <root/core/primitives.h>

namespace root {

template<typename T>
class vec3 {
public:
    vec3(const T& x, const T& y, const T& z) 
    : x(x), y(y), z(z) {}

    vec3(T&& other) 
    : x(std::move(other.x)), y(std::move(other.y)), z(std::move(other.z)) {}

    vec3(const T& other)
    : x(other.x), y(other.y), z(other.z) {}

    inline constexpr auto operator[](const int index) -> T& {
        switch (index)
        {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            break;
        }
    }

    inline constexpr auto operator[](const int index) const -> T {
        switch (index)
        {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            break;
        }
    }

    inline constexpr auto operator+(const vec3<T>& rhs) const -> vec3<T> {
        return vec3<T>(x + rhs.x, y + rhs.y, z + rhs.z);
    }

    inline constexpr auto operator-(const vec3<T>& rhs) const -> vec3<T> {
        return vec3<T>(x - rhs.x, y - rhs.y, z - rhs.z);
    }

    inline constexpr auto operator==(const vec3<T>& rhs) const -> bool {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }

    inline constexpr auto operator!=(const vec3<T>& rhs) const -> bool {
        return !operator==(rhs);
    }

    constexpr static i32 num_components = 3;

    T x, y, z;
};

template<typename T>
auto dot(const vec3<T>& lhs, const vec3<T>& rhs) -> T {
    return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z);
}

template<typename T>
auto mul(const vec3<T>& lhs, const vec3<T>& rhs) -> vec3<T> {
    return vec3<T>(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
}

template<typename T>
auto div(const vec3<T>& lhs, const vec3<T>& rhs) -> vec3<T> {
    return vec3<T>(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
}

template<typename T>
auto cross(const vec3<T>& lhs, const vec3<T>& rhs) -> vec3<T> {
    return vec3<T>((lhs.y * rhs.z) - (lhs.z * rhs.y),
                   (lhs.z * rhs.x) - (lhs.x * rhs.z),
                   (lhs.x * rhs.y) - (lhs.y * rhs.x));
}

template<typename T>
auto magnitude(const vec3<T>& vec) -> T {
    return sqrt(dot(vec,vec));
}

template<typename T>
auto normalize(const vec3<T>& vec) -> vec3<T> {
    T mag = magnitude(vec);
    return vec3<T>(vec.x/mag, vec.y/mag, vec.z/mag);
}

} // namespace root