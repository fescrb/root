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

#include <root/core/array_view.h>

namespace root {

class string_view : public array_view<i8> {
public:
    inline string_view() { clear(); } 

    inline string_view(char* data, const u64& first, const u64& last)
    :   array_view(data, first, last) {}

    inline string_view(string_view&& other) 
    :   array_view(std::move(other)) {}

    inline string_view(const string_view& other)
    :   array_view(other) {}

    inline string_view(array_view<i8>&& other) 
    :   array_view(std::move(other)) {}

    inline string_view(const array_view<i8>& other)
    :   array_view(other) {}
    
    auto operator=(const string_view& other) -> array_view& {
        return array_view<char>::operator=(other);
    }

    auto operator=(array_view&& other) -> array_view& {
        return array_view<char>::operator=(std::move(other));
    }
};

} // namespace root