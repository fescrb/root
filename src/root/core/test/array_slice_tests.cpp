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

#include <root/core/array_slice.h>

#include <gtest/gtest.h>

#include <cstring>

class array_slice_tests : public ::testing::Test {
public:
    void SetUp() override {
        for(int i = 0; i < ARRAY_SIZE; i++)
            memory[i] = rand();
    }

    void TearDown() override {
    }

    constexpr static size_t ARRAY_SIZE = 512;

    int memory[ARRAY_SIZE];
};

TEST_F(array_slice_tests, empty_init) {
    root::array_slice<int> array;

    EXPECT_FALSE(array);
    EXPECT_EQ(array.size(), 0);
}

TEST_F(array_slice_tests, init) {
    root::array_slice<int> array(memory, 0, ARRAY_SIZE);

    EXPECT_TRUE(array);
    EXPECT_EQ(array.size(), ARRAY_SIZE);
    EXPECT_EQ(memcmp(array, memory, ARRAY_SIZE*sizeof(int)), 0);
}

TEST_F(array_slice_tests, init_copy) {
    root::array_slice<int> array(memory, 0, ARRAY_SIZE);
    root::array_slice<int> copy_array(array);

    EXPECT_TRUE(copy_array);
    EXPECT_EQ(copy_array.size(), ARRAY_SIZE);
    EXPECT_EQ(memcmp(array, memory, ARRAY_SIZE*sizeof(int)), 0);
    EXPECT_EQ(memcmp(copy_array, memory, ARRAY_SIZE*sizeof(int)), 0);
}

TEST_F(array_slice_tests, init_move) {
    root::array_slice<int> array(memory, 0, ARRAY_SIZE);
    root::array_slice<int> move_array(std::move(array));

    EXPECT_TRUE(move_array);
    EXPECT_EQ(move_array.size(), ARRAY_SIZE);
    EXPECT_EQ(memcmp(move_array, memory, ARRAY_SIZE*sizeof(int)), 0);
}

TEST_F(array_slice_tests, copy_assign) {
    root::array_slice<int> array(memory, 0, ARRAY_SIZE);
    root::array_slice<int> copy_array;
    
    copy_array = array;

    EXPECT_TRUE(copy_array);
    EXPECT_EQ(copy_array.size(), ARRAY_SIZE);
    EXPECT_EQ(memcmp(array, memory, ARRAY_SIZE*sizeof(int)), 0);
    EXPECT_EQ(memcmp(copy_array, memory, ARRAY_SIZE*sizeof(int)), 0);
}

TEST_F(array_slice_tests, move_assign) {
    root::array_slice<int> array(memory, 0, ARRAY_SIZE);
    root::array_slice<int> move_array;
    
    move_array = std::move(array);

    EXPECT_TRUE(move_array);
    EXPECT_EQ(move_array.size(), ARRAY_SIZE);
    EXPECT_EQ(memcmp(move_array, memory, ARRAY_SIZE*sizeof(int)), 0);
}

TEST_F(array_slice_tests, index_op_const) {
    const root::array_slice<int> array(memory, 0, ARRAY_SIZE);
    
    for(int i = 0; i < ARRAY_SIZE; i++)
        EXPECT_EQ(array[i], memory[i]);
}

TEST_F(array_slice_tests, index_op) {
    int second_array[ARRAY_SIZE];
    for(int i = 0; i < ARRAY_SIZE; i++)
        second_array[i] = rand();
    
    root::array_slice<int> array(memory, 0, ARRAY_SIZE);

    for(int i = 0; i < ARRAY_SIZE; i++)
        array[i] = second_array[i];

    EXPECT_EQ(memcmp(array, memory, ARRAY_SIZE*sizeof(int)), 0);
}

TEST_F(array_slice_tests, offset) {
    constexpr int OFFSET = ARRAY_SIZE/2;
    root::array_slice<int> array(memory, 0, ARRAY_SIZE);

    root::array_slice<int> offset_array = array.offset(OFFSET);

    EXPECT_TRUE(offset_array);
    EXPECT_EQ(offset_array.size(), ARRAY_SIZE - OFFSET);
    EXPECT_EQ(memcmp(offset_array, memory + OFFSET, offset_array.size()*sizeof(int)), 0);
}

TEST_F(array_slice_tests, limit) {
    constexpr int LIMIT = ARRAY_SIZE/4;
    root::array_slice<int> array(memory, 0, ARRAY_SIZE);

    root::array_slice<int> limit_array = array.limit(LIMIT);

    EXPECT_TRUE(limit_array);
    EXPECT_EQ(limit_array.size(), LIMIT);
    EXPECT_EQ(memcmp(limit_array, memory, limit_array.size()*sizeof(int)), 0);
}

TEST_F(array_slice_tests, range) {
    constexpr int OFFSET = ARRAY_SIZE/4;
    constexpr int LIMIT = ARRAY_SIZE/2;
    root::array_slice<int> array(memory, 0, ARRAY_SIZE);

    root::array_slice<int> range_array = array.range(OFFSET, LIMIT);

    EXPECT_TRUE(range_array);
    EXPECT_EQ(range_array.size(), LIMIT - OFFSET);
    EXPECT_EQ(memcmp(range_array, memory + OFFSET, range_array.size()*sizeof(int)), 0);
}