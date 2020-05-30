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

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <root/memory/private/reference_counter.h>
#include <root/memory/strong_ptr.h>
#include <root/memory/weak_ptr.h>

#include <thread>

#include "mock_allocator.h"

using ::testing::NiceMock;
using ::testing::Test;
using ::testing::Return;

class weak_ptr_tests : public Test {
public:
    class Class {
    public:
        Class(int data) : m_data(data) {}
    private:
        int m_data;
    };

    void SetUp() override {
        counter = new root::reference_counter;
        memory = new Class(0);
        ON_CALL(allocator, malloc(sizeof(Class))).WillByDefault(Return(memory));
        ON_CALL(allocator, malloc(sizeof(root::reference_counter))).WillByDefault(Return(counter));
        strong = root::strong_ptr<Class>::make(&allocator, data);
    }

    void TearDown() override {
        strong.clear();
        delete memory;
        delete counter;
    }

    int data = 5;
    root::reference_counter* counter;
    Class* memory;
    root::strong_ptr<Class> strong;
    NiceMock<mock_allocator> allocator;
};

TEST_F(weak_ptr_tests, creation) {
    EXPECT_EQ(counter->strong_refs(), 1);
    EXPECT_EQ(counter->weak_refs(), 0);
    root::weak_ptr<Class> weak(strong);
    EXPECT_EQ(counter->strong_refs(), 1);
    EXPECT_EQ(counter->weak_refs(), 1);
    //root::weak_ptr<Class> other_weak = root::weak_ptr<Class>(strong);
}


TEST_F(weak_ptr_tests, destroy_strong_first) {
    EXPECT_EQ(counter->strong_refs(), 1);
    EXPECT_EQ(counter->weak_refs(), 0);
    root::weak_ptr<Class> weak(strong);
    EXPECT_EQ(counter->strong_refs(), 1);
    EXPECT_EQ(counter->weak_refs(), 1);
    EXPECT_CALL(allocator, free(memory, sizeof(Class))).Times(1);
    strong = root::strong_ptr<Class>();
    EXPECT_EQ(counter->strong_refs(), 0);
    EXPECT_EQ(counter->weak_refs(), 1);
    EXPECT_CALL(allocator, free(counter, sizeof(root::reference_counter))).Times(1);
    weak.clear();
    EXPECT_EQ(counter->strong_refs(), 0);
    EXPECT_EQ(counter->weak_refs(), 0);
}