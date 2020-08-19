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

#include <root/math/vec3.h>

namespace root {

template<typename T>
class vec4 {
public:
    vec4(const T& x, const T& y, const T& z, const T& w) 
    : x(x), y(y), z(z), w(w) {}

    vec4(const vec3<T>& vec, const T& w) 
    : x(vec.x), y(vec.y), z(vec.z), w(w) {}

    vec4(vec3<T>&& vec, const T& w) 
    : x(std::move(vec.x)), y(std::move(vec.y)), z(std::move(vec.z)), w(w) {}

    vec4(const vec4<T>& other)
    : x(other.x), y(other.y), z(other.z), w(other.w) {}

    vec4(vec4<T>&& other) 
    : x(std::move(other.x)), y(std::move(other.y)), z(std::move(other.z)), w(std::move(other.w)) {}

    inline constexpr auto operator[](const int index) -> T& {
        switch (index)
        {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return w;
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
        case 3:
            return w;
        }
    }

    inline auto operator==(const vec4<T>& other) const -> bool {
        return (x == other.x) && (y == other.y) && (z == other.z) && (w == other.w);
    }

    inline auto operator!=(const vec4<T>& other) const -> bool {
        return !operator==(other);
    }

    inline explicit operator vec3<T>() const {
        return vec3<T>(x,y,z);
    }

    constexpr static i32 num_components = 4;

    T x, y, z, w;
};

template<typename T>
inline auto normalize(const vec4<T>& vec) -> vec4<T> {
    return vec4<T>(vec.x/vec.w, vec.y/vec.w, vec.z/vec.w, vec.w/vec.w);
}

template<typename T>
inline auto dot(const vec4<T>& v1, const vec4<T>& v2) -> T {
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w);
}

} // namespace root