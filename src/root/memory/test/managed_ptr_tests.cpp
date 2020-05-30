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

#include <root/memory/private/managed_ptr.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "mock_allocator.h"

class managed_ptr_tests : public ::testing::Test {
public:
    void SetUp() override {
        counter = new root::reference_counter;
        data = new int;
        ptr = new root::managed_ptr<int>(data, counter, &allocator);
    }

    void TearDown() override {
        delete ptr;
        delete counter;
        delete data;
    }

    root::reference_counter* counter;
    mock_allocator allocator;
    int* data;
    root::managed_ptr<int> *ptr;
};

TEST_F(managed_ptr_tests, counter_does_not_change) {
    EXPECT_EQ(counter->strong_refs(), 1);
    EXPECT_EQ(counter->weak_refs(), 0);
}