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

#if defined(ROOT_LINUX)
#include <unistd.h> 
#include <limits.h>
#endif

namespace root {

namespace path {

#if defined(ROOT_LINUX)
constexpr i8 FOLDER_DELIMITER = '/';
#else 
#pragma message( "FOLDER_DELIMITER not defined" )
#endif


constexpr auto dirname(const string_view& path) -> string_view {
    auto location = find(path.rbegin(), path.rend(), FOLDER_DELIMITER);
    root_assert(location != path.rend());
    if(location == path.rbegin()&& distance(location, path.rend()) > 1) location = find(++path.rbegin(), path.rend(), FOLDER_DELIMITER);
    if(*location == FOLDER_DELIMITER && distance(location, path.rend()) > 1) location++;
    return string_view(location, path.rend());
}

inline auto binary_location() -> const string_view& {
    static string_view location;
#if defined(ROOT_LINUX)
    static char location_str[PATH_MAX];
    if(!location.size()) {
        size_t loc_len = readlink("/proc/self/exe", location_str, PATH_MAX);
        location_str[loc_len] = '\0'; // readlink doesn't nul-terminate strings
        location = dirname(location_str);
    } 
#endif
    return location;
}

} // namespace path

} // namespace root