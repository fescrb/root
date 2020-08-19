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
#include <root/core/buffer.h>

namespace root {

class stream {
public:
    enum class offset_relativity : u8 {
        current_position = 0,
        file_start = 1
    };

    virtual u64 read(buffer* dst) = 0;
    // TODO: write()
    virtual i64 seek(const i64& offset, const offset_relativity& offset_relativity) = 0;
    virtual u64 remaining() = 0;
    virtual u64 length() = 0;

    virtual ~stream() {}
};

} // namespace root