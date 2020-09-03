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
#include <root/core/error.h>

#include <limits>

namespace root {

class stream {
public:
    enum class relative_to : u8 {
        start = 0,
        current_position = 1,
        end = 2
    };

    constexpr static u64 INVALID_SIZE = std::numeric_limits<u64>::max();

    virtual auto read(void* dst, const u64& len) -> error = 0;
    virtual auto write(void* src, const u64& len) -> error = 0;
    virtual auto seek(const i64& offset, const relative_to& relative_to = relative_to::start) -> error = 0;
    virtual auto tell(const relative_to& relative_to = relative_to::start) const -> value_or_error<i64> = 0;

    virtual ~stream() {}
};

} // namespace root