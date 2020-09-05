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

#include <root/io/format.h>
#include <root/core/assert.h>

#include <cmath>

namespace root {

template<> auto to_string<bool>(const bool& boolean) -> const char* {
    return boolean? "true" : "false";
}

template<typename T> auto integer_strlen(T i) -> u64 {
    int len = 0;
    if (i < 0) {
        len++;
        i = -i;
    }
    while(i > 9) {
        len++;
        i /= 10;
    }
    return ++len;
} 

// TODO: Look for a method to do with with concepts?
template<> auto strlen<i8>(const i8& object) -> u64 {
    return 1;
}

template<> auto strlen<i16>(const i16& object) -> u64 {
    return integer_strlen(object);
}

template<> auto strlen<i32>(const i32& object) -> u64 {
    return integer_strlen(object);
}

template<> auto strlen<i64>(const i64& object) -> u64 {
    return integer_strlen(object);
}

template<> auto strlen<u8>(const u8& object) -> u64 {
    return integer_strlen(object);
}

template<> auto strlen<u16>(const u16& object) -> u64 {
    return integer_strlen(object);
}

template<> auto strlen<u32>(const u32& object) -> u64 {
    return integer_strlen(object);
}

template<> auto strlen<u64>(const u64& object) -> u64 {
    return integer_strlen(object);
}

template<typename T> auto integer_to_string(char* str, T i, const u64& len) -> char* {
    int index = len - 1;
    if (i < 0) {
        str[0] = '-';
        i = -i;
    }
    while(i > 9) {
        str[index] = (i % 10) - '0';
        i /= 10;
        index--;
    }
    str[index] = i;
    return str + len;
} 

template<> auto to_string<i8>(char* str, const i8& i, const u64& len) -> char* {
    str[0] = i;
    return str + 1;
}

template<> auto to_string<i16>(char* str, const i16& i, const u64& len) -> char* {
    return integer_to_string(str, i, len);
}

template<> auto to_string<i32>(char* str, const i32& i, const u64& len) -> char* {
    return integer_to_string(str, i, len);
}

template<> auto to_string<i64>(char* str, const i64& i, const u64& len) -> void {
    integer_to_string(str, i, len);
}

template<> auto to_string<u8>(char* str, const u8& i, const u64& len) -> void {
    integer_to_string(str, i, len);
}

template<> auto to_string<u16>(char* str, const u16& i, const u64& len) -> void {
    integer_to_string(str, i, len);
}

template<> auto to_string<u32>(char* str, const u32& i, const u64& len) -> void {
    integer_to_string(str, i, len);
}

template<> auto to_string<u64>(char* str, const u64& i, const u64& len) -> void {
    integer_to_string(str, i, len);
}

template<typename T> auto float_str_len(const T& f) -> u64 {
    T temp;
    u64 fractpart = static_cast<u64>(modf(abs(f), &temp));
    u64 intpart = static_cast<u64>(temp);
    u64 sign_len = f < 0.0 ? 1 : 0;
    return sign_len + strlen(intpart) + 1 /*sign_point*/ + strlen(fractpart); 
}

template<> auto strlen<f32>(const f32& object) -> u64 {
    return float_str_len(object);
}

template<> auto strlen<f64>(const f64& object) -> u64 {
    return float_str_len(object);
}

template<typename T> auto float_to_string(char* str, const u64& i, const u64& len) -> char* {
    T temp;
    u64 fractpart = static_cast<u64>(modf(abs(f), &temp));
    u64 intpart = static_cast<u64>(temp);
    if (f < 0.0) {
        str[0] = '-'; str++;
    }
    str = to_string(str, intpart, strlen(intpart));
    str[0] = '.'; str++;
    return to_string(str, fractpart, strlen(intpart));
}

template<> auto to_string<u32>(char* str, const u32& i, const u64& len) -> char* {
    return float_to_string(str, i, len);
}

template<> auto to_string<u64>(char* str, const u64& i, const u64& len) -> char* {
    return float_to_string(str, i, len);
}

} // namespace root