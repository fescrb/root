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

#include <limits>

namespace root {

class stream {
public:
    enum class relativity : u8 {
        start = 0,
        current = 1,
        end = 2
    };

    constexpr static u64 INVALID_SIZE = std::numeric_limits<u64>::max();

    virtual u64 read(void* dst, const u64& len) = 0;
    virtual u64 write(void* src, const u64& len) = 0;
    virtual void seek(const i64& offset, const relativity& offset_relativity = relativity::start) = 0;
    virtual u64 tell(const relativity& tell_relativity = relativity::start) = 0;

    virtual ~stream() {}
};

} // namespace root