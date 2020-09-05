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

#include <root/io/writer.h>
#include <root/io/test/mock_stream.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstdlib>
#include <cstring>

class writer_tests : public ::testing::Test {
public:
    writer_tests() 
    :   stream(), writer(&stream) {}

    void SetUp() override {
    }

    void TearDown() override {}

    constexpr static size_t BUFFER_SIZE = 512;
    root::mock_stream stream;
    root::writer writer;
};

using ::testing::Return;

TEST_F(writer_tests, tell) {
    EXPECT_CALL(stream, tell(root::relative_to::start)).Times(1).WillOnce(Return(0));
    EXPECT_EQ(writer.tell(), 0);

    // Now error
    EXPECT_CALL(stream, tell(root::relative_to::start)).Times(1).WillOnce(Return(root::error::DEAD_OBJECT));
    EXPECT_EQ(writer.tell(), root::error::DEAD_OBJECT);
} 

TEST_F(writer_tests, seek) {
    EXPECT_CALL(stream, seek(50, root::relative_to::start)).Times(1).WillOnce(Return(root::error::NO_ERROR));
    EXPECT_EQ(writer.seek(50), root::error::NO_ERROR);
} 

TEST_F(writer_tests, write) {
    const size_t BUFFER_SIZE = 512;
    char buffer[BUFFER_SIZE];
    EXPECT_CALL(stream, write(buffer, BUFFER_SIZE)).Times(1).WillOnce(Return(root::error::NO_ERROR));
    EXPECT_EQ(writer.write(buffer, BUFFER_SIZE), root::error::NO_ERROR);
} 