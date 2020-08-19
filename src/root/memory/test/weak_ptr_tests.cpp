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
#include <root/memory/weak_ptr.h>

#include <thread>

using ::testing::NiceMock;
using ::testing::Test;
using ::testing::Return;

class weak_ptr_tests : public Test {
public:
    class Class {
    public:
        Class(int data) : m_data(data) {}
        int m_data;
    };

    void SetUp() override {
        counter = new root::reference_counter;
        memory = new Class(0);
        ON_CALL(allocator, malloc(sizeof(Class), alignof(Class))).WillByDefault(Return(memory));
        ON_CALL(allocator, malloc(sizeof(root::reference_counter), alignof(Class))).WillByDefault(Return(counter));
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
    NiceMock<root::mock_allocator> allocator;
};

TEST_F(weak_ptr_tests, creation) {
    EXPECT_EQ(counter->strong_refs(), 1);
    EXPECT_EQ(counter->weak_refs(), 0);
    root::weak_ptr<Class> weak(strong);
    EXPECT_EQ(counter->strong_refs(), 1);
    EXPECT_EQ(counter->weak_refs(), 1);
    root::weak_ptr<Class> other_weak = root::weak_ptr<Class>(strong);
    EXPECT_EQ(counter->strong_refs(), 1);
    EXPECT_EQ(counter->weak_refs(), 2);
    root::weak_ptr<Class> copy_weak = weak;
    EXPECT_EQ(counter->strong_refs(), 1);
    EXPECT_EQ(counter->weak_refs(), 3);
}


TEST_F(weak_ptr_tests, destroy_strong_first) {
    EXPECT_EQ(counter->strong_refs(), 1);
    EXPECT_EQ(counter->weak_refs(), 0);
    root::weak_ptr<Class> weak(strong);
    EXPECT_EQ(counter->strong_refs(), 1);
    EXPECT_EQ(counter->weak_refs(), 1);
    EXPECT_CALL(allocator, free(memory, sizeof(Class), alignof(Class))).Times(1);
    strong = root::strong_ptr<Class>();
    EXPECT_EQ(counter->strong_refs(), 0);
    EXPECT_EQ(counter->weak_refs(), 1);
    EXPECT_CALL(allocator, free(counter, sizeof(root::reference_counter), alignof(Class))).Times(1);
    weak.clear();
    EXPECT_EQ(counter->strong_refs(), 0);
    EXPECT_EQ(counter->weak_refs(), 0);
}

TEST_F(weak_ptr_tests, acesss_after_promotion) {
    EXPECT_EQ(counter->strong_refs(), 1);
    EXPECT_EQ(counter->weak_refs(), 0);
    root::weak_ptr<Class> weak(strong);
    EXPECT_EQ(counter->strong_refs(), 1);
    EXPECT_EQ(counter->weak_refs(), 1);
    root::strong_ptr<Class> promoted = weak.promote();
    EXPECT_EQ(counter->strong_refs(), 2);
    EXPECT_EQ(counter->weak_refs(), 1);
    EXPECT_EQ(promoted->m_data, data);
    promoted->m_data = 2;
    EXPECT_EQ(promoted->m_data, 2);
}

TEST_F(weak_ptr_tests, multithread_release) {
    EXPECT_EQ(counter->strong_refs(), 1);
    EXPECT_EQ(counter->weak_refs(), 0);
    constexpr int NUM_THREADS = 100;
    std::thread threads[NUM_THREADS];
    root::weak_ptr<Class> weaks[NUM_THREADS];

    for(int i = 0; i < NUM_THREADS; i++) {
        threads[i] = std::thread([&weaks, i, this](){
            weaks[i] = root::weak_ptr<Class>(this->strong);
        });
    }

    for(int i = 0; i < NUM_THREADS; i++) {
        threads[i].join();
    }

    EXPECT_EQ(counter->strong_refs(), 1);
    EXPECT_EQ(counter->weak_refs(), NUM_THREADS);

    EXPECT_CALL(allocator, free(memory, sizeof(Class), alignof(Class))).Times(1);

    strong.clear();

    EXPECT_EQ(counter->strong_refs(), 0);
    EXPECT_EQ(counter->weak_refs(), NUM_THREADS);


    EXPECT_CALL(allocator, free(counter, sizeof(root::reference_counter), alignof(Class))).Times(1);

    for(int i = 0; i < NUM_THREADS; i++) {
        threads[i] = std::thread([&weaks, i](){
            weaks[i] = root::weak_ptr<Class>();
        });
    }

    for(int i = 0; i < NUM_THREADS; i++) {
        threads[i].join();
    }

    EXPECT_EQ(counter->strong_refs(), 0);
    EXPECT_EQ(counter->weak_refs(), 0);
}

TEST_F(weak_ptr_tests, multithread_interleaved_release) {
    EXPECT_EQ(counter->strong_refs(), 1);
    EXPECT_EQ(counter->weak_refs(), 0);
    constexpr int NUM_THREADS = 100;
    std::thread threads[NUM_THREADS];
    root::strong_ptr<Class> strongs[NUM_THREADS/2];
    root::weak_ptr<Class> weaks[NUM_THREADS/2];

    for(int i = 0; i < NUM_THREADS; i++) {
        threads[i] = std::thread([&weaks, &strongs, i, this](){
            if (i%2) {
                strongs[i/2] = this->strong;
            } else {
                weaks[i/2] = root::weak_ptr<Class>(this->strong);
            }
        });
    }

    for(int i = 0; i < NUM_THREADS; i++) {
        threads[i].join();
    }

    EXPECT_EQ(counter->strong_refs(), 1 + (NUM_THREADS/2));
    EXPECT_EQ(counter->weak_refs(), NUM_THREADS/2);

    strong.clear();

    EXPECT_EQ(counter->strong_refs(), NUM_THREADS/2);
    EXPECT_EQ(counter->weak_refs(), NUM_THREADS/2);

    EXPECT_CALL(allocator, free(memory, sizeof(Class), alignof(Class))).Times(1);
    EXPECT_CALL(allocator, free(counter, sizeof(root::reference_counter), alignof(Class))).Times(1);

    for(int i = 0; i < NUM_THREADS; i++) {
        threads[i] = std::thread([&weaks, &strongs, i](){
            if(i%2) {
                strongs[i/2].clear();
            } else {
                weaks[i/2].clear();
            }
        });
    }

    for(int i = 0; i < NUM_THREADS; i++) {
        threads[i].join();
    }

    EXPECT_EQ(counter->strong_refs(), 0);
    EXPECT_EQ(counter->weak_refs(), 0);
}