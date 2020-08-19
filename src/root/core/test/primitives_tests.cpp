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

#include <gtest/gtest.h>

#include <type_traits>

TEST(primitives_test, sizes) {
    EXPECT_EQ(sizeof(root::i64), 8);
    EXPECT_EQ(sizeof(root::i32), 4);
    EXPECT_EQ(sizeof(root::i16), 2);
    EXPECT_EQ(sizeof(root::i8), 1);
    EXPECT_EQ(sizeof(root::u64), 8);
    EXPECT_EQ(sizeof(root::u32), 4);
    EXPECT_EQ(sizeof(root::u16), 2);
    EXPECT_EQ(sizeof(root::u8), 1);
    EXPECT_EQ(sizeof(root::f64), 8);
    EXPECT_EQ(sizeof(root::f32), 4);
}

TEST(primitives_test, signedness) {
    EXPECT_TRUE(std::is_signed<root::i64>::value);
    EXPECT_TRUE(std::is_signed<root::i32>::value);
    EXPECT_TRUE(std::is_signed<root::i16>::value);
    EXPECT_TRUE(std::is_signed<root::i8>::value);
    EXPECT_TRUE(std::is_signed<root::f64>::value);
    EXPECT_TRUE(std::is_signed<root::f32>::value);
    EXPECT_TRUE(std::is_unsigned<root::u64>::value);
    EXPECT_TRUE(std::is_unsigned<root::u32>::value);
    EXPECT_TRUE(std::is_unsigned<root::u16>::value);
    EXPECT_TRUE(std::is_unsigned<root::u8>::value);
}

TEST(primitives_test, fp) {
    EXPECT_FALSE(std::is_floating_point<root::i64>::value);
    EXPECT_FALSE(std::is_floating_point<root::i32>::value);
    EXPECT_FALSE(std::is_floating_point<root::i16>::value);
    EXPECT_FALSE(std::is_floating_point<root::i8>::value);
    EXPECT_TRUE(std::is_floating_point<root::f64>::value);
    EXPECT_TRUE(std::is_floating_point<root::f32>::value);
    EXPECT_FALSE(std::is_floating_point<root::u64>::value);
    EXPECT_FALSE(std::is_floating_point<root::u32>::value);
    EXPECT_FALSE(std::is_floating_point<root::u16>::value);
    EXPECT_FALSE(std::is_floating_point<root::u8>::value);
}

TEST(primitives_test, arithmetic) {
    EXPECT_TRUE(std::is_arithmetic<root::i64>::value);
    EXPECT_TRUE(std::is_arithmetic<root::i32>::value);
    EXPECT_TRUE(std::is_arithmetic<root::i16>::value);
    EXPECT_TRUE(std::is_arithmetic<root::i8>::value);
    EXPECT_TRUE(std::is_arithmetic<root::f64>::value);
    EXPECT_TRUE(std::is_arithmetic<root::f32>::value);
    EXPECT_TRUE(std::is_arithmetic<root::u64>::value);
    EXPECT_TRUE(std::is_arithmetic<root::u32>::value);
    EXPECT_TRUE(std::is_arithmetic<root::u16>::value);
    EXPECT_TRUE(std::is_arithmetic<root::u8>::value);
}