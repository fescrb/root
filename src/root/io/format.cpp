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
#include <root/math/math.h>

#include <cmath>

namespace root {

formatter* format::m_default_formatter = new formatter();

template<>
auto format_to<string_view>(buffer_writer& dst, const string_view& object, const string_view& format_args) -> void {
    dst.write(object.data(), object.size());
}

auto format_to(const bool& boolean) -> const char* {
    return boolean ? "true" : "false";
}

template<> auto strlen<bool>(const bool& object, const string_view& format_args) -> u64 {
    return strlen(format_to(object));
}

template<> auto format_to<bool>(buffer_writer& dst, const bool& object, const string_view& format_args) -> void {
    format_to(dst, format_to(object));
}

template<typename T> auto integer_strlen(T i) -> u64 {
    if(i == 0) return 1;
    u64 digits = static_cast<u64>(ceil(log10(fabs(static_cast<f64>(i)))));
    // If i is an exact power of 10 we will need one more character
    return (i < 0 ? 1 : 0) + digits + (i % static_cast<T>(pow(10, digits)) ? 0 : 1);
} 

// TODO: Look for a method to do with with concepts?
template<> auto strlen<i8>(const i8& object, const string_view& format_args) -> u64 {
    return 1;
}

template<> auto strlen<i16>(const i16& object, const string_view& format_args) -> u64 {
    return integer_strlen(object);
}

template<> auto strlen<i32>(const i32& object, const string_view& format_args) -> u64 {
    return integer_strlen(object);
}

template<> auto strlen<i64>(const i64& object, const string_view& format_args) -> u64 {
    return integer_strlen(object);
}

template<> auto strlen<u8>(const u8& object, const string_view& format_args) -> u64 {
    return integer_strlen(object);
}

template<> auto strlen<u16>(const u16& object, const string_view& format_args) -> u64 {
    return integer_strlen(object);
}

template<> auto strlen<u32>(const u32& object, const string_view& format_args) -> u64 {
    return integer_strlen(object);
}

template<> auto strlen<u64>(const u64& object, const string_view& format_args) -> u64 {
    return integer_strlen(object);
}

template<typename T> auto unsigned_int_format_to(buffer_writer& dst, const T& i, const u64& min_digits = 0) -> void {
    T digits = i == 0 ? 0 : floor(log10(static_cast<f64>(i)));
    T scale = static_cast<T>(pow(10, digits));
    while(min_digits > (digits+1)) {
        format_to(dst, '0');
        digits++;
    }
    while(scale >= 10) {
        format_to(dst, static_cast<i8>(((i / scale) % 10) + '0'));
        scale/=10;
    }
    format_to(dst, static_cast<i8>((i  % 10) + '0'));
} 

template<typename T> auto integer_format_to(buffer_writer& dst, const T& i) -> void {
    // This needs a cleanup
    T abs_i = i;
    if (i < 0) {
        format_to(dst, '-');
        abs_i = -i;
    }
    unsigned_int_format_to(dst, abs_i);
} 

template<> auto format_to<i8>(buffer_writer& dst, const i8& i, const string_view& format_args) -> void {
    dst.write(&i, 1);
}

template<> auto format_to<i16>(buffer_writer& dst, const i16& i, const string_view& format_args) -> void {
    integer_format_to(dst, i);
}

template<> auto format_to<i32>(buffer_writer& dst, const i32& i, const string_view& format_args) -> void {
    integer_format_to(dst, i);
}

template<> auto format_to<i64>(buffer_writer& dst, const i64& i, const string_view& format_args) -> void {
    integer_format_to(dst, i);
}

template<> auto format_to<u8>(buffer_writer& dst, const u8& i, const string_view& format_args) -> void {
    integer_format_to(dst, i);
}

template<> auto format_to<u16>(buffer_writer& dst, const u16& i, const string_view& format_args) -> void {
    integer_format_to(dst, i);
}

template<> auto format_to<u32>(buffer_writer& dst, const u32& i, const string_view& format_args) -> void {
    integer_format_to(dst, i);
}

template<> auto format_to<u64>(buffer_writer& dst, const u64& i, const string_view& format_args) -> void {
    integer_format_to(dst, i);
}

/*template<typename T> auto float_str_len(const T& f, const u32& precision = 6) -> u64 {
    u64 sign_len = f < 0.0 ? 1 : 0;
    f64 absolute_f = fabs(f);
    f64 digits = log10(absolute_f);
    return sign_len + ceil(digits) + (precision > 0 ? 1 + precision : 0);
}*/

template<typename T> auto float_str_len(const T& f, const u32& precision = 6) -> u64 {
    u64 sign_len = f < 0.0 ? 1 : 0;
    f64 absolute_f = fabs(f);
    f64 digits = log10(absolute_f);
    if(digits > static_cast<f64>(precision)) {
        // Will print in sNe+E form
        return sign_len + precision + 3 /*decimal point + e+*/ + strlen(static_cast<u64>(floor(digits)));
    }
    tuple<f64,f64> split = modf(absolute_f);
    u64 integer_part = static_cast<u64>(split.at<0>());
    if(integer_part == 0) {
        // Will print in sNe-E form
        f64 complement_digits = ceil(log10(1.0/absolute_f));
        if(complement_digits > static_cast<f64>(precision-1))
            return sign_len + precision + 3 /*decimal point + e-*/ + strlen(static_cast<u64>(ceil(complement_digits)));
    }
    return sign_len + precision + (precision > digits ? 1 : 0);
}

template<> auto strlen<f32>(const f32& object, const string_view& format_args) -> u64 {
    return float_str_len(object);
}

template<> auto strlen<f64>(const f64& object, const string_view& format_args) -> u64 {
    return float_str_len(object);
}

/*template<typename T> auto float_format_to(buffer_writer& dst, const T& f, const u32& precision = 6) -> void {
    if(f < 0.0) {
        format_to(dst, '-');
    }
    constexpr u64 MAX_DIGITS_IN_U64 = 18;
    f64 absolute_f = fabs(f);
    tuple<f64,f64> split = modf(absolute_f);
    f64 to_write = split.at<0>();
    u64 digits_to_write = ceil(log10(split.at<0>()));
    while(digits_to_write > MAX_DIGITS_IN_U64) {
        f64 scale = pow(10, digits_to_write - MAX_DIGITS_IN_U64);
        f64 this_write = to_write / scale ;
        std:: cout << " scale: " << scale 
                   << " this_write: " << this_write
                   << " to_write: " << to_write
                   << " digits_to_write: " << digits_to_write << std::endl;
        format_to(dst, static_cast<u64>(this_write));
        to_write -= (floor(this_write)*scale);
        digits_to_write -= MAX_DIGITS_IN_U64;
    }
    format_to(dst, static_cast<u64>(to_write));
    if(precision > 0) {
        format_to(dst, '.');
        f64 scaled_fractpart = split.at<1>() * pow(10, precision);
        format_to(dst, static_cast<u64>(to_write));
        while(-dst.tell(relative_to::end) > 0) {
            format_to(dst, '0');
        }
    }
}*/

template<typename T> auto float_format_to(buffer_writer& dst, const T& f, const u32& precision = 6) -> void {
    if(f < 0.0) {
        format_to(dst, '-');
    }
    f64 absolute_f = fabs(f);
    f64 digits = log10(absolute_f);
    if(digits > static_cast<f64>(precision)) { 
        // Will print in sNe+E form
        tuple<f64,f64> split = modf(digits);
        float_format_to(dst, pow(10, split.at<1>()), precision);
        format_to(dst, "e+");
        format_to(dst, static_cast<u64>(split.at<0>()));
        return;
    }
    tuple<f64,f64> split = modf(absolute_f);
    u64 integer_part = static_cast<u64>(split.at<0>());
    if(integer_part == 0) {
        // Will print in sNe-E form
        f64 complement_digits = ceil(log10(1.0/absolute_f));
        if(complement_digits > static_cast<f64>(precision-1)) {
            float_format_to(dst, absolute_f * pow(10, complement_digits), precision);
            format_to(dst, "e-");
            format_to(dst, static_cast<u64>(complement_digits));
            return;
        }
    }
    format_to(dst, static_cast<u64>(integer_part));
    if (digits < precision) {
        u64 left_over_digits = precision - (digits < 0 ? 1 : digits);
        format_to(dst, ".");
        unsigned_int_format_to(dst, static_cast<u64>(round(split.at<1>() * pow(10, floor(left_over_digits)))), left_over_digits);
    }
}

template<> auto format_to<f32>(buffer_writer& dst, const f32& f, const string_view& format_args) -> void {
    return float_format_to(dst, f);
}

template<> auto format_to<f64>(buffer_writer& dst, const f64& f, const string_view& format_args) -> void {
    return float_format_to(dst, f);
}

} // namespace root