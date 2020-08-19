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

#pragma once

#ifndef ROOT_ASSERT

#define root_assert(_expr_) ((void) 0)

#define root_static_assert(_expr_) ((void) 0)

#else 

#define root_assert(_expr_) root::assert(_expr_, "_expr_", __FILE__, __LINE__)

#define root_static_assert(_expr_) static_assert(_expr_)

namespace root {

auto _assert_fail(const char* expr_str, const char* file, const int line_num) -> void;

auto inline assert(const bool expr_result, const char* expr_str, const char* file, const int line_num) -> void {
    if(!expr_result) {
        _asert_fail(expr_str, file, line_num);
    }
}

} // namespace root

#endif