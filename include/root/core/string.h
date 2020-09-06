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

#include <root/core/array.h>
#include <root/core/primitives.h>

#include <cstring>

namespace root {

class string : public array<i8> {
public:
    explicit inline string(const char* str, allocator* alloc = allocator::default_allocator()) 
    :   array(strlen(str), alloc) {
        for(u64 i = 0; i < m_length; i++) {
            m_data[i] = str[i];
        }
    }

    explicit inline string(const u64& length, allocator* alloc = allocator::default_allocator()) 
    : array(length, alloc) {}

    string(const string&) = delete;
    inline string(string&& other) 
    : array(std::move(other)) {}

    inline string(buffer&& b) 
    :   array(std::move(b)) {}
};

} // namespace root