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

class mock_allocator : public root::allocator {
public:
    MOCK_METHOD(void*, malloc, (const size_t&));
    MOCK_METHOD(void, free, (void*, const size_t&));
};

class managed_ptr_tests : public ::testing::Test {
public:
    template<typename C>
    class stub_ptr : public root::managed_ptr<C> {
    public:
        stub_ptr() : root::managed_ptr<C>(nullptr, nullptr, root::allocator::default_allocator()) {}
        stub_ptr(C* memory, root::reference_counter* counter, root::allocator& alloc) 
        :   root::managed_ptr<C>(memory, counter, alloc) {}   

        auto operator=(const stub_ptr<C>& other) -> stub_ptr<C>& {
            this->m_memory = other.m_memory;
            this->m_ref_count = other.m_ref_count;
            this->m_allocator = other.m_allocator;
            return *this;
        }
    };

    void SetUp() override {
        counter = new root::reference_counter;
        data = new int;
        ptr = stub_ptr<int>(data, counter, allocator);
    }

    void TearDown() override {
        delete counter;
        delete data;
    }

    root::reference_counter* counter;
    mock_allocator allocator;
    int* data;
    stub_ptr<int> ptr;
};

TEST_F(managed_ptr_tests, counter_does_not_change) {
    
}