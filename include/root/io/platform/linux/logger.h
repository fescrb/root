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

#include <root/io/writer.h>
#include <root/io/format.h>

namespace root {

class logger {
public:
    explicit logger(writer* out) : m_writer(out) {}

    template<typename... Args>
    inline auto i(const string_view& tag, const format_string& fmt, Args... args) -> void {
        constexpr char const* PRIO_TAG = "INFO: ";
        constexpr u64 PRIO_LEN = strlen(PRIO_TAG);
        m_writer->write(PRIO_TAG, PRIO_LEN);
        print_tag(tag);
        string str = format(fmt, args...);
        m_writer->write(str.data(), str.size());
        endl();
    }

    template<typename... Args>
    inline auto e(const string_view& tag, const format_string& fmt, Args... args) -> void {
        constexpr char const* PRIO_TAG = "ERROR: ";
        constexpr u64 PRIO_LEN = strlen(PRIO_TAG);
        m_writer->write(PRIO_TAG, PRIO_LEN);
        print_tag(tag);
        string str = format(fmt, args...);
        m_writer->write(str.data(), str.size());
        endl();
    }

    template<typename... Args>
    inline auto d(const string_view& tag, const format_string& fmt, Args... args) -> void {
        constexpr char const* PRIO_TAG = "DEBUG: ";
        constexpr u64 PRIO_LEN = strlen(PRIO_TAG);
        m_writer->write(PRIO_TAG, PRIO_LEN);
        print_tag(tag);
        string str = format(fmt, args...);
        m_writer->write(str.data(), str.size());
        endl();
    }

    template<typename... Args>
    inline auto w(const string_view& tag, const format_string& fmt, Args... args) -> void {
        constexpr char const* PRIO_TAG = "WARN: ";
        constexpr u64 PRIO_LEN = strlen(PRIO_TAG);
        m_writer->write(PRIO_TAG, PRIO_LEN);
        print_tag(tag);
        string str = format(fmt, args...);
        m_writer->write(str.data(), str.size());
        endl();
    }

private:
    inline auto print_tag(const string_view& tag) -> void {
        constexpr char const * COLON = ": ";
        constexpr u64 COLON_LEN = strlen(COLON);
        if(tag.size()) {
            m_writer->write(tag.data(), tag.size());
            m_writer->write(COLON, COLON_LEN);
        }
    }

    inline auto endl() -> void {
        constexpr char const * ENDL = "\n";
        constexpr u64 ENDL_LEN = strlen(ENDL);
        m_writer->write(ENDL, ENDL_LEN);
    }

    writer * const  m_writer;
};

} // namespace root