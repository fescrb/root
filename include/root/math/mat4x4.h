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

#include <root/math/vec4.h>

namespace root {

template<typename T>
class mat4x4 {
public:
    mat4x4(const T mat[4][4])
    : x(mat[0][0], mat[0][1], mat[0][2], mat[0][3]),
      y(mat[1][0], mat[1][1], mat[1][2], mat[1][3]),
      z(mat[2][0], mat[2][1], mat[2][2], mat[2][3]),
      w(mat[3][0], mat[3][1], mat[3][2], mat[3][3]) {}

    mat4x4(const vec4<T>& row_x, const vec4<T>& row_y, const vec4<T>& row_z, const vec4<T>& row_w)
    : x(row_x),
      y(row_y),
      z(row_z),
      w(row_w) {}

    mat4x4(const mat4x4<T>& mat)
    : x(mat.x),
      y(mat.y),
      z(mat.z),
      w(mat.w) {}

    mat4x4(mat4x4<T>&& mat)
    : x(std::move(mat.x)),
      y(std::move(mat.y)),
      z(std::move(mat.z)),
      w(std::move(mat.w)) {}

    inline auto operator*(const vec4<T>& vec) const -> vec4<T> {
        return vec4<T>(dot(x,vec), dot(y,vec), dot(z,vec), dot(w,vec));
    }

    inline auto operator*(const mat4x4<T>& mat) const -> mat4x4<T> {
        mat4x4<T> transposed_mat = transpose(mat); // TODO write this out to avoid the temp matrix store
        return mat4x4({{dot(x, transposed_mat.x), dot(x, transposed_mat.y), dot(x, transposed_mat.z), dot(x, transposed_mat.w)},
                       {dot(y, transposed_mat.x), dot(y, transposed_mat.y), dot(y, transposed_mat.z), dot(y, transposed_mat.w)},
                       {dot(z, transposed_mat.x), dot(z, transposed_mat.y), dot(z, transposed_mat.z), dot(z, transposed_mat.w)},
                       {dot(w, transposed_mat.x), dot(w, transposed_mat.y), dot(w, transposed_mat.z), dot(w, transposed_mat.w)}}); 
    }

    inline auto operator==(const mat4x4<T>& other) const -> bool {
        return (x == other.x) && (y == other.y) && (z == other.z) && (w == other.w);
    }

    inline auto operator!=(const mat4x4<T>& other) const -> bool {
        return !operator==(other);
    }

    inline static auto identity() -> mat4x4 {
        return mat4x4({{1, 0, 0, 0},
                       {0, 1, 0, 0},
                       {0, 0, 1, 0},
                       {0, 0, 0, 1}});
    }

    static constexpr bool column_major = false;
    static constexpr bool row_major = true;
    static constexpr i32 num_components = 16;

    vec4<T> x, y, z, w; // These represent rows in the matrix 
};

template<typename T>
inline auto transpose(const mat4x4<T>& mat) -> mat4x4<T> {
    return mat4x4<T>({{mat.x.x, mat.y.x, mat.z.x, mat.w.x},
                      {mat.x.y, mat.y.y, mat.z.y, mat.w.y},
                      {mat.x.z, mat.y.z, mat.z.z, mat.w.z},
                      {mat.x.w, mat.y.w, mat.z.w, mat.w.w}});
}

} // namespace root