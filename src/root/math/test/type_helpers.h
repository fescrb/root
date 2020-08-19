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

#include <root/math/vec3.h>
#include <root/math/vec4.h>
#include <root/math/mat4x4.h>
#include <root/core/primitives.h>

#include <gtest/gtest.h>


using ivec3 = root::vec3<root::i32>;
using vec3 = root::vec3<root::f32>;

using ivec4 = root::vec4<root::i32>;
using vec4 = root::vec4<root::f32>;

using mat4x4 = root::mat4x4<root::f32>;

#define EXPECT_EXACT_EQ(_1_, _2_) EXPECT_EQ(_1_, _2_)

#define EXPECT_APPROX_EQ(_1_, _2_)  expect_approx_eq(_1_, _2_, "_1_", "_2_") 

inline auto expect_approx_eq(const vec3& v1, const vec3& v2, const char* v1_str, const char* v2_str) -> void {
    EXPECT_FLOAT_EQ(v1.x, v2.x);
    EXPECT_FLOAT_EQ(v1.y, v2.y);
    EXPECT_FLOAT_EQ(v1.z, v2.z);
}

inline auto expect_approx_eq(const vec4& v1, const vec4& v2, const char* v1_str, const char* v2_str) -> void {
    EXPECT_FLOAT_EQ(v1.x, v2.x);
    EXPECT_FLOAT_EQ(v1.y, v2.y);
    EXPECT_FLOAT_EQ(v1.z, v2.z);
    EXPECT_FLOAT_EQ(v1.w, v2.w);
}

inline auto expect_approx_eq(const mat4x4& m1, const mat4x4& m2, const char* m1_str, const char* m2_str) -> void {
    expect_approx_eq(m1.x, m2.x, m1_str, m2_str);
    expect_approx_eq(m1.y, m2.y, m1_str, m2_str);
    expect_approx_eq(m1.z, m2.z, m1_str, m2_str);
    expect_approx_eq(m1.w, m2.w, m1_str, m2_str);
}

