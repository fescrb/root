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

#if !defined(ROOT_TESTS_BINARY_PATH)
#pragma message( "ROOT_TESTS_BINARY_PATH not defined. Cannot test binary_location()." )
#define ROOT_TESTS_BINARY_PATH ""
#endif

#include <iostream>

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

TEST(path_tests, binary_location) {
    constexpr root::string_view BINARY_LOCATION = ROOT_TESTS_BINARY_PATH;

    if(BINARY_LOCATION.size()) {
        EXPECT_EQ(BINARY_LOCATION, root::path::binary_location());
    } 
}