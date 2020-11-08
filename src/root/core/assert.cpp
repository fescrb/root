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

#include <root/core/assert.h>
#include <root/io/log.h>

#if defined(ROOT_LINUX)
#include <execinfo.h>
#endif

namespace root {

#ifdef ROOT_ASSERT
auto _assert_fail(const char* expr_str, const char* message, const char* file, const int line_num) -> void {
    if(!message) {
        log::e("", "assert({}) failed at {}:{}", expr_str, file, line_num);
    } else {
        log::e("", "assert({}, {}) failed at {}:{}", expr_str, message, file, line_num);
    }
#if defined(ROOT_LINUX)
    constexpr i32 MAX_BT = 64;
    void* bt[MAX_BT];
    i32 size = backtrace(bt, MAX_BT);
    char** bt_symbols = backtrace_symbols(bt, size);
    log::e("assert", "backtrace:");
    for(int i = 0; i < size; i++) {
        log::e("assert", "{} {} {}", i, bt[i], bt_symbols[i]);
    }
#endif
    abort();
}
#endif

} // namespace root