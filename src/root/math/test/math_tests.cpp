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

#include <root/math/math.h>

#include <gtest/gtest.h>

TEST(math_tests, modf) {
    constexpr double FULL_NUMBER = 3.1415;
    constexpr double INT_PART = 3;
    constexpr double FRACTION_PART = 0.1415;

    auto ans = root::modf(FULL_NUMBER);
    EXPECT_FLOAT_EQ(ans.at<0>(), INT_PART);
    EXPECT_FLOAT_EQ(ans.at<1>(), FRACTION_PART);
}