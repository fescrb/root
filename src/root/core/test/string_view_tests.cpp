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

#define STRING_VIEW_TEST(_str_view_, _string_lit_) \
    EXPECT_EQ(strlen(_string_lit_), _str_view_.size()); \
    EXPECT_EQ(memcmp(_string_lit_, _str_view_.data(), _str_view_.size()), 0);

    constexpr root::string_view lit = "Test string please ignore.";
    constexpr auto p_location = root::find(lit.begin(), lit.end(), 'p');
    constexpr root::string_view smaller = root::string_view(lit.begin(), p_location);
    constexpr root::string_view after = root::string_view(p_location, lit.end());

    STRING_VIEW_TEST(smaller, "Test string ");
    STRING_VIEW_TEST(after, "please ignore.");

    constexpr root::string_view lit2 = "This is a {formatting} test";
    auto placeholder_start = find(lit2.begin(), lit2.end(), '{');
    auto placeholder_end = find(placeholder_start, lit2.end(), '}');


    root::string_view pre_placeholder = root::string_view(lit2.begin(), placeholder_start);
    root::string_view format = root::string_view(++placeholder_start, placeholder_end);
    root::string_view post_placeholder = root::string_view(++placeholder_end, lit2.end());

    STRING_VIEW_TEST(pre_placeholder, "This is a ");
    STRING_VIEW_TEST(format, "formatting");
    STRING_VIEW_TEST(post_placeholder, " test");
}

TEST(string_view_tests, reverse_iterator_init) {

#define STRING_VIEW_TEST(_str_view_, _string_lit_) \
    EXPECT_EQ(strlen(_string_lit_), _str_view_.size()); \
    EXPECT_EQ(memcmp(_string_lit_, _str_view_.data(), _str_view_.size()), 0);

    constexpr root::string_view lit = "Test string please ignore.";
    constexpr auto p_location = root::find(lit.rbegin(), lit.rend(), 'p');
    constexpr root::string_view smaller = root::string_view(lit.rbegin(), p_location);
    constexpr root::string_view after = root::string_view(p_location, lit.rend());

    STRING_VIEW_TEST(smaller, "lease ignore.");
    STRING_VIEW_TEST(after, "Test string p");
}

TEST(string_view_tests, equality) {
    constexpr root::string_view str = "Test string please ignore.";
    constexpr root::string_view same = "Test string please ignore.";
    constexpr root::string_view extended = "Test string please ignore. Again.";
    constexpr root::string_view diff = "Test str1ng please ignore.";
    
    EXPECT_EQ(str, same);
    EXPECT_EQ(same, str);
    EXPECT_NE(str, extended);
    EXPECT_NE(extended, str);
    EXPECT_NE(str, diff);
    EXPECT_NE(diff, str);
}