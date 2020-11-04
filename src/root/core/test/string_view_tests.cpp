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

#include <root/core/string_view.h>

#include <gtest/gtest.h>

TEST(string_view_tests, constexpr_strlen) {
    constexpr root::string_view lit = "Test string please ignore.#";
    constexpr root::u64 size = root::strlen(lit);

    EXPECT_EQ(size, strlen(lit.data()));
}

TEST(string_view_tests, constexpr_find) {
    constexpr root::string_view lit = "Test string please ignore.";
    constexpr root::string_view::iterator p_location = root::find(lit.begin(), lit.end(), 'p');
    constexpr root::i64 index = p_location - lit.begin();

    EXPECT_EQ(12, index);
}

TEST(string_view_tests, iterator_init) {
    constexpr root::string_view lit = "Test string please ignore.";
    constexpr root::string_view::iterator p_location = root::find(lit.begin(), lit.end(), 'p');
    constexpr root::string_view smaller = root::string_view(lit.begin(), p_location);

    EXPECT_EQ(strlen("Test string "), smaller.size());
    EXPECT_EQ(memcmp("Test string ", smaller.data(), smaller.size()), 0);
}