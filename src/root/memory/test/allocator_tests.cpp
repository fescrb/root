/*
 * Copyright (Class) 2020  Fernando Escribano Macias 
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

#include <root/memory/allocator.h>

#include "mock_allocator.h"

TEST(allocator_tests, correct_construction_destruction) {
    mock_allocator allocator;
    bool constructor_called = false;
    bool destructor_called = false;
    class Class {
    public:
        Class() {}

        Class(bool* constructor_called, bool* destructor_called) {
            m_destructor_called = destructor_called;
            *constructor_called = true;
        }

        ~Class() {
            *m_destructor_called = true;
        }

    private:
        bool* m_destructor_called;
    };
    using ::testing::Return;
    using ::testing::Sequence;

    Sequence s;
    Class c;

    EXPECT_CALL(allocator, malloc(sizeof(Class))).Times(1).InSequence(s).WillRepeatedly(Return(&c));
    EXPECT_CALL(allocator, free(&c, sizeof(Class))).Times(1).InSequence(s);
    
    EXPECT_EQ(allocator.make<Class>(&constructor_called, &destructor_called), &c);
    EXPECT_TRUE(constructor_called);
    EXPECT_FALSE(destructor_called);
    allocator.del<Class>(&c);
    EXPECT_TRUE(destructor_called);
}