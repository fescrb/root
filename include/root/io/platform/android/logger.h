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

#include <android/log.h>
#include <root/io/format.h>

namespace root {

class logger {
public:
    template<typename... Args>
    inline auto i(const string_view& tag, const format_string& fmt, Args... args) -> void {
        log<ANDROID_LOG_INFO>(tag, fmt, args...);
    }

    template<typename... Args>
    inline auto e(const string_view& tag, const format_string& fmt, Args... args) -> void {
        log<ANDROID_LOG_ERROR>(tag, fmt, args...);
    }

    template<typename... Args>
    inline auto d(const string_view& tag, const format_string& fmt, Args... args) -> void {
        log<ANDROID_LOG_DEBUG>(tag, fmt, args...);
    }

    template<typename... Args>
    inline auto w(const string_view& tag, const format_string& fmt, Args... args) -> void {
        log<ANDROID_LOG_WARN>(tag, fmt, args...);
    }

private:
    template<int p, typename... Args> 
    inline auto log(const string_view& tag, const format_string& fmt, Args... args) -> void {
        string str = format(fmt, args...);
        __android_log_buf_write(LOG_ID_MAIN, p, tag.size()? tag.data(): "", str.data());
    }
    
};

}