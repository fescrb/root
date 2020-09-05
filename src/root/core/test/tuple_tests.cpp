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

#include <root/core/tuple.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstdlib>

TEST(tuple_tests, blank_init) {
    const root::tuple<int,int> two_ints;

    EXPECT_EQ(two_ints.at<0>(), 0);
    EXPECT_EQ(two_ints.at<1>(), 0);    
} 

TEST(tuple_tests, value_init) {
    int first_val = rand();
    int second_val = rand();
    const root::tuple<int,int> two_ints(first_val, second_val);

    EXPECT_EQ(two_ints.at<0>(), first_val);
    EXPECT_EQ(two_ints.at<1>(), second_val);    
} 

TEST(tuple_tests, copy_init) {
    int first_val = rand();
    int second_val = rand();
    int third_val = rand();
    const root::tuple<int,int, int> three_ints(first_val, second_val, third_val);
    const auto three_ints_copy(three_ints);

    EXPECT_EQ(three_ints_copy.at<0>(), first_val);
    EXPECT_EQ(three_ints_copy.at<1>(), second_val);
    EXPECT_EQ(three_ints_copy.at<2>(), third_val);    
} 

TEST(tuple_tests, move_init) {
    int first_val = rand();
    int second_val = rand();
    int third_val = rand();
    const root::tuple<int,int, int> three_ints(first_val, second_val, third_val);
    const auto three_ints_copy(std::move(three_ints));

    EXPECT_EQ(three_ints_copy.at<0>(), first_val);
    EXPECT_EQ(three_ints_copy.at<1>(), second_val);
    EXPECT_EQ(three_ints_copy.at<2>(), third_val);    
} 

TEST(tuple_tests, equality_op) {
    int first_val = rand();
    int second_val = rand();
    const root::tuple<int,int> two_ints(first_val, second_val);
    const root::tuple<int,int> two_ints_again(first_val, second_val);

    EXPECT_EQ(two_ints, two_ints_again); 
}

TEST(tuple_tests, assign_op) {
    int first_val = rand();
    int second_val = rand();
    const root::tuple<int,int> two_ints(first_val, second_val);
    root::tuple<int,int> two_ints_again;

    two_ints_again = two_ints;

    EXPECT_EQ(two_ints, two_ints_again); 
}

TEST(tuple_tests, move_assign_op) {
    int first_val = rand();
    int second_val = rand();
    const root::tuple<int,int> two_ints(first_val, second_val);
    root::tuple<int,int> two_ints_again;

    two_ints_again = std::move(two_ints);

    EXPECT_EQ(two_ints_again.at<0>(), first_val);
    EXPECT_EQ(two_ints_again.at<1>(), second_val);    
}

TEST(tuple_tests, setting_values) {
    int first_val = rand();
    int second_val = rand();

    root::tuple<int,int> two_ints(first_val, second_val);

    int third_val = rand();
    int fourth_val = rand();

    two_ints.at<0>() = third_val;
    two_ints.at<1>() = fourth_val;

    EXPECT_EQ(two_ints.at<0>(), third_val);
    EXPECT_EQ(two_ints.at<1>(), fourth_val); 
}

