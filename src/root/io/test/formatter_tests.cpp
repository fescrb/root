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

#include <root/io/formatter.h>
#include <root/memory/test/mock_allocator.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <limits>
#include <iostream> // TODO remove

class formatter_tests : public ::testing::Test {
public:
    formatter_tests() 
    :   formatter(&allocator) {}

    void SetUp() override {
        memory = malloc(MEMORY_SIZE);
    }

    void TearDown() override {
        free(memory);
    }

    static constexpr size_t MEMORY_SIZE = 512;
    root::mock_allocator allocator;
    root::formatter formatter;
    void* memory;
};

using ::testing::Return;

template<typename T, const char* root_fmt_string, const char* c_fmt_string>
auto int_format_test() -> void {
}

TEST_F(formatter_tests, format) {
    constexpr size_t NUM_TESTS = 10;
    constexpr size_t MAX_STR_SIZE = 512;

#define INT_FORMAT_TEST(_T_, _root_fmt_string_, _c_fmt_string_) \
    _T_ test = (rand() % std::numeric_limits<_T_>::max()) - (std::numeric_limits<_T_>::max()/2); \
    char str_lit[MAX_STR_SIZE]; \
    sprintf(str_lit, _c_fmt_string_, test); \
    EXPECT_CALL(allocator, malloc(strlen(str_lit)+1, alignof(root::i8))).Times(1).WillOnce(Return(memory));\
    root::string str = formatter.format(_root_fmt_string_, test);\
    EXPECT_EQ(memcmp(str, str_lit, strlen(str_lit)), 0);\
    EXPECT_CALL(allocator, free(memory)).Times(1);

    for(int i = 0; i < NUM_TESTS; i++) {
        INT_FORMAT_TEST(root::i8, "Formatting {} test", "Formatting %c test");
    }

    for(int i = 0; i < NUM_TESTS; i++) {
        INT_FORMAT_TEST(root::i16, "Formatting {} test", "Formatting %d test");
    }
    
    for(int i = 0; i < NUM_TESTS; i++) {
        INT_FORMAT_TEST(root::i32, "Formatting {} test", "Formatting %d test");
    }

    for(int i = 0; i < NUM_TESTS; i++) {
        INT_FORMAT_TEST(root::i64, "Formatting {} test", "Formatting %lld test");
    }

        for(int i = 0; i < NUM_TESTS; i++) {
        INT_FORMAT_TEST(root::u8, "Formatting {} test", "Formatting %d test");
    }

    for(int i = 0; i < NUM_TESTS; i++) {
        INT_FORMAT_TEST(root::u16, "Formatting {} test", "Formatting %d test");
    }
    
    for(int i = 0; i < NUM_TESTS; i++) {
        INT_FORMAT_TEST(root::u32, "Formatting {} test", "Formatting %u test");
    }

    for(int i = 0; i < NUM_TESTS; i++) {
        INT_FORMAT_TEST(root::u64, "Formatting {} test", "Formatting %llu test");
    }
}

TEST_F(formatter_tests, bool_to_string) {
    const char* TRUE_BOOLEAN = "true";
    const char* FALSE_BOOLEAN = "false";
    {
        EXPECT_CALL(allocator, malloc(strlen(TRUE_BOOLEAN)+1, alignof(root::i8))).Times(1).WillOnce(Return(memory));
        root::string str = formatter.to_string(true);
        EXPECT_EQ(memcmp(str, TRUE_BOOLEAN, strlen(TRUE_BOOLEAN)), 0);
        EXPECT_CALL(allocator, free(memory)).Times(1);
    }

    {
        EXPECT_CALL(allocator, malloc(strlen(FALSE_BOOLEAN)+1, alignof(root::i8))).Times(1).WillOnce(Return(memory));
        root::string str = formatter.to_string(false);
        EXPECT_EQ(memcmp(str, FALSE_BOOLEAN, strlen(FALSE_BOOLEAN)), 0);
        EXPECT_CALL(allocator, free(memory)).Times(1);
    }

    {
        EXPECT_EQ(root::strlen("{}", true), strlen(TRUE_BOOLEAN));
        EXPECT_EQ(root::strlen("{}", false), strlen(FALSE_BOOLEAN));
        EXPECT_EQ(root::strlen("This is {}", true), strlen("This is ") + strlen(TRUE_BOOLEAN));
        EXPECT_EQ(root::strlen("{} it was", false), strlen(" it was") + strlen(FALSE_BOOLEAN));
    }
}

TEST_F(formatter_tests, i8_to_string) {
    constexpr size_t NUM_TESTS = 10;
    constexpr size_t MAX_STR_SIZE = 512;
    constexpr root::i8 MAX = std::numeric_limits<root::i8>::max();
    for (int _ = 0; _ < NUM_TESTS; _++) {
        root::i8 test = (rand() % MAX) - (MAX / 2);
        char str_lit[MAX_STR_SIZE];
        sprintf(str_lit, "%c", test);
        EXPECT_CALL(allocator, malloc(strlen(str_lit)+1, alignof(root::i8))).Times(1).WillOnce(Return(memory));
        root::string str = formatter.to_string(test);
        EXPECT_EQ(memcmp(str, str_lit, strlen(str_lit)), 0);
        EXPECT_CALL(allocator, free(memory)).Times(1);
    }
}

TEST_F(formatter_tests, u8_to_string) {
    constexpr size_t NUM_TESTS = 10;
    constexpr size_t MAX_STR_SIZE = 512;
    constexpr root::u8 MAX = std::numeric_limits<root::u8>::max();
    for (int _ = 0; _ < NUM_TESTS; _++) {
        root::u8 test = rand() % MAX;
        char str_lit[MAX_STR_SIZE];
        sprintf(str_lit, "%d", test);
        EXPECT_CALL(allocator, malloc(strlen(str_lit)+1, alignof(root::i8))).Times(1).WillOnce(Return(memory));
        root::string str = formatter.to_string(test);
        EXPECT_EQ(memcmp(str, str_lit, strlen(str_lit)), 0);
        EXPECT_CALL(allocator, free(memory)).Times(1);
    }
}

TEST_F(formatter_tests, i16_to_string) {
    constexpr size_t NUM_TESTS = 10;
    constexpr size_t MAX_STR_SIZE = 512;
    constexpr root::i16 MAX = std::numeric_limits<root::i16>::max();
    for (int _ = 0; _ < NUM_TESTS; _++) {
        root::i16 test = (rand() % MAX) - (MAX / 2);
        char str_lit[MAX_STR_SIZE];
        sprintf(str_lit, "%d", test);
        EXPECT_CALL(allocator, malloc(strlen(str_lit)+1, alignof(root::i8))).Times(1).WillOnce(Return(memory));
        root::string str = formatter.to_string(test);
        EXPECT_EQ(memcmp(str, str_lit, strlen(str_lit)), 0);
        EXPECT_CALL(allocator, free(memory)).Times(1);
    }
}

TEST_F(formatter_tests, u16_to_string) {
    constexpr size_t NUM_TESTS = 10;
    constexpr size_t MAX_STR_SIZE = 512;
    constexpr root::u16 MAX = std::numeric_limits<root::u16>::max();
    for (int _ = 0; _ < NUM_TESTS; _++) {
        root::u16 test = rand() % MAX;
        char str_lit[MAX_STR_SIZE];
        sprintf(str_lit, "%d", test);
        EXPECT_CALL(allocator, malloc(strlen(str_lit)+1, alignof(root::i8))).Times(1).WillOnce(Return(memory));
        root::string str = formatter.to_string(test);
        EXPECT_EQ(memcmp(str, str_lit, strlen(str_lit)), 0);
        EXPECT_CALL(allocator, free(memory)).Times(1);
    }
}

TEST_F(formatter_tests, u32_to_string) {
    constexpr size_t NUM_TESTS = 10;
    constexpr size_t MAX_STR_SIZE = 512;
    constexpr root::u32 MAX = std::numeric_limits<root::u32>::max();
    for (int _ = 0; _ < NUM_TESTS; _++) {
        root::u32 test = rand() % MAX;
        char str_lit[MAX_STR_SIZE];
        sprintf(str_lit, "%d", test);
        EXPECT_CALL(allocator, malloc(strlen(str_lit)+1, alignof(root::i8))).Times(1).WillOnce(Return(memory));
        root::string str = formatter.to_string(test);
        EXPECT_EQ(memcmp(str, str_lit, strlen(str_lit)), 0);
        EXPECT_CALL(allocator, free(memory)).Times(1);
    }
}

TEST_F(formatter_tests, u64_to_string) {
    constexpr size_t NUM_TESTS = 10;
    constexpr size_t MAX_STR_SIZE = 512;
    constexpr root::u64 MAX = std::numeric_limits<root::u64>::max();
    for (int _ = 0; _ < NUM_TESTS; _++) {
        root::u64 test = rand() % MAX;
        char str_lit[MAX_STR_SIZE];
        sprintf(str_lit, "%llu", test);
        EXPECT_CALL(allocator, malloc(strlen(str_lit)+1, alignof(root::i8))).Times(1).WillOnce(Return(memory));
        root::string str = formatter.to_string(test);
        EXPECT_EQ(memcmp(str, str_lit, strlen(str_lit)), 0);
        EXPECT_CALL(allocator, free(memory)).Times(1);
    }
}

TEST_F(formatter_tests, i32_to_string) {
    constexpr size_t NUM_TESTS = 10;
    constexpr size_t MAX_STR_SIZE = 512;
    constexpr root::i32 MAX = std::numeric_limits<root::i32>::max();
    for (int _ = 0; _ < NUM_TESTS; _++) {
        root::i32 test = (rand() % MAX) - (MAX / 2);
        char str_lit[MAX_STR_SIZE];
        sprintf(str_lit, "%d", test);
        EXPECT_CALL(allocator, malloc(strlen(str_lit)+1, alignof(root::i8))).Times(1).WillOnce(Return(memory));
        root::string str = formatter.to_string(test);
        EXPECT_EQ(memcmp(str, str_lit, strlen(str_lit)), 0);
        EXPECT_CALL(allocator, free(memory)).Times(1);
    }
}

TEST_F(formatter_tests, i64_to_string) {
    constexpr size_t NUM_TESTS = 10;
    constexpr size_t MAX_STR_SIZE = 512;
    constexpr root::i64 MAX = std::numeric_limits<root::i64>::max();
    for (int _ = 0; _ < NUM_TESTS; _++) {
        root::i64 test = (rand() % MAX) - (MAX / 2);
        char str_lit[MAX_STR_SIZE];
        sprintf(str_lit, "%lld", test);
        EXPECT_CALL(allocator, malloc(strlen(str_lit)+1, alignof(root::i8))).Times(1).WillOnce(Return(memory));
        root::string str = formatter.to_string(test);
        EXPECT_EQ(memcmp(str, str_lit, strlen(str_lit)), 0);
        EXPECT_CALL(allocator, free(memory)).Times(1);
    }
}

TEST_F(formatter_tests, f32_to_string) {
    constexpr size_t NUM_TESTS = 100;
    constexpr size_t MAX_STR_SIZE = 512;
    for (int _ = 0; _ < NUM_TESTS; _++) {
        constexpr root::f32 SCALE = std::numeric_limits<root::f32>::max();
        root::f32 test = ((static_cast<root::f32>(rand()) /static_cast<root::f32>(RAND_MAX))
                          * SCALE) - (SCALE / 2);
        char str_lit[MAX_STR_SIZE];
        sprintf(str_lit, "%1.5e", test);
        EXPECT_CALL(allocator, malloc(strlen(str_lit)+1, alignof(root::i8))).Times(1).WillOnce(Return(memory));
        root::string str = formatter.to_string(test);
        EXPECT_EQ(memcmp(str, str_lit, strlen(str_lit)), 0);
        EXPECT_CALL(allocator, free(memory)).Times(1);
    }

    for (int _ = 0; _ < NUM_TESTS; _++) {
        constexpr root::f32 SCALE = 1e15f;
        root::f32 test = ((static_cast<root::f32>(rand()) /static_cast<root::f32>(RAND_MAX))
                          * SCALE) - (SCALE / 2);
        char str_lit[MAX_STR_SIZE];
        sprintf(str_lit, "%1.5e", test);
        EXPECT_CALL(allocator, malloc(strlen(str_lit)+1, alignof(root::i8))).Times(1).WillOnce(Return(memory));
        root::string str = formatter.to_string(test);
        EXPECT_EQ(memcmp(str, str_lit, strlen(str_lit)), 0);
        EXPECT_CALL(allocator, free(memory)).Times(1);
    }

    /*for (int _ = 0; _ < NUM_TESTS; _++) {
        constexpr root::f32 SCALE = 10.0f;
        root::f32 test = ((static_cast<root::f32>(rand()) /static_cast<root::f32>(RAND_MAX))
                          * SCALE) - (SCALE / 2);
        char str_lit[MAX_STR_SIZE];
        sprintf(str_lit, "%2.4f", test);
        EXPECT_CALL(allocator, malloc(strlen(str_lit)+1, alignof(root::i8))).Times(1).WillOnce(Return(memory));
        root::string str = formatter.to_string(test);
        EXPECT_EQ(memcmp(str, str_lit, strlen(str_lit)), 0);
        EXPECT_CALL(allocator, free(memory)).Times(1);
    }*/

    for (int _ = 0; _ < NUM_TESTS; _++) {
        constexpr root::f32 SCALE = 2.0f;
        root::f32 test = ((static_cast<root::f32>(rand()) /static_cast<root::f32>(RAND_MAX))
                          * SCALE) - (SCALE / 2);
        char str_lit[MAX_STR_SIZE];
        sprintf(str_lit, "%1.5f", test);
        EXPECT_CALL(allocator, malloc(strlen(str_lit)+1, alignof(root::i8))).Times(1).WillOnce(Return(memory));
        root::string str = formatter.to_string(test);
        EXPECT_EQ(memcmp(str, str_lit, strlen(str_lit)), 0);
        EXPECT_CALL(allocator, free(memory)).Times(1);
    }
}