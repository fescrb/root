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

#include <root/io/path.h>

#if defined(ROOT_LINUX)
#include <unistd.h> 
#include <limits.h>
#endif

#if defined(ROOT_WIN)
#include <windows.h>
#include <libloaderapi.h>
#endif

namespace root {

namespace path {

auto exe_path() -> string_view {
    static string_view location;
    static char location_str[PATH_MAX];
    if(!location.size()) {
#if defined(ROOT_LINUX)
        size_t loc_len = readlink("/proc/self/exe", location_str, PATH_MAX);
        location_str[loc_len] = '\0'; // readlink doesn't nul-terminate strings
        location = string_view(location_str);
#endif
#if defined(ROOT_WIN)
        GetModuleFileNameA(nullptr, location_str, MAX_PATH);
        location = string_view(location_str);
#endif
    }
    return location;
}

auto binary_location() -> const string_view& {
    static string_view location;
    if(!location.size()) {
        location = dirname(exe_path());
    } 
    return location;
}


auto binary_name() -> const string_view& {
    static string_view location;
    if(!location.size()) {
        location = basename(exe_path());
    } 
    return location;
}

} // namespace path

} // namespace root