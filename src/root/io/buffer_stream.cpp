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

#include <root/io/buffer_stream.h>

#include <algorithm>

namespace root {

auto buffer_stream::read(void* dst, const u64& len) -> error {
    if (!backing) return error::DEAD_OBJECT;
    return memcpy_helper(dst, backing.at(pointer), len);
}

auto buffer_stream::write(void* src, const u64& len) -> error {
    if (!backing) return error::DEAD_OBJECT;
    return memcpy_helper(backing.at(pointer), src, len);
}

auto buffer_stream::seek(const i64& offset, const relative_to& relative_to) -> error {
    if (!backing) return error::DEAD_OBJECT;
    switch(relative_to) {
        case relative_to::start:
            pointer = offset;
            break;
        case relative_to::current_position:
            pointer += offset;
            break;
        case relative_to::end:
            pointer = backing.size() + offset;
    }
    return error::NO_ERROR;
}

auto buffer_stream::tell(const relative_to& relative_to) const -> value_or_error<i64> {
    if (!backing) return error::DEAD_OBJECT; // TODO better error
    switch(relative_to) {
        case relative_to::start:
            return pointer;
        case relative_to::current_position:
            return 0;
        case relative_to::end:
            return pointer - backing.size();
    }
}

} // namespace root