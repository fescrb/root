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

#include <root/math/mat4x4.h>

#include <type_traits> // Do we want to not depend on stdlib?
#include <cmath>

namespace root {

template<typename T>
inline auto translation(const vec3<T>& movement) -> mat4x4<T> {
    return mat4x4<T>({{1, 0, 0, movement.x},
                      {0, 1, 0, movement.y},
                      {0, 0, 1, movement.z},
                      {0, 0, 0,          1}});
}

template<typename T>
inline auto scaling(const vec3<T>& scale_factors) -> mat4x4<T> {
    return mat4x4<T>({{scale_factors.x,               0,               0, 0},
                      {              0, scale_factors.y,               0, 0},
                      {              0,               0, scale_factors.z, 0},
                      {              0,               0,               0, 1}});
}

template<typename T>
inline auto rotate_around_x(const T& angle) -> mat4x4<T> {
    root_static_assert(std::is_floating_point<T>::value);
    return mat4x4<T>({{1           0,           0, 0},
                      {0, cos(angle), -sin(angle), 0},
                      {0, sin(angle),  cos(angle), 0},
                      {0,          0,           0, 1}});
}

template<typename T>
inline auto rotate_around_y(const T& angle) -> mat4x4<T> {
    root_static_assert(std::is_floating_point<T>::value);
    return mat4x4<T>({{ cos(angle), 0, sin(angle), 0},
                      {          0, 1,          0, 0},
                      {-sin(angle), 0, cos(angle), 0},
                      {          0, 0,          0, 1}});
}

template<typename T>
inline auto rotate_around_z(const T& angle) -> mat4x4<T> {
    root_static_assert(std::is_floating_point<T>::value);
    return mat4x4<T>({{cos(angle), -sin(angle), 0, 0},
                      {sin(angle),  cos(angle), 0, 0},
                      {         0,           0, 1, 0},
                      {         0,           0, 0, 1}});
}


template<typename T>
inline auto rotate_around_axis(const vec3<T>& axis, const T& angle) -> mat4x4<T> {
    root_static_assert(std::is_floating_point<T>::value);
    // TODO assert that the axis is normalized?
    // TODO in general
    
}

template <typename T>
inline auto look_at(const vec3<T>& position, const vec3<T>& target, const vec3<T>& up) {
    root_static_assert(std::is_floating_point<T>::value);
    vec3<T> camera_to_target = normalize(target - position);
    vec3<T> right = normalize(cross(up, camera_to_target));
    vec3<T> camera_up = cross(camera_to_target, right);

    return mat4x4<T>({{right.x, camera_up.x, camera_to_target.x, position.x},
                      {right.y, camera_up.y, camera_to_target.y, position.y},
                      {right.z, camera_up.z, camera_to_target.z, position.z},
                      {      0,           0,                  0,          1}});
}

} // namespace root