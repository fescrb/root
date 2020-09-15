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

#include <root/io/reader.h>
#include <root/io/test/mock_stream.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstdlib>
#include <cstring>

class reader_tests : public ::testing::Test {
public:
    reader_tests() 
    :   stream(), reader(&stream) {}

    void SetUp() override {
    }

    void TearDown() override {}

    constexpr static size_t BUFFER_SIZE = 512;
    root::mock_stream stream;
    root::reader reader;
};

using ::testing::Return;

TEST_F(reader_tests, tell) {
    EXPECT_CALL(stream, tell(root::relative_to::start)).Times(1).WillOnce(Return(0));
    EXPECT_EQ(reader.tell(), 0);

    // Now error
    EXPECT_CALL(stream, tell(root::relative_to::start)).Times(1).WillOnce(Return(root::error::DEAD_OBJECT));
    EXPECT_EQ(reader.tell(), root::error::DEAD_OBJECT);
} 

TEST_F(reader_tests, seek) {
    EXPECT_CALL(stream, seek(50, root::relative_to::start)).Times(1).WillOnce(Return(root::error::NO_ERROR));
    EXPECT_EQ(reader.seek(50), root::error::NO_ERROR);
} 

TEST_F(reader_tests, write) {
    const size_t BUFFER_SIZE = 512;
    char buffer[BUFFER_SIZE];
    EXPECT_CALL(stream, read(buffer, BUFFER_SIZE)).Times(1).WillOnce(Return(root::error::NO_ERROR));
    EXPECT_EQ(reader.read(buffer, BUFFER_SIZE), root::error::NO_ERROR);
} 