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
#include <root/memory/test/mock_allocator.h>
#include <root/memory/strong_ptr.h>

#include <thread>

class strong_ptr_tests : public ::testing::Test {
public:
    class Class {
    public:
        Class(int data) : m_data(data) {}
    
        int m_data;
    };

    void SetUp() override {
        counter = new root::reference_counter;
        memory = new Class(0);
    }

    void TearDown() override {
        delete memory;
        delete counter;
    }

    root::reference_counter* counter;
    Class* memory;
    root::mock_allocator allocator;
};

using ::testing::Return;
using ::testing::Sequence;

TEST_F(strong_ptr_tests, creation_and_destruction) {
    Sequence s_ref, s_class;
    EXPECT_CALL(allocator, malloc(sizeof(Class), alignof(Class))).Times(1).InSequence(s_class).WillOnce(Return(memory));
    EXPECT_CALL(allocator, malloc(sizeof(root::reference_counter), alignof(root::reference_counter))).Times(1).InSequence(s_ref).WillOnce(Return(counter));
    auto _ = allocator.make_strong<Class>(5);
    EXPECT_EQ(counter->strong_refs(), 1);
    EXPECT_EQ(counter->weak_refs(), 0);
    EXPECT_CALL(allocator, free(memory, sizeof(Class), alignof(Class))).Times(1).InSequence(s_class);
    EXPECT_CALL(allocator, free(counter, sizeof(root::reference_counter), alignof(root::reference_counter))).Times(1).InSequence(s_ref);
}

TEST_F(strong_ptr_tests, validity) {
    Sequence s_ref, s_class;
    EXPECT_CALL(allocator, malloc(sizeof(Class), alignof(Class))).Times(1).InSequence(s_class).WillOnce(Return(memory));
    EXPECT_CALL(allocator, malloc(sizeof(root::reference_counter), alignof(root::reference_counter))).Times(1).InSequence(s_ref).WillOnce(Return(counter));
    auto ptr = allocator.make_strong<Class>(5);
    EXPECT_EQ(counter->strong_refs(), 1);
    EXPECT_EQ(counter->weak_refs(), 0);
    EXPECT_TRUE(ptr);
    EXPECT_CALL(allocator, free(memory, sizeof(Class), alignof(Class))).Times(1).InSequence(s_class);
    EXPECT_CALL(allocator, free(counter, sizeof(root::reference_counter), alignof(root::reference_counter))).Times(1).InSequence(s_ref);
}

TEST_F(strong_ptr_tests, clear) {
    Sequence s_ref, s_class;
    EXPECT_CALL(allocator, malloc(sizeof(Class), alignof(Class))).Times(1).InSequence(s_class).WillOnce(Return(memory));
    EXPECT_CALL(allocator, malloc(sizeof(root::reference_counter), alignof(root::reference_counter))).Times(1).InSequence(s_ref).WillOnce(Return(counter));
    auto ptr = allocator.make_strong<Class>(5);
    EXPECT_EQ(counter->strong_refs(), 1);
    EXPECT_EQ(counter->weak_refs(), 0);
    EXPECT_CALL(allocator, free(memory, sizeof(Class), alignof(Class))).Times(1).InSequence(s_class);
    EXPECT_CALL(allocator, free(counter, sizeof(root::reference_counter), alignof(root::reference_counter))).Times(1).InSequence(s_ref);
    ptr.clear();
    EXPECT_EQ(counter->strong_refs(), 0);
    EXPECT_EQ(counter->weak_refs(), 0);
    EXPECT_FALSE(ptr);
}

TEST_F(strong_ptr_tests, single_sequential_copy) {
    Sequence s_ref, s_class;
    EXPECT_CALL(allocator, malloc(sizeof(Class), alignof(Class))).Times(1).InSequence(s_class).WillOnce(Return(memory));
    EXPECT_CALL(allocator, malloc(sizeof(root::reference_counter), alignof(root::reference_counter))).Times(1).InSequence(s_ref).WillOnce(Return(counter));
    auto original = allocator.make_strong<Class>(5);
    {
        auto copy = original;
        EXPECT_EQ(counter->strong_refs(), 2);
        EXPECT_EQ(counter->weak_refs(), 0);
    }
    EXPECT_EQ(counter->strong_refs(), 1);
    EXPECT_EQ(counter->weak_refs(), 0);
    auto second_copy = original;
    EXPECT_EQ(counter->strong_refs(), 2);
    EXPECT_EQ(counter->weak_refs(), 0);
    second_copy = root::strong_ptr<Class>();
    EXPECT_EQ(counter->strong_refs(), 1);
    EXPECT_EQ(counter->weak_refs(), 0);
    EXPECT_FALSE(second_copy);
    EXPECT_CALL(allocator, free(memory, sizeof(Class), alignof(Class))).Times(1).InSequence(s_class);
    EXPECT_CALL(allocator, free(counter, sizeof(root::reference_counter), alignof(root::reference_counter))).Times(1).InSequence(s_ref);
}

TEST_F(strong_ptr_tests, multiple_concurrent_copies){
    constexpr int NUM_THREADS = 100;
    Sequence s_ref, s_class;
    EXPECT_CALL(allocator, malloc(sizeof(Class), alignof(Class))).Times(1).InSequence(s_class).WillOnce(Return(memory));
    EXPECT_CALL(allocator, malloc(sizeof(root::reference_counter), alignof(root::reference_counter))).Times(1).InSequence(s_ref).WillOnce(Return(counter));
    auto original = allocator.make_strong<Class>(5);
    root::strong_ptr<Class> copies[NUM_THREADS];
    std::thread threads[NUM_THREADS];
    for(int i = 0; i < NUM_THREADS; i++) {
        threads[i] = std::thread([&copies, i, &original](){
            copies[i] = original;
        });
    }
    for(int i = 0; i < NUM_THREADS; i++) {
        threads[i].join();
    }
    EXPECT_EQ(counter->strong_refs(), NUM_THREADS+1);
    EXPECT_EQ(counter->weak_refs(), 0);
    original = root::strong_ptr<Class>();;
    EXPECT_EQ(counter->strong_refs(), NUM_THREADS);
    EXPECT_EQ(counter->weak_refs(), 0);
    EXPECT_CALL(allocator, free(memory, sizeof(Class), alignof(Class))).Times(1).InSequence(s_class);
    EXPECT_CALL(allocator, free(counter, sizeof(root::reference_counter), alignof(root::reference_counter))).Times(1).InSequence(s_ref);
    for(int i = 0; i < NUM_THREADS; i++) {
        threads[i] = std::thread([&copies, i](){
            copies[i] = root::strong_ptr<Class>();
        });
    }
    for(int i = 0; i < NUM_THREADS; i++) {
        threads[i].join();
    }
    EXPECT_EQ(counter->strong_refs(), 0);
    EXPECT_EQ(counter->weak_refs(), 0);
}

TEST_F(strong_ptr_tests, dereference) {
    Sequence s_ref, s_class;
    constexpr int INITIAL_VALUE = 5;
    constexpr int SECOND_VALUE = 42;
    constexpr int THIRD_VALUE = 7;
    constexpr int LAST_VALUE = 360;
    EXPECT_CALL(allocator, malloc(sizeof(Class), alignof(Class))).Times(1).InSequence(s_class).WillOnce(Return(memory));
    EXPECT_CALL(allocator, malloc(sizeof(root::reference_counter), alignof(root::reference_counter))).Times(1).InSequence(s_ref).WillOnce(Return(counter));
    auto ptr = allocator.make_strong<Class>(5);
    EXPECT_EQ(counter->strong_refs(), 1);
    EXPECT_EQ(counter->weak_refs(), 0);
    EXPECT_EQ(INITIAL_VALUE, ptr->m_data);
    EXPECT_EQ(INITIAL_VALUE, (*ptr).m_data);
    ptr->m_data = SECOND_VALUE;
    EXPECT_EQ(SECOND_VALUE, ptr->m_data);
    EXPECT_EQ(SECOND_VALUE, (*ptr).m_data);
    EXPECT_EQ(SECOND_VALUE, memory->m_data);
    (*ptr).m_data = THIRD_VALUE;
    EXPECT_EQ(THIRD_VALUE, ptr->m_data);
    EXPECT_EQ(THIRD_VALUE, (*ptr).m_data);
    EXPECT_EQ(THIRD_VALUE, memory->m_data);
    memory->m_data = LAST_VALUE;
    EXPECT_EQ(LAST_VALUE, ptr->m_data);
    EXPECT_EQ(LAST_VALUE, (*ptr).m_data);
    EXPECT_EQ(LAST_VALUE, memory->m_data);
    EXPECT_CALL(allocator, free(memory, sizeof(Class), alignof(Class))).Times(1).InSequence(s_class);
    EXPECT_CALL(allocator, free(counter, sizeof(root::reference_counter), alignof(root::reference_counter))).Times(1).InSequence(s_ref);
}