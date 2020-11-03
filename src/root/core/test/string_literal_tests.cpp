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

#include <root/core/string_literal.h>

#include <gtest/gtest.h>

TEST(string_literal_tests, constexpr_strlen) {
    constexpr root::string_literal lit = "Test string please ignore.";
    constexpr root::u64 size = strlen(lit);

    EXPECT_EQ(size, strlen(lit.data()));
}

TEST(string_literal_tests, constexpr_find) {
    constexpr root::string_literal lit = "Test string please ignore.";
    constexpr root::u64 size = strlen(lit);

    EXPECT_EQ(size, strlen(lit.data()));
}