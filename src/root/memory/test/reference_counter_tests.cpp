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

#include <root/memory/private/reference_counter.h>

#include <thread>

class reference_counter_tests : public ::testing::Test {
protected:
    virtual void SetUp() override {
        counter = new root::reference_counter();
    }
    
    virtual void TearDown() override {
        delete counter;
    }

    root::reference_counter *counter = nullptr;  
};

TEST_F(reference_counter_tests, correct_initialization) {
    EXPECT_EQ(counter->strong_refs(), 1);
    EXPECT_EQ(counter->weak_refs(), 0);
}

TEST_F(reference_counter_tests, abandoning) {
    EXPECT_TRUE(counter->decrement_strong());
    EXPECT_TRUE(counter->abandoned());
}

TEST_F(reference_counter_tests, no_increments_after_abandonement) {
    EXPECT_TRUE(counter->decrement_strong());
    EXPECT_FALSE(counter->try_increment_strong());
    EXPECT_FALSE(counter->try_increment_weak());
}

TEST_F(reference_counter_tests, no_lost_changes) {
    constexpr int NUM_THREADS = 100;
    std::thread threads[NUM_THREADS];
    counter->try_increment_weak(); // So that we can check all decrement weak calls to be false
    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i] = std::thread([i, this](){
            if(i % 2) {
                EXPECT_TRUE(counter->try_increment_strong());
                EXPECT_FALSE(counter->decrement_strong());
            } else {
                EXPECT_TRUE(counter->try_increment_weak());
                EXPECT_FALSE(counter->decrement_weak());
            }
        });
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i].join();
    }
    EXPECT_EQ(counter->strong_refs(), 1);
    EXPECT_EQ(counter->weak_refs(), 1);
}