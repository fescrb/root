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

TEST(mat4x4_tests, eq_op) {
    EXPECT_EXACT_EQ(
        mat4x4({{ 1.0f,  2.0f,  3.0f,  4.0f},
                { 5.0f,  6.0f,  7.0f,  8.0f},
                { 9.0f, 10.0f, 11.0f, 12.0f},
                {13.0f, 14.0f, 15.0f, 16.0f}}),
        mat4x4({{ 1.0f,  2.0f,  3.0f,  4.0f},
                { 5.0f,  6.0f,  7.0f,  8.0f},
                { 9.0f, 10.0f, 11.0f, 12.0f},
                {13.0f, 14.0f, 15.0f, 16.0f}})
    );
    EXPECT_EXACT_EQ(
        mat4x4({{ 1.0f,  2.0f,  3.0f,  4.0f},
                { 5.0f,  6.0f,  7.0f,  8.0f},
                { 9.0f, 10.0f, 11.0f, 12.0f},
                {13.0f, 14.0f, 15.0f, 16.0f}}),
        mat4x4(vec4( 1.0f,  2.0f,  3.0f,  4.0f),
               vec4( 5.0f,  6.0f,  7.0f,  8.0f),
               vec4( 9.0f, 10.0f, 11.0f, 12.0f),
               vec4(13.0f, 14.0f, 15.0f, 16.0f))
    );
}

TEST(mat4x4_tests, ne_op) {
    EXPECT_NE(
        mat4x4({{ 1.0f,  2.0f,  3.0f,  4.0f},
                { 5.0f,  6.0f,  7.0f,  8.0f},
                { 9.0f, 10.0f, 11.0f, 12.0f},
                {13.0f, 14.0f, 15.0f, 16.0f}}),
        mat4x4({{17.0f, 18.0f, 19.0f, 20.0f},
                {21.0f, 22.0f, 23.0f, 24.0f},
                {25.0f, 26.0f, 27.0f, 28.0f},
                {29.0f, 30.0f, 31.0f, 32.0f}})
    );
    EXPECT_NE(
        mat4x4({{ 1.0f,  2.0f,  3.0f,  4.0f},
                { 5.0f,  6.0f,  7.0f,  8.0f},
                { 9.0f, 10.0f, 11.0f, 12.0f},
                {13.0f, 14.0f, 15.0f, 16.0f}}),
        mat4x4({{17.0f,  2.0f,  3.0f,  4.0f},
                { 5.0f,  6.0f,  7.0f,  8.0f},
                { 9.0f, 10.0f, 11.0f, 12.0f},
                {13.0f, 14.0f, 15.0f, 16.0f}})
    );
    EXPECT_NE(
        mat4x4({{ 1.0f,  2.0f,  3.0f,  4.0f},
                { 5.0f,  6.0f,  7.0f,  8.0f},
                { 9.0f, 10.0f, 11.0f, 12.0f},
                {13.0f, 14.0f, 15.0f, 16.0f}}),
        mat4x4({{ 1.0f,  2.0f,  3.0f,  4.0f},
                { 5.0f, 22.0f,  7.0f,  8.0f},
                { 9.0f, 10.0f, 11.0f, 12.0f},
                {13.0f, 14.0f, 15.0f, 16.0f}})
    );
    EXPECT_NE(
        mat4x4({{ 1.0f,  2.0f,  3.0f,  4.0f},
                { 5.0f,  6.0f,  7.0f,  8.0f},
                { 9.0f, 10.0f, 11.0f, 12.0f},
                {13.0f, 14.0f, 15.0f, 16.0f}}),
        mat4x4({{ 1.0f,  2.0f,  3.0f,  4.0f},
                { 5.0f,  6.0f,  7.0f,  8.0f},
                { 9.0f, 10.0f, 27.0f, 12.0f},
                {13.0f, 14.0f, 15.0f, 16.0f}})
    );
    EXPECT_NE(
        mat4x4({{ 1.0f,  2.0f,  3.0f,  4.0f},
                { 5.0f,  6.0f,  7.0f,  8.0f},
                { 9.0f, 10.0f, 11.0f, 12.0f},
                {13.0f, 14.0f, 15.0f, 16.0f}}),
        mat4x4({{ 1.0f,  2.0f,  3.0f,  4.0f},
                { 5.0f,  6.0f,  7.0f,  8.0f},
                { 9.0f, 10.0f, 11.0f, 12.0f},
                {13.0f, 14.0f, 15.0f, 32.0f}})
    );
}

TEST(mat4x4_tests, copy_const) {
    mat4x4 m1 = mat4x4({{ 1.0f,  2.0f,  3.0f,  4.0f},
                        { 5.0f,  6.0f,  7.0f,  8.0f},
                        { 9.0f, 10.0f, 11.0f, 12.0f},
                        {13.0f, 14.0f, 15.0f, 16.0f}});
    mat4x4 m2 = m1;
    EXPECT_EXACT_EQ(m1,m2);
}

TEST(mat4x4_tests, transpose) {
    EXPECT_EXACT_EQ(
        transpose(mat4x4({{ 1.0f,  2.0f,  3.0f,  4.0f},
                          { 5.0f,  6.0f,  7.0f,  8.0f},
                          { 9.0f, 10.0f, 11.0f, 12.0f},
                          {13.0f, 14.0f, 15.0f, 16.0f}})),
        mat4x4({{1.0f, 5.0f,  9.0f, 13.0f},
                {2.0f, 6.0f, 10.0f, 14.0f},
                {3.0f, 7.0f, 11.0f, 15.0f},
                {4.0f, 8.0f, 12.0f, 16.0f}})
    );
}

TEST(mat4x4_tests, vec_mul) {
    mat4x4 m = mat4x4({{ 1.0f,  2.0f,  3.0f,  4.0f},
                       { 5.0f,  6.0f,  7.0f,  8.0f},
                       { 9.0f, 10.0f, 11.0f, 12.0f},
                       {13.0f, 14.0f, 15.0f, 16.0f}});
    vec4 v = vec4(17.0f, 18.0f, 19.0f, 20.0f);
    EXPECT_APPROX_EQ(m * v, vec4(190.0f, 486.0f, 782.0f, 1078.0f));
}

TEST(mat4x4_tests, mat_mul) {
    mat4x4 m1 = mat4x4({{ 1.0f,  2.0f,  3.0f,  4.0f},
                        { 5.0f,  6.0f,  7.0f,  8.0f},
                        { 9.0f, 10.0f, 11.0f, 12.0f},
                        {13.0f, 14.0f, 15.0f, 16.0f}});
    mat4x4 m2 = mat4x4({{17.0f, 18.0f, 19.0f, 20.0f},
                        {21.0f, 22.0f, 23.0f, 24.0f},
                        {25.0f, 26.0f, 27.0f, 28.0f},
                        {29.0f, 30.0f, 31.0f, 32.0f}});
    mat4x4 ans = mat4x4({{ 250.0f,  260.0f,  270.0f,  280.0f},
                         { 618.0f,  644.0f,  670.0f,  696.0f},
                         { 986.0f, 1028.0f, 1070.0f, 1112.0f},
                         {1354.0f, 1412.0f, 1470.0f, 1528.0f}});
    EXPECT_APPROX_EQ(m1 * m2, ans);
}

TEST(mat4x4_tests, identity) {
    mat4x4 i = mat4x4::identity();
    mat4x4 m = mat4x4({{ 1.0f,  2.0f,  3.0f,  4.0f},
                       { 5.0f,  6.0f,  7.0f,  8.0f},
                       { 9.0f, 10.0f, 11.0f, 12.0f},
                       {13.0f, 14.0f, 15.0f, 16.0f}});
    vec4 v = vec4(17.0f, 18.0f, 19.0f, 20.0f);
    EXPECT_EXACT_EQ(i*m, m);
    EXPECT_EXACT_EQ(i*v, v);
}