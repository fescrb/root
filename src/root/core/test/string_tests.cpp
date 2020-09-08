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

#include <root/core/string.h>
#include <root/memory/test/mock_allocator.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstdlib>

class string_tests : public ::testing::Test {
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

TEST_F(string_tests, string_literal_initializer) {
    const char* TEST_STRING = "Hello Tests!";
    const int STRING_LENGTH = strlen(TEST_STRING);
    EXPECT_CALL(allocator, malloc(sizeof(char) * STRING_LENGTH, alignof(char))).Times(1).WillOnce(Return(memory));
    
    root::string str(TEST_STRING, &allocator);

    EXPECT_EQ(str.length(), STRING_LENGTH);

    for(int i = 0; i < STRING_LENGTH; i++) {
        EXPECT_EQ(str[i], TEST_STRING[i]);
    }

    EXPECT_CALL(allocator, free(memory, sizeof(char) * STRING_LENGTH, alignof(char))).Times(1);
}

TEST_F(string_tests, move_init) {
    const char* TEST_STRING = "Hello Tests!";
    const int STRING_LENGTH = strlen(TEST_STRING);
    EXPECT_CALL(allocator, malloc(sizeof(char) * STRING_LENGTH, alignof(char))).Times(1).WillOnce(Return(memory));
    
    root::string str(TEST_STRING, &allocator);
    root::string moved_str(std::move(str));

    EXPECT_EQ(moved_str.length(), STRING_LENGTH);

    for(int i = 0; i < STRING_LENGTH; i++) {
        EXPECT_EQ(moved_str[i], TEST_STRING[i]);
    }

    EXPECT_CALL(allocator, free(memory, sizeof(char) * STRING_LENGTH, alignof(char))).Times(1);
}