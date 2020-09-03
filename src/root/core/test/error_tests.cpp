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

#include <root/core/error.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(error_tests, value_or_error_error) {
    constexpr root::error SAMPLE_ERROR = root::error::UNKNOWN_ERROR;
    root::value_or_error<int> voe(SAMPLE_ERROR);

    EXPECT_EQ(voe, SAMPLE_ERROR);
    EXPECT_FALSE(voe);
    EXPECT_FALSE(voe < 10);
    EXPECT_FALSE(voe <= 10);
    EXPECT_FALSE(voe == 10);
    EXPECT_FALSE(voe != 10);
    EXPECT_FALSE(voe >= 10);
    EXPECT_FALSE(voe > 10);
}

TEST(error_tests, value_or_error_valie) {
    constexpr int SAMPLE_VALUE = 42;
    root::value_or_error<int> voe(SAMPLE_VALUE);

    EXPECT_EQ(voe, SAMPLE_VALUE);
    EXPECT_TRUE(voe);
    EXPECT_NE(voe, -SAMPLE_VALUE);
    EXPECT_LT(voe, SAMPLE_VALUE+1);
    EXPECT_GT(voe, SAMPLE_VALUE-1);
    EXPECT_GE(voe, SAMPLE_VALUE);
    EXPECT_LE(voe, SAMPLE_VALUE);
}