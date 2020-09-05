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

#include <root/core/primitives.h>

namespace root {

template<u64 I, typename T, typename... Ts> 
struct variadric_type_by_index {
    typedef typename variadric_type_by_index<I-1, Ts...>::type type;
};

template<typename T, typename... Ts> 
struct variadric_type_by_index<0, T, Ts...> {
    typedef T type;
};

template<typename T> 
struct variadric_type_by_index<0, T> {
    typedef T type;
};

template<u64 I>
struct variadric_index_error {
    constexpr static bool value = false; 
};

template<u64 I,typename T> 
struct variadric_type_by_index<I, T> {
    static_assert(variadric_index_error<I>::value, "Variadric template index out of bounds.");
};


} // namespace root