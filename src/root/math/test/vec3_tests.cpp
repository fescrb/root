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

#include <limits>
#include <random>
#include <cmath>
#include <iostream>
#include <ostream>

#include <gtest/gtest.h>

template<typename T>
inline auto operator<<(std::ostream& os, const root::vec3<T>& vec) -> std::ostream& {
    return os << "{" << vec.x << ", " << vec.y << ", " << vec.z << "}";
}

inline auto epsilon_equality(const root::f32& lhs, const root::f32& rhs) -> bool {
    return fabsf(lhs - rhs) < (std::numeric_limits<root::f32>::epsilon()*std::max(fabsf(lhs), fabsf(rhs)));
}

TEST(vec3_tests, eq_op) {
    EXPECT_EXACT_EQ(ivec3(1, 2, 3), ivec3(1, 2, 3));
    EXPECT_EXACT_EQ(vec3(1.0f, 2.0f, 3.0f), vec3(1.0f, 2.0f, 3.0f));
}

TEST(vec3_tests, ne_op) {
    EXPECT_NE(ivec3(1, 2, 3), ivec3(4, 5, 6));
    EXPECT_NE(vec3(1.0f, 2.0f, 3.0f), vec3(4.0f, 5.0f, 6.0f));
    EXPECT_NE(vec3(1.0f, 2.0f, 3.0f), vec3(4.0f, 2.0f, 3.0f));
    EXPECT_NE(vec3(1.0f, 2.0f, 3.0f), vec3(1.0f, 5.0f, 3.0f));
    EXPECT_NE(vec3(1.0f, 2.0f, 3.0f), vec3(1.0f, 2.0f, 6.0f));
}

TEST(vec3_tests, copy_const) {
    vec3 v1 = vec3(1.0f, 2.0f, 3.0f);
    vec3 v2 = v1;
    EXPECT_EXACT_EQ(v1, v2);
}

TEST(vec3_tests, add) {
    EXPECT_EXACT_EQ(ivec3(1, 2, 3) + ivec3(4, 5, 6), ivec3(5, 7, 9));
    EXPECT_APPROX_EQ(vec3(1.0f, 2.0f, 3.0f) + vec3(4.0f, 5.0f, 6.0f), vec3(5.0f, 7.0f, 9.0f));
}

TEST(vec3_tests, sub) {
    EXPECT_EXACT_EQ(ivec3(4, 5, 6) - ivec3(1, 2, 3), ivec3(3, 3, 3));
    EXPECT_APPROX_EQ(vec3(1.0f, 2.0f, 3.0f) - vec3(4.0f, 5.0f, 6.0f), vec3(-3.0f, -3.0f, -3.0f));
}

TEST(vec3_tests, mag) {
    EXPECT_FLOAT_EQ(root::magnitude(vec3(1.0f, 2.0f, 3.0f)), sqrt(14.0f));
}

TEST(vec3_tests, normalize) {
    constexpr int NUM_TESTS = 10;
    std::default_random_engine generator;
    std::normal_distribution<root::f32> distribution(15.0f,2.0f);
    for(int i = 0; i < NUM_TESTS; i++) {
        vec3 v = vec3(distribution(generator),distribution(generator),distribution(generator));
        if(!epsilon_equality(root::magnitude(v), 1.0f)) {
            EXPECT_FLOAT_EQ(root::magnitude(root::normalize(v)), 1.0f);
        }
    }
}

TEST(vec3_tests, dot) {
    vec3 v1 = vec3(3.5f, 7.6f, 9.1f);
    vec3 v2 = vec3(-6.7f, 1.3f, -4.3f);
    root::f32 ans = -52.7;
    EXPECT_FLOAT_EQ(root::dot(v1,v2), ans);
}

TEST(vec3_tests, cross) {
    vec3 v1 = vec3(3.5f, 7.6f, 9.1f);
    vec3 v2 = vec3(-6.7f, 1.3f, -4.3f);
    vec3 ans = vec3(-44.51, -45.92, 55.47);
    EXPECT_APPROX_EQ(root::cross(v1,v2), ans);
}

TEST(vec3_tests, products) {
    constexpr int NUM_TESTS = 10;
    std::default_random_engine generator;
    std::normal_distribution<root::f32> distribution(0.0f,15.0f);
    for(int i = 0; i < NUM_TESTS; i++) {
        vec3 v1 = vec3(distribution(generator),distribution(generator),distribution(generator));
        vec3 v2 = vec3(distribution(generator),distribution(generator),distribution(generator));
        vec3 v3 = root::cross(v1, v2);
        EXPECT_LE(fabsf(root::dot(v1,v3)), 1e-2f);
        EXPECT_LE(fabsf(root::dot(v2,v3)), 1e-2f);
    }
}