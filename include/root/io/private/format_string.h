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

#include <root/core/string_view.h> 
#include <root/core/private/variadric_type_info.h>

namespace root {

class format_string : public string_view {
public:
    constexpr format_string(const char* str_lit) noexcept 
    :   string_view(str_lit) { }

    constexpr format_string(const iterator& begin, const iterator& end) noexcept
    :   string_view(begin, end) {}

    constexpr format_string(const string_view& str_lit) noexcept
    :   string_view(str_lit) {}

    format_string(const format_string&) = delete;
    format_string(format_string&&) = delete;



};

} // namespace root