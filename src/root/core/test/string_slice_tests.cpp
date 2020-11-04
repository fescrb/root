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

#include <root/core/string_slice.h>

#include <gtest/gtest.h>

#include <cstring>
#include <limits>

class string_slice_tests : public ::testing::Test {
public:
    void SetUp() override {
        for(int i = 0; i < STRING_SIZE; i++)
            memory[i] = rand() % std::numeric_limits<char>::max();
    }

    void TearDown() override {
    }

    constexpr inline static size_t STRING_SIZE = 512;

    char memory[STRING_SIZE];
};

TEST_F(string_slice_tests, empty_init) {
    root::string_slice string;

    EXPECT_FALSE(string);
    EXPECT_EQ(string.size(), 0);
}

TEST_F(string_slice_tests, init) {
    root::string_slice string(memory, 0, STRING_SIZE);

    EXPECT_TRUE(string);
    EXPECT_EQ(string.size(), STRING_SIZE);
    EXPECT_EQ(memcmp(string, memory, STRING_SIZE*sizeof(int)), 0);
}

TEST_F(string_slice_tests, init_copy) {
    root::string_slice string(memory, 0, STRING_SIZE);
    root::string_slice copy_string(string);

    EXPECT_TRUE(copy_string);
    EXPECT_EQ(copy_string.size(), STRING_SIZE);
    EXPECT_EQ(memcmp(string, memory, STRING_SIZE*sizeof(int)), 0);
    EXPECT_EQ(memcmp(copy_string, memory, STRING_SIZE*sizeof(int)), 0);
}

TEST_F(string_slice_tests, init_move) {
    root::string_slice string(memory, 0, STRING_SIZE);
    root::string_slice move_array(std::move(string));

    EXPECT_TRUE(move_array);
    EXPECT_EQ(move_array.size(), STRING_SIZE);
    EXPECT_EQ(memcmp(move_array, memory, STRING_SIZE*sizeof(int)), 0);
}

TEST_F(string_slice_tests, copy_assign) {
    root::string_slice string(memory, 0, STRING_SIZE);
    root::string_slice copy_string;
    
    copy_string = string;

    EXPECT_TRUE(copy_string);
    EXPECT_EQ(copy_string.size(), STRING_SIZE);
    EXPECT_EQ(memcmp(string, memory, STRING_SIZE*sizeof(int)), 0);
    EXPECT_EQ(memcmp(copy_string, memory, STRING_SIZE*sizeof(int)), 0);
}

TEST_F(string_slice_tests, move_assign) {
    root::string_slice string(memory, 0, STRING_SIZE);
    root::string_slice move_array;
    
    move_array = std::move(string);

    EXPECT_TRUE(move_array);
    EXPECT_EQ(move_array.size(), STRING_SIZE);
    EXPECT_EQ(memcmp(move_array, memory, STRING_SIZE*sizeof(int)), 0);
}

TEST_F(string_slice_tests, index_op_const) {
    const root::string_slice string(memory, 0, STRING_SIZE);
    
    for(int i = 0; i < STRING_SIZE; i++)
        EXPECT_EQ(string[i], memory[i]);
}

TEST_F(string_slice_tests, index_op) {
    int second_array[STRING_SIZE];
    for(int i = 0; i < STRING_SIZE; i++)
        second_array[i] = rand() % std::numeric_limits<char>::max();
    
    root::string_slice string(memory, 0, STRING_SIZE);

    for(int i = 0; i < STRING_SIZE; i++)
        string[i] = second_array[i];

    EXPECT_EQ(memcmp(string, memory, STRING_SIZE*sizeof(int)), 0);
}

TEST_F(string_slice_tests, offset) {
    constexpr int OFFSET = STRING_SIZE/2;
    root::string_slice string(memory, 0, STRING_SIZE);

    root::string_slice offset_string = string.offset(OFFSET);

    EXPECT_TRUE(offset_string);
    EXPECT_EQ(offset_string.size(), STRING_SIZE - OFFSET);
    EXPECT_EQ(memcmp(offset_string, memory + OFFSET, offset_string.size()*sizeof(int)), 0);
}

TEST_F(string_slice_tests, limit) {
    constexpr int LIMIT = STRING_SIZE/4;
    root::string_slice string(memory, 0, STRING_SIZE);

    root::string_slice limit_array = string.limit(LIMIT);

    EXPECT_TRUE(limit_array);
    EXPECT_EQ(limit_array.size(), LIMIT);
    EXPECT_EQ(memcmp(limit_array, memory, limit_array.size()*sizeof(int)), 0);
}

TEST_F(string_slice_tests, range) {
    constexpr int OFFSET = STRING_SIZE/4;
    constexpr int LIMIT = STRING_SIZE/2;
    root::string_slice string(memory, 0, STRING_SIZE);

    root::string_slice range_array = string.range(OFFSET, LIMIT);

    EXPECT_TRUE(range_array);
    EXPECT_EQ(range_array.size(), LIMIT - OFFSET);
    EXPECT_EQ(memcmp(range_array, memory + OFFSET, range_array.size()*sizeof(int)), 0);
}