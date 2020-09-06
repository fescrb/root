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
    constexpr static size_t ALIGNMENT = 1;

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
    EXPECT_CALL(allocator, malloc(ALLOCATION_SIZE, ALIGNMENT)).Times(1).WillOnce(Return(memory));
    
    root::buffer buffer(ALLOCATION_SIZE, ALIGNMENT, &allocator);

    EXPECT_EQ(buffer.size(), ALLOCATION_SIZE);
    EXPECT_TRUE(buffer);
    EXPECT_EQ(buffer.raw(), memory);

    EXPECT_CALL(allocator, free(memory, ALLOCATION_SIZE, ALIGNMENT)).Times(1);
}

TEST_F(buffer_tests, move_init) {
    EXPECT_CALL(allocator, malloc(ALLOCATION_SIZE, ALIGNMENT)).Times(1).WillOnce(Return(memory));
    
    root::buffer buffer(ALLOCATION_SIZE, ALIGNMENT, &allocator);

    EXPECT_EQ(buffer.size(), ALLOCATION_SIZE);
    EXPECT_TRUE(buffer);
    EXPECT_EQ(buffer.raw(), memory);
   
    root::buffer move_buffer(std::move(buffer));

    EXPECT_EQ(move_buffer.size(), ALLOCATION_SIZE);
    EXPECT_TRUE(move_buffer);
    EXPECT_EQ(move_buffer.raw(), memory);
    EXPECT_EQ(buffer.size(), 0);
    EXPECT_FALSE(buffer);

    EXPECT_CALL(allocator, free(memory, ALLOCATION_SIZE, ALIGNMENT)).Times(1);
}

TEST_F(buffer_tests, move_assign) {
    EXPECT_CALL(allocator, malloc(ALLOCATION_SIZE, ALIGNMENT)).Times(1).WillOnce(Return(memory));
    
    root::buffer buffer(ALLOCATION_SIZE, ALIGNMENT, &allocator);
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

    EXPECT_CALL(allocator, free(memory, ALLOCATION_SIZE, ALIGNMENT)).Times(1);
}

TEST_F(buffer_tests, buffer_offset) {
    EXPECT_CALL(allocator, malloc(ALLOCATION_SIZE, ALIGNMENT)).Times(1).WillOnce(Return(memory));
    constexpr size_t OFFSET = ALLOCATION_SIZE/2;
    constexpr size_t REMAINDER = ALLOCATION_SIZE - OFFSET;
    constexpr size_t SECOND_OFFSET = REMAINDER/2;
    constexpr size_t SECOND_REMAINDER = REMAINDER - SECOND_OFFSET;
    root::buffer buffer(ALLOCATION_SIZE, ALIGNMENT, &allocator);

    root::buffer::view offset = buffer + OFFSET;

    EXPECT_TRUE(offset);

    EXPECT_NE(buffer.raw(), offset.raw());
    EXPECT_EQ(offset.size(), REMAINDER);

    root::buffer::view second_offset = offset + SECOND_OFFSET;
    
    EXPECT_TRUE(second_offset);

    EXPECT_NE(buffer.raw(), second_offset.raw());
    EXPECT_NE(offset.raw(), second_offset.raw());
    EXPECT_EQ(second_offset.size(), SECOND_REMAINDER);

    root::buffer moved_buffer(std::move(buffer));
    
    EXPECT_FALSE(offset);
    EXPECT_FALSE(second_offset);

    EXPECT_CALL(allocator, free(memory, ALLOCATION_SIZE, ALIGNMENT)).Times(1);
}


TEST_F(buffer_tests, buffer_range) {
    EXPECT_CALL(allocator, malloc(ALLOCATION_SIZE, ALIGNMENT)).Times(1).WillOnce(Return(memory));
    
    root::buffer buffer(ALLOCATION_SIZE, ALIGNMENT, &allocator);

    EXPECT_EQ(static_cast<root::buffer::view>(buffer).size(), buffer.size());
    EXPECT_EQ(static_cast<root::buffer::view>(buffer).raw(), buffer.raw());

    constexpr size_t OFFSET = ALLOCATION_SIZE / 4;
    constexpr size_t END = OFFSET + (ALLOCATION_SIZE / 2);

    root::buffer::view range = buffer.range(OFFSET, END);

    EXPECT_EQ(range.size(), END - OFFSET);
    EXPECT_EQ(range.raw(), buffer + OFFSET);
    EXPECT_TRUE(range);

    root::buffer::view second_range = range.at(OFFSET);

    EXPECT_EQ(second_range.size(), END - (OFFSET*2));
    EXPECT_EQ(second_range.raw(), buffer + (OFFSET * 2));
    EXPECT_TRUE(second_range);

    root::buffer moved_buffer(std::move(buffer));
    
    EXPECT_FALSE(range);
    EXPECT_FALSE(second_range);

    EXPECT_CALL(allocator, free(memory, ALLOCATION_SIZE, ALIGNMENT)).Times(1);
}

TEST_F(buffer_tests, buffer_limit) {
    EXPECT_CALL(allocator, malloc(ALLOCATION_SIZE, ALIGNMENT)).Times(1).WillOnce(Return(memory));
    
    root::buffer buffer(ALLOCATION_SIZE, ALIGNMENT, &allocator);

    constexpr size_t LIMIT = ALLOCATION_SIZE / 2;

    root::buffer::view limit = buffer.limit(LIMIT);

    EXPECT_EQ(limit.size(), LIMIT);
    EXPECT_EQ(limit.raw(), buffer);
    EXPECT_TRUE(limit);

    constexpr size_t OFFSET = LIMIT / 2;

    root::buffer::view second_limit = limit.at(OFFSET);

    EXPECT_EQ(second_limit.size(), LIMIT - OFFSET);
    EXPECT_EQ(second_limit.raw(), buffer + OFFSET);
    EXPECT_TRUE(second_limit);

    root::buffer moved_buffer(std::move(buffer));
    
    EXPECT_FALSE(limit);
    EXPECT_FALSE(second_limit);

    EXPECT_CALL(allocator, free(memory, ALLOCATION_SIZE, ALIGNMENT)).Times(1);
}

TEST_F(buffer_tests, memcpy_buffer) {
    char const* MESSAGE = "Hello failing test";
    const size_t MESSAGE_LENGTH = strlen(MESSAGE);
    EXPECT_CALL(allocator, malloc(MESSAGE_LENGTH, alignof(char))).Times(1).WillOnce(Return(memory));
    
    root::buffer buffer(MESSAGE_LENGTH, alignof(char), &allocator);

    EXPECT_EQ(buffer.size(), MESSAGE_LENGTH);
    EXPECT_TRUE(buffer);
    EXPECT_EQ(buffer.raw(), memory);

    memcpy(buffer, MESSAGE, MESSAGE_LENGTH);

    EXPECT_EQ(memcmp(MESSAGE, buffer.raw(), MESSAGE_LENGTH), 0);

    char const* MODIFICATION = "passing";
    const size_t MODIFICATION_LENGTH = strlen(MODIFICATION);
    const size_t MODIFICATION_START = 6; // Just after "Hello "
    char const* MODIFIED_MESSAGE = "Hello passing test";

    memcpy(buffer + MODIFICATION_START, MODIFICATION, MODIFICATION_LENGTH);

    EXPECT_EQ(memcmp(MODIFIED_MESSAGE, buffer.raw(), MESSAGE_LENGTH), 0);

    EXPECT_CALL(allocator, free(memory, MESSAGE_LENGTH, alignof(char))).Times(1);
}