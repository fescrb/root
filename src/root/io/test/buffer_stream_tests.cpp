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

#include <root/io/buffer_stream.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstdlib>
#include <cstring>

class buffer_stream_tests : public ::testing::Test {
public:
    buffer_stream_tests() 
    :   buffer(BUFFER_SIZE),
        stream(buffer) {

    }

    void SetUp() override {
    }

    void TearDown() override {}

    constexpr static size_t BUFFER_SIZE = 512;
    root::buffer buffer;
    root::buffer_stream stream;
};

TEST_F(buffer_stream_tests, tell) {
    EXPECT_EQ(stream.tell(), 0);
    EXPECT_EQ(stream.tell(root::relative_to::current_position), 0);
    EXPECT_EQ(stream.tell(root::relative_to::end), -BUFFER_SIZE);
}

TEST_F(buffer_stream_tests, seek_from_start) {
    constexpr int NUM_TESTS = 10;
    for(int _ = 0; _ < NUM_TESTS; _++) {
        int position = rand() % BUFFER_SIZE;
        EXPECT_EQ(stream.seek(position), root::error::NO_ERROR);
        EXPECT_EQ(stream.tell(), position);
        EXPECT_EQ(stream.tell(root::relative_to::current_position), 0);
        EXPECT_EQ(stream.tell(root::relative_to::end), position - BUFFER_SIZE);
    }
}

TEST_F(buffer_stream_tests, seek_from_end) {
    constexpr int NUM_TESTS = 10;
    for(int _ = 0; _ < NUM_TESTS; _++) {
        int position = rand() % BUFFER_SIZE;
        EXPECT_EQ(stream.seek(-position, root::relative_to::end), root::error::NO_ERROR);
        EXPECT_EQ(stream.tell(), BUFFER_SIZE - position);
        EXPECT_EQ(stream.tell(root::relative_to::current_position), 0);
        EXPECT_EQ(stream.tell(root::relative_to::end), -position);
    }
}

TEST_F(buffer_stream_tests, seek_relative) {
    constexpr int NUM_TESTS = 10;
    constexpr int MAX_MOVE = BUFFER_SIZE / NUM_TESTS;
    int position = BUFFER_SIZE / 2;
    EXPECT_EQ(stream.seek(position), root::error::NO_ERROR);
    EXPECT_EQ(stream.tell(), position);
    for(int _ = 0; _ < NUM_TESTS; _++) {
        int move = (rand() % MAX_MOVE) - (MAX_MOVE / 2);
        position += move;
        EXPECT_EQ(stream.seek(move, root::relative_to::current_position), root::error::NO_ERROR);
        EXPECT_EQ(stream.tell(), position);
        EXPECT_EQ(stream.tell(root::relative_to::current_position), 0);
        EXPECT_EQ(stream.tell(root::relative_to::end), position - BUFFER_SIZE);
    }
}

TEST_F(buffer_stream_tests, write) {
    char raw_buffer[BUFFER_SIZE];
    int* buffer_as_ints = reinterpret_cast<int*>(raw_buffer);
    for(int i = 0; i < (BUFFER_SIZE/sizeof(int)); i++) {
        buffer_as_ints[i] = rand();
    }

    constexpr int NUM_WRITES = 4;
    constexpr int WRITE_SIZE = BUFFER_SIZE / NUM_WRITES;

    for(int i = 0; i < NUM_WRITES; i++) {
        EXPECT_EQ(stream.tell(), i * WRITE_SIZE);
        EXPECT_EQ(stream.tell(root::relative_to::current_position), 0);
        EXPECT_EQ(stream.tell(root::relative_to::end), (i * WRITE_SIZE) - BUFFER_SIZE);

        EXPECT_EQ(stream.write(&(raw_buffer[i*WRITE_SIZE]), WRITE_SIZE), root::error::NO_ERROR);
    }

    EXPECT_EQ(stream.tell(), BUFFER_SIZE);
    EXPECT_EQ(stream.tell(root::relative_to::current_position), 0);
    EXPECT_EQ(stream.tell(root::relative_to::end), 0);

    EXPECT_EQ(memcmp(buffer, reinterpret_cast<void*>(raw_buffer), BUFFER_SIZE), 0);
}

TEST_F(buffer_stream_tests, write_errors) {
    char raw_buffer[BUFFER_SIZE];
    int* buffer_as_ints = reinterpret_cast<int*>(raw_buffer);
    for(int i = 0; i < (BUFFER_SIZE/sizeof(int)); i++) {
        buffer_as_ints[i] = rand();
    }

    // Set to invalid state
    constexpr int ERROR_POS = -1;
    EXPECT_EQ(stream.seek(ERROR_POS), root::error::NO_ERROR);
    
    constexpr int NUM_WRITES = 4;
    constexpr int WRITE_SIZE = BUFFER_SIZE / NUM_WRITES;
    for(int i = 0; i < NUM_WRITES; i++) {
        EXPECT_EQ(stream.tell(), ERROR_POS);
        EXPECT_EQ(stream.tell(root::relative_to::current_position), 0);
        EXPECT_EQ(stream.tell(root::relative_to::end), ERROR_POS - BUFFER_SIZE);

        EXPECT_EQ(stream.write(&(raw_buffer[i*WRITE_SIZE]), WRITE_SIZE), root::error::INVALID_OPERATION);
    }

    EXPECT_NE(memcmp(buffer, raw_buffer, BUFFER_SIZE), 0);

    constexpr int OVERFLOW_POS = BUFFER_SIZE - 1;

    EXPECT_EQ(stream.seek(OVERFLOW_POS), root::error::NO_ERROR);

    EXPECT_EQ(stream.write(&raw_buffer, WRITE_SIZE), root::error::INVALID_OPERATION);
    EXPECT_NE(memcmp(buffer, raw_buffer, BUFFER_SIZE), 0);
}

TEST_F(buffer_stream_tests, read) {
    char raw_buffer[BUFFER_SIZE];
    int* buffer_as_ints = reinterpret_cast<int*>(buffer.raw());
    for(int i = 0; i < (BUFFER_SIZE/sizeof(int)); i++) {
        buffer_as_ints[i] = rand();
    }

    constexpr int NUM_WRITES = 4;
    constexpr int READ_SIZE = BUFFER_SIZE / NUM_WRITES;

    for(int i = 0; i < NUM_WRITES; i++) {
        EXPECT_EQ(stream.tell(), i * READ_SIZE);
        EXPECT_EQ(stream.tell(root::relative_to::current_position), 0);
        EXPECT_EQ(stream.tell(root::relative_to::end), (i * READ_SIZE) - BUFFER_SIZE);

        EXPECT_EQ(stream.read(&(raw_buffer[i*READ_SIZE]), READ_SIZE), root::error::NO_ERROR);
    }

    EXPECT_EQ(stream.tell(), BUFFER_SIZE);
    EXPECT_EQ(stream.tell(root::relative_to::current_position), 0);
    EXPECT_EQ(stream.tell(root::relative_to::end), 0);

    EXPECT_EQ(memcmp(buffer, reinterpret_cast<void*>(raw_buffer), BUFFER_SIZE), 0);
}

TEST_F(buffer_stream_tests, read_errors) {
    char raw_buffer[BUFFER_SIZE];
    int* buffer_as_ints = reinterpret_cast<int*>(buffer.raw());
    for(int i = 0; i < (BUFFER_SIZE/sizeof(int)); i++) {
        buffer_as_ints[i] = rand();
    }

    // Set to invalid state
    constexpr int ERROR_POS = -1;
    EXPECT_EQ(stream.seek(ERROR_POS), root::error::NO_ERROR);
    
    constexpr int NUM_WRITES = 4;
    constexpr int READ_SIZE = BUFFER_SIZE / NUM_WRITES;
    for(int i = 0; i < NUM_WRITES; i++) {
        EXPECT_EQ(stream.tell(), ERROR_POS);
        EXPECT_EQ(stream.tell(root::relative_to::current_position), 0);
        EXPECT_EQ(stream.tell(root::relative_to::end), ERROR_POS - BUFFER_SIZE);

        EXPECT_EQ(stream.read(&(raw_buffer[i*READ_SIZE]), READ_SIZE), root::error::INVALID_OPERATION);
    }

    EXPECT_NE(memcmp(buffer, raw_buffer, BUFFER_SIZE), 0);

    constexpr int OVERFLOW_POS = BUFFER_SIZE - 1;

    EXPECT_EQ(stream.seek(OVERFLOW_POS), root::error::NO_ERROR);

    EXPECT_EQ(stream.read(&raw_buffer, READ_SIZE), root::error::INVALID_OPERATION);
    EXPECT_NE(memcmp(buffer, raw_buffer, BUFFER_SIZE), 0);
}