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

#include <root/io/path.h>

#include <gtest/gtest.h>

#include <root/memory/test/mock_allocator.h>

#if !defined(ROOT_TESTS_BINARY_PATH)
#pragma message( "ROOT_TESTS_BINARY_PATH not defined. Cannot test binary_location()." )
#define ROOT_TESTS_BINARY_PATH ""
#endif

#if !defined(ROOT_TESTS_BINARY_NAME)
#pragma message( "ROOT_TESTS_BINARY_NAME not defined. Cannot test binary_name()." )
#define ROOT_TESTS_BINARY_NAME ""
#endif

#include <iostream>

using ::testing::Return;

TEST(path_tests, basename) {
    constexpr root::string_view ROOT = "/";
    constexpr root::string_view ONLY_FILE = "file";
    constexpr root::string_view ROOT_FILE_LOCATION = "/file";
    constexpr root::string_view FOLDER_LOCATION = "/home/";
    constexpr root::string_view FILE_LOCATION = "/home/file";

    constexpr root::string_view BASENAME_FOLDER_LOCATION = "home";

    EXPECT_EQ(ROOT, root::path::basename(ROOT));
    EXPECT_EQ(BASENAME_FOLDER_LOCATION, root::path::basename(FOLDER_LOCATION));
    EXPECT_EQ(ONLY_FILE, root::path::basename(FILE_LOCATION));
    EXPECT_EQ(ONLY_FILE, root::path::basename(ONLY_FILE));
    EXPECT_EQ(ONLY_FILE, root::path::basename(ROOT_FILE_LOCATION));
}

TEST(path_tests, dirname) {
    constexpr root::string_view ROOT = "/";
    constexpr root::string_view REDUCE_TO_ROOT = "/home";
    constexpr root::string_view FOLDER_LOCATION = "/home/user/";
    constexpr root::string_view FILE_LOCATION = "/home/user/file";

    constexpr root::string_view DIRNAME_FOLDER_LOCATION = "/home";
    constexpr root::string_view DIRNAME_FILE_LOCATION = "/home/user";

    EXPECT_EQ(ROOT, root::path::dirname(ROOT));
    EXPECT_EQ(ROOT, root::path::dirname(REDUCE_TO_ROOT));
    EXPECT_EQ(DIRNAME_FOLDER_LOCATION, root::path::dirname(FOLDER_LOCATION));
    EXPECT_EQ(DIRNAME_FILE_LOCATION, root::path::dirname(FILE_LOCATION));
}

TEST(path_tests, ext) {
    constexpr root::string_view ROOT = "/";
    constexpr root::string_view FOLDER_LOCATION = "/home/user/";
    constexpr root::string_view FOLDER_AS_FOLDER_LOCATION = "/home/user/file.vert/";
    constexpr root::string_view FILE_LOCATION = "/home/user/file.vert";
    constexpr root::string_view JUST_FILE = "file.frag";
    constexpr root::string_view FILE_NO_EXT_LOCATION = "/home/user/file";

    constexpr root::string_view EXT_EMPTY = "";
    constexpr root::string_view VERT_EXT = "vert";
    constexpr root::string_view FRAG_EXT = "frag";

    EXPECT_EQ(EXT_EMPTY, root::path::ext(ROOT));
    EXPECT_EQ(EXT_EMPTY, root::path::ext(FOLDER_LOCATION));
    EXPECT_EQ(EXT_EMPTY, root::path::ext(FOLDER_AS_FOLDER_LOCATION));
    EXPECT_EQ(VERT_EXT, root::path::ext(FILE_LOCATION));
    EXPECT_EQ(FRAG_EXT, root::path::ext(JUST_FILE));
    EXPECT_EQ(EXT_EMPTY, root::path::ext(FILE_NO_EXT_LOCATION));
}

TEST(path_tests, binary_location) {
    constexpr root::string_view BINARY_LOCATION = ROOT_TESTS_BINARY_PATH;

    if(BINARY_LOCATION.size()) {
        EXPECT_EQ(BINARY_LOCATION, root::path::binary_location());
    } 
}


TEST(path_tests, binary_name) {
    constexpr root::string_view BINARY_NAME = ROOT_TESTS_BINARY_NAME;

    if(BINARY_NAME.size()) {
        EXPECT_EQ(BINARY_NAME, root::path::binary_name());
    } 
}


TEST(path_tests, join) {
    constexpr const char* FOLDER_LOCATION = "/home/user";
    constexpr const char* FILE = "file.frag";
    constexpr const char* FULL_PATH = "/home/user/file.frag";

    root::mock_allocator mock_allocator;
    char memory[PATH_MAX];

    EXPECT_CALL(mock_allocator, malloc(strlen(FOLDER_LOCATION) + sizeof(root::path::FOLDER_DELIMITER) + strlen(FILE) +1, alignof(char))).WillOnce(Return(memory));

    root::string full_path = root::path::join(FOLDER_LOCATION, FILE, &mock_allocator);
    EXPECT_EQ(strcmp(full_path.data(), FULL_PATH), 0);
    
    EXPECT_CALL(mock_allocator, free(memory));
}