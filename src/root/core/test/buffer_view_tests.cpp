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

#include <root/core/buffer_view.h>

#include <gtest/gtest.h>

#include <cstdlib>
#include <cstring>

class buffer_view_tests : public ::testing::Test {
public:
    void SetUp() override {
        memory = malloc(ALLOCATION_SIZE);
    }

    void TearDown() override {
        free(memory);
    }

    constexpr static size_t ALLOCATION_SIZE = 512;

    void* memory;
};

TEST_F(buffer_view_tests, blank_init) {
    root::buffer_view buffer_view(memory, 0, ALLOCATION_SIZE);

    EXPECT_EQ(buffer_view.size(), ALLOCATION_SIZE);
    EXPECT_TRUE(buffer_view);
    EXPECT_EQ(buffer_view.data(), memory);
}

TEST_F(buffer_view_tests, move_init) {
    root::buffer_view buffer_view(memory, 0, ALLOCATION_SIZE);

    EXPECT_EQ(buffer_view.size(), ALLOCATION_SIZE);
    EXPECT_TRUE(buffer_view);
    EXPECT_EQ(buffer_view.data(), memory);
   
    root::buffer_view move_buffer(std::move(buffer_view));

    EXPECT_EQ(move_buffer.size(), ALLOCATION_SIZE);
    EXPECT_TRUE(move_buffer);
    EXPECT_EQ(move_buffer.data(), memory);
}

TEST_F(buffer_view_tests, buffer_offset) {
    constexpr size_t OFFSET = ALLOCATION_SIZE/2;
    constexpr size_t REMAINDER = ALLOCATION_SIZE - OFFSET;
    constexpr size_t SECOND_OFFSET = REMAINDER/2;
    constexpr size_t SECOND_REMAINDER = REMAINDER - SECOND_OFFSET;
    root::buffer_view buffer_view(memory, 0, ALLOCATION_SIZE);

    root::buffer_view offset = buffer_view + OFFSET;

    EXPECT_TRUE(offset);

    EXPECT_NE(buffer_view.data(), offset.data());
    EXPECT_EQ(offset.size(), REMAINDER);

    root::buffer_view second_offset = offset + SECOND_OFFSET;
    
    EXPECT_TRUE(second_offset);

    EXPECT_NE(buffer_view.data(), second_offset.data());
    EXPECT_NE(offset.data(), second_offset.data());
    EXPECT_EQ(second_offset.size(), SECOND_REMAINDER);
}


TEST_F(buffer_view_tests, buffer_range) {
    root::buffer_view buffer_view(memory, 0, ALLOCATION_SIZE);

    constexpr size_t OFFSET = ALLOCATION_SIZE / 4;
    constexpr size_t END = OFFSET + (ALLOCATION_SIZE / 2);

    root::buffer_view range = buffer_view.range(OFFSET, END);

    EXPECT_EQ(range.size(), END - OFFSET);
    EXPECT_EQ(range.data(), buffer_view + OFFSET);
    EXPECT_TRUE(range);

    root::buffer_view second_range = range.offset(OFFSET);

    EXPECT_EQ(second_range.size(), END - (OFFSET*2));
    EXPECT_EQ(second_range.data(), buffer_view + (OFFSET * 2));
    EXPECT_TRUE(second_range);
}

TEST_F(buffer_view_tests, buffer_limit) {
    root::buffer_view buffer_view(memory, 0, ALLOCATION_SIZE);

    constexpr size_t LIMIT = ALLOCATION_SIZE / 2;

    root::buffer_view limit = buffer_view.limit(LIMIT);

    EXPECT_EQ(limit.size(), LIMIT);
    EXPECT_EQ(limit.data(), buffer_view);
    EXPECT_TRUE(limit);

    constexpr size_t OFFSET = LIMIT / 2;

    root::buffer_view second_limit = limit.offset(OFFSET);

    EXPECT_EQ(second_limit.size(), LIMIT - OFFSET);
    EXPECT_EQ(second_limit.data(), buffer_view + OFFSET);
    EXPECT_TRUE(second_limit);
}

TEST_F(buffer_view_tests, memcpy_buffer) {
    char const* MESSAGE = "Hello failing test";
    const size_t MESSAGE_LENGTH = strlen(MESSAGE);
    
    root::buffer_view buffer_view(memory, 0, MESSAGE_LENGTH);

    EXPECT_EQ(buffer_view.size(), MESSAGE_LENGTH);
    EXPECT_TRUE(buffer_view);
    EXPECT_EQ(buffer_view.data(), memory);

    memcpy(buffer_view, MESSAGE, MESSAGE_LENGTH);

    EXPECT_EQ(memcmp(MESSAGE, buffer_view.data(), MESSAGE_LENGTH), 0);

    char const* MODIFICATION = "passing";
    const size_t MODIFICATION_LENGTH = strlen(MODIFICATION);
    const size_t MODIFICATION_START = 6; // Just after "Hello "
    char const* MODIFIED_MESSAGE = "Hello passing test";

    memcpy(buffer_view + MODIFICATION_START, MODIFICATION, MODIFICATION_LENGTH);

    EXPECT_EQ(memcmp(MODIFIED_MESSAGE, buffer_view.data(), MESSAGE_LENGTH), 0);
}