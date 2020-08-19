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

#include <root/core/array.h>
#include <root/memory/test/mock_allocator.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstdlib>

class array_tests : public ::testing::Test {
public:
    void SetUp() override {
        memory = malloc(ALLOCATION_SIZE);
    }

    void TearDown() override {
        free(memory);
    }

    constexpr static size_t ALLOCATION_SIZE = 512;

    root::mock_allocator allocator;
    void* memory;
};


using ::testing::Return;

TEST_F(array_tests, blank_init) {
    constexpr uint64_t ARRAY_SIZE = 6;
    EXPECT_CALL(allocator, malloc(sizeof(int) * ARRAY_SIZE, alignof(int))).Times(1).WillOnce(Return(memory));
    
    root::array<int> array(ARRAY_SIZE, &allocator);

    EXPECT_EQ(array.length(), ARRAY_SIZE);

    EXPECT_CALL(allocator, free(memory, sizeof(int) * ARRAY_SIZE, alignof(int))).Times(1);
}

TEST_F(array_tests, index_operator) {
    constexpr uint64_t ARRAY_SIZE = 6;
    EXPECT_CALL(allocator, malloc(sizeof(int) * ARRAY_SIZE, alignof(int))).Times(1).WillOnce(Return(memory));
    
    root::array<int> array(ARRAY_SIZE, &allocator);
    int basic_array[ARRAY_SIZE];
    
    for(int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = basic_array[i] = rand();
    }

    for(int i = 0; i < ARRAY_SIZE; i++) {
        EXPECT_EQ(array[i], basic_array[i]);
    }

    EXPECT_CALL(allocator, free(memory, sizeof(int) * ARRAY_SIZE, alignof(int))).Times(1);
}

TEST_F(array_tests, initializer_lists) {
    constexpr uint64_t ARRAY_SIZE = 6;
    EXPECT_CALL(allocator, malloc(sizeof(int) * ARRAY_SIZE, alignof(int))).Times(1).WillOnce(Return(memory));
    
    root::array<int> array({1, 2, 3, 4, 5, 6}, &allocator);
    int basic_array[ARRAY_SIZE] = {1, 2, 3, 4, 5, 6};

    
    EXPECT_EQ(array.length(), ARRAY_SIZE);

    for(int i = 0; i < ARRAY_SIZE; i++) {
        EXPECT_EQ(array[i], basic_array[i]);
    }

    EXPECT_CALL(allocator, free(memory, sizeof(int) * ARRAY_SIZE, alignof(int))).Times(1);
}

TEST_F(array_tests, raw) {
    constexpr uint64_t ARRAY_SIZE = 6;
    EXPECT_CALL(allocator, malloc(sizeof(int) * ARRAY_SIZE, alignof(int))).Times(1).WillOnce(Return(memory));
    
    root::array<int> array({1, 2, 3, 4, 5, 6}, &allocator);
    int basic_array[ARRAY_SIZE] = {1, 2, 3, 4, 5, 6};

    EXPECT_EQ(array.raw(), memory);

    for(int i = 0; i < ARRAY_SIZE; i++) {
        EXPECT_EQ(array.raw()[i], basic_array[i]);
    }

    EXPECT_CALL(allocator, free(memory, sizeof(int) * ARRAY_SIZE, alignof(int))).Times(1);
}

TEST_F(array_tests, const_index) {
    constexpr uint64_t ARRAY_SIZE = 6;
    EXPECT_CALL(allocator, malloc(sizeof(int) * ARRAY_SIZE, alignof(int))).Times(1).WillOnce(Return(memory));
    
    const root::array<int> array({1, 2, 3, 4, 5, 6}, &allocator);
    int basic_array[ARRAY_SIZE] = {1, 2, 3, 4, 5, 6};

    for(int i = 0; i < ARRAY_SIZE; i++) {
        EXPECT_EQ(array[i], basic_array[i]);
    }

    EXPECT_CALL(allocator, free(memory, sizeof(int) * ARRAY_SIZE, alignof(int))).Times(1);
}