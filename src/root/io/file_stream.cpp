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

#include <root/io/file_stream.h>

namespace root {

auto file_stream::read(void* dst, const u64& len) -> value_or_error<u64> {
    u64 res = fread(dst, 1, len, m_file);
    if(res != len && feof(m_file) == 0) {
        return error::UNKNOWN_ERROR;
    }
    return res;
}

auto file_stream::write(const void* src, const u64& len) -> value_or_error<u64> {
    u64 res = fwrite(src, 1, len, m_file);
    if(res != len && feof(m_file) == 0) {
        return error::UNKNOWN_ERROR;
    }
    return res;
}

auto file_stream::seek(const i64& offset, const relative_to& relative_to) -> error {
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
    if(fseek(m_file, offset, origin) != 0)
        return error::UNKNOWN_ERROR;
    return error::NO_ERROR;
}

auto file_stream::tell(const relative_to& relative_to) const -> value_or_error<i64> {
    i64 pos = ftell(m_file);
    if(pos == INVALID_POSITION) return error::UNKNOWN_ERROR;
    switch(relative_to) {
        case relative_to::start:
            return pos;
        case relative_to::current_position:
            return 0;
        case relative_to::end:
            // A bit more involved
            fpos_t pos_mem;
            if(fgetpos(m_file, &pos_mem) != 0) return error::UNKNOWN_ERROR;
            if(fseek(m_file, 0, SEEK_END) != 0) return error::UNKNOWN_ERROR;
            i64 size = ftell(m_file);
            if(size == INVALID_POSITION) return error::UNKNOWN_ERROR;
            if(fsetpos(m_file, &pos_mem) != 0) return error::UNKNOWN_ERROR;
            return size - pos;
    }
}

} // namespace root