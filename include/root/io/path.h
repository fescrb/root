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

#include <root/core/string.h>
#include <root/core/string_view.h>
#include <root/io/formatter.h>

namespace root {

namespace path {

constexpr i8 EXTENSION_DELIMITER = '.';

#if defined(ROOT_WIN)
constexpr i8 FOLDER_DELIMITER = '\\';
#else 
constexpr i8 FOLDER_DELIMITER = '/';
#endif

constexpr auto basename(const string_view& path) -> string_view {
    auto location = find(path.rbegin(), path.rend(), FOLDER_DELIMITER);
    if(location == path.rbegin()) {
        if(distance(location, path.rend()) > 1) {
            location = find(++path.rbegin(), path.rend(), FOLDER_DELIMITER);
            return string_view(++path.rbegin(), location);
        }
        return path; // Path is "/"
    }
    return string_view(path.rbegin(), location);
}

constexpr auto dirname(const string_view& path) -> string_view {
    auto location = find(path.rbegin(), path.rend(), FOLDER_DELIMITER);
    root_assert(location != path.rend());
    if(location == path.rbegin()&& distance(location, path.rend()) > 1) location = find(++path.rbegin(), path.rend(), FOLDER_DELIMITER);
    if(*location == FOLDER_DELIMITER && distance(location, path.rend()) > 1) location++;
    return string_view(location, path.rend());
}

constexpr auto ext(const string_view& path) -> string_view {
    constexpr string_view NO_EXT = "";
    if(*path.rbegin() == FOLDER_DELIMITER) return NO_EXT;
    const string_view filename = basename(path);
    auto location = find(filename.rbegin(), filename.rend(), EXTENSION_DELIMITER);
    if(location == filename.rend()) return NO_EXT;
    return string_view(path.rbegin(), location);
}

auto binary_location() -> const string_view&;

auto binary_name() -> const string_view&;

inline auto join(const string_view& lhs, const string_view& rhs, allocator* alloc = allocator::get_default()) -> string {
    formatter formatter(alloc);
    return formatter.format("{}{}{}", lhs, FOLDER_DELIMITER, rhs);
}

} // namespace path

} // namespace root