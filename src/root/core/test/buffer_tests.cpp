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

#include <root/core/buffer.h>
#include <root/memory/test/mock_allocator.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstdlib>
#include <cstring>

class buffer_tests : public ::testing::Test {
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

TEST_F(buffer_tests, empty_init) {
    root::buffer buffer;

    EXPECT_EQ(buffer.size(), 0);
    EXPECT_FALSE(buffer);
    EXPECT_EQ(buffer.raw(), nullptr);
}

TEST_F(buffer_tests, blank_init) {
    EXPECT_CALL(allocator, malloc(ALLOCATION_SIZE, 0)).Times(1).WillOnce(Return(memory));
    
    root::buffer buffer(ALLOCATION_SIZE, &allocator);

    EXPECT_EQ(buffer.size(), ALLOCATION_SIZE);
    EXPECT_TRUE(buffer);
    EXPECT_EQ(buffer.raw(), memory);

    EXPECT_CALL(allocator, free(memory, ALLOCATION_SIZE, 0)).Times(1);
}

TEST_F(buffer_tests, move_init) {
    EXPECT_CALL(allocator, malloc(ALLOCATION_SIZE, 0)).Times(1).WillOnce(Return(memory));
    
    root::buffer buffer(ALLOCATION_SIZE, &allocator);

    EXPECT_EQ(buffer.size(), ALLOCATION_SIZE);
    EXPECT_TRUE(buffer);
    EXPECT_EQ(buffer.raw(), memory);
   
    root::buffer move_buffer(std::move(buffer));

    EXPECT_EQ(move_buffer.size(), ALLOCATION_SIZE);
    EXPECT_TRUE(move_buffer);
    EXPECT_EQ(move_buffer.raw(), memory);
    EXPECT_EQ(buffer.size(), 0);
    EXPECT_FALSE(buffer);

    EXPECT_CALL(allocator, free(memory, ALLOCATION_SIZE, 0)).Times(1);
}

TEST_F(buffer_tests, move_assign) {
    EXPECT_CALL(allocator, malloc(ALLOCATION_SIZE, 0)).Times(1).WillOnce(Return(memory));
    
    root::buffer buffer(ALLOCATION_SIZE, &allocator);
    root::buffer move_buffer;

    EXPECT_EQ(buffer.size(), ALLOCATION_SIZE);
    EXPECT_TRUE(buffer);
    EXPECT_EQ(buffer.raw(), memory);
    EXPECT_EQ(move_buffer.size(), 0);
    EXPECT_FALSE(move_buffer);
    EXPECT_NE(move_buffer.raw(), memory);
   
    move_buffer = std::move(buffer);

    EXPECT_EQ(move_buffer.size(), ALLOCATION_SIZE);
    EXPECT_TRUE(move_buffer);
    EXPECT_EQ(move_buffer.raw(), memory);
    EXPECT_EQ(buffer.size(), 0);
    EXPECT_FALSE(buffer);
    EXPECT_NE(buffer.raw(), memory);

    EXPECT_CALL(allocator, free(memory, ALLOCATION_SIZE, 0)).Times(1);
}

TEST_F(buffer_tests, write_raw_buffer) {
    char const* MESSAGE = "Hello failing test";
    const size_t MESSAGE_LENGTH = strlen(MESSAGE);
    EXPECT_CALL(allocator, malloc(MESSAGE_LENGTH, 0)).Times(1).WillOnce(Return(memory));
    
    root::buffer buffer(MESSAGE_LENGTH, &allocator);

    EXPECT_EQ(buffer.size(), MESSAGE_LENGTH);
    EXPECT_TRUE(buffer);
    EXPECT_EQ(buffer.raw(), memory);

    buffer.write(0, MESSAGE, 0, MESSAGE_LENGTH);

    EXPECT_EQ(memcmp(MESSAGE, buffer.raw(), MESSAGE_LENGTH), 0);

    char const* MODIFICATION = "passing";
    const size_t MODIFICATION_LENGTH = strlen(MODIFICATION);
    const size_t MODIFICATION_START = 6; // Just after "Hello "
    char const* MODIFIED_MESSAGE = "Hello passing test";

    buffer.write(MODIFICATION_START, MODIFICATION, 0, MODIFICATION_LENGTH);

    EXPECT_EQ(memcmp(MODIFIED_MESSAGE, buffer.raw(), MESSAGE_LENGTH), 0);

    EXPECT_CALL(allocator, free(memory, MESSAGE_LENGTH, 0)).Times(1);
}

TEST_F(buffer_tests, write_buffer) {
    char const* MESSAGE = "Hello failing test";
    const size_t MESSAGE_LENGTH = strlen(MESSAGE);
    void* mem2 = malloc(ALLOCATION_SIZE);
    EXPECT_CALL(allocator, malloc(MESSAGE_LENGTH, 0)).Times(1).WillOnce(Return(memory));
    
    root::buffer buffer(MESSAGE_LENGTH, &allocator);

    EXPECT_EQ(buffer.size(), MESSAGE_LENGTH);
    EXPECT_TRUE(buffer);
    EXPECT_EQ(buffer.raw(), memory);

    {
        EXPECT_CALL(allocator, malloc(MESSAGE_LENGTH, 0)).Times(1).WillOnce(Return(mem2));
        root::buffer src_buffer(MESSAGE_LENGTH, &allocator);
        src_buffer.write(0, MESSAGE, 0, MESSAGE_LENGTH);
        buffer.write(0, src_buffer, 0, MESSAGE_LENGTH);

        EXPECT_EQ(memcmp(MESSAGE, buffer.raw(), MESSAGE_LENGTH), 0);
        EXPECT_EQ(memcmp(src_buffer.raw(), buffer.raw(), MESSAGE_LENGTH), 0);
        EXPECT_NE(src_buffer.raw(), buffer.raw());

        EXPECT_CALL(allocator, free(mem2, MESSAGE_LENGTH, 0)).Times(1);
    }

    char const* MODIFICATION = "passing";
    const size_t MODIFICATION_LENGTH = strlen(MODIFICATION);
    const size_t MODIFICATION_START = 6; // Just after "Hello "
    char const* MODIFIED_MESSAGE = "Hello passing test";
    
    {
        EXPECT_CALL(allocator, malloc(MODIFICATION_LENGTH, 0)).Times(1).WillOnce(Return(mem2));
        root::buffer src_buffer(MODIFICATION_LENGTH, &allocator);
        src_buffer.write(0, MODIFICATION, 0, MODIFICATION_LENGTH);
        buffer.write(MODIFICATION_START, src_buffer, 0, MODIFICATION_LENGTH);

        EXPECT_EQ(memcmp(MODIFIED_MESSAGE, buffer.raw(), MESSAGE_LENGTH), 0);
        EXPECT_NE(src_buffer.raw(), buffer.raw());

        EXPECT_CALL(allocator, free(mem2, MODIFICATION_LENGTH, 0)).Times(1);
    }

    buffer.write(MODIFICATION_START, MODIFICATION, 0, MODIFICATION_LENGTH);
    
    EXPECT_EQ(memcmp(MODIFIED_MESSAGE, buffer.raw(), MESSAGE_LENGTH), 0);

    EXPECT_CALL(allocator, free(memory, MESSAGE_LENGTH, 0)).Times(1);
    
    free(mem2);
}