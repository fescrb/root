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

#include "type_helpers.h"

#include <gtest/gtest.h>

TEST(vec4_tests, eq_op) {
    EXPECT_EXACT_EQ(ivec4(1, 2, 3, 4), ivec4(1, 2, 3, 4));
    EXPECT_EXACT_EQ(vec4(1.0f, 2.0f, 3.0f, 4.0f), vec4(1.0f, 2.0f, 3.0f, 4.0f));
}

TEST(vec4_tests, ne_op) {
    EXPECT_NE(ivec4(1, 2, 3, 4), ivec4(5, 6, 7, 8));
    EXPECT_NE(vec4(1.0f, 2.0f, 3.0f, 4.0f), vec4(5.0f, 6.0f, 7.0f, 8.0f));
    EXPECT_NE(vec4(1.0f, 2.0f, 3.0f, 4.0f), vec4(5.0f, 2.0f, 3.0f, 4.0f));
    EXPECT_NE(vec4(1.0f, 2.0f, 3.0f, 4.0f), vec4(1.0f, 6.0f, 3.0f, 4.0f));
    EXPECT_NE(vec4(1.0f, 2.0f, 3.0f, 4.0f), vec4(1.0f, 2.0f, 7.0f, 4.0f));
    EXPECT_NE(vec4(1.0f, 2.0f, 3.0f, 4.0f), vec4(1.0f, 2.0f, 3.0f, 8.0f));
}

TEST(vec4_tests, copy_const) {
    vec4 v1 = vec4(1.0f, 2.0f, 3.0f, 4.0f);
    vec4 v2 = v1;
    EXPECT_EXACT_EQ(v1, v2);
}

TEST(vec4_tests, normalize) {
    EXPECT_EXACT_EQ(normalize(ivec4(8, 4, 16, 2)), ivec4(4, 2, 8, 1));
    EXPECT_APPROX_EQ(normalize(vec4(1.0f, 2.0f, 3.0f, 4.0f)), vec4(0.25f, 0.5f, 0.75f, 1.0f));
}

TEST(vec4_tests, dot) {
    vec4 v1 = vec4(3.5f, 7.6f, 9.1f, -3.5f);
    vec4 v2 = vec4(-6.7f, 1.3f, -4.3f, 5.5f);
    root::f32 ans = -71.95;
    EXPECT_FLOAT_EQ(root::dot(v1,v2), ans);
}