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

#include <root/io/platform/android/aasset_stream.h>


#include <cstdio>

namespace root {

auto aasset_stream::read(void* dst, const u64& len) ->  value_or_error<u64> {
    AAsset_read(m_asset, dst, len);
}

auto aasset_stream::write(const void* src, const u64& len) ->  value_or_error<u64> {
    return error::INVALID_OPERATION;
}

auto aasset_stream::seek(const i64& offset, const relative_to& relative_to = relative_to::start) -> error {
    int origin = 0;
    switch(relative_to) {
        case relative_to::start:
            origin = SEEK_SET;
            break;
        case relative_to::current_position:
            origin = SEEK_CUR;
            break;
        case relative_to::end:
            origin = SEEK_END;
            break;
    }
    if(AAsset_seek64(m_asset, offset, origin) == INVALID_POSITION)
        return error::UNKNOWN_ERROR;
    return error::NO_ERROR;
}

auto aasset_stream::tell(const relative_to& relative_to = relative_to::start) const -> value_or_error<i64> {
    switch(relative_to) {
        case relative_to::start:
            return AAsset_getLength64(m_asset) - AAsset_getRemainingLength64(m_asset);
        case relative_to::current_position:
            return 0;
        case relative_to::end:
            return - AAsset_getRemainingLength64(m_asset);
    }
}

} // namespace root
