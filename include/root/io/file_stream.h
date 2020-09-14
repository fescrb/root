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

#include <root/io/stream.h>

#include <cstdio>

namespace root {

class file_stream final : public stream {
public:
    explicit file_stream(FILE* f) : m_file(f) {} 

    constexpr static i64 INVALID_POSITION = -1L;

    auto read(void* dst, const u64& len) ->  value_or_error<u64> override;
    auto write(const void* src, const u64& len) ->  value_or_error<u64> override;
    auto seek(const i64& offset, const relative_to& relative_to = relative_to::start) -> error override;
    auto tell(const relative_to& relative_to = relative_to::start) const -> value_or_error<i64> override;

    ~file_stream() {}

private:
    FILE* m_file;
};

} // namespace root