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

#include <root/core/buffer.h>
#include <root/io/stream.h>

#include <limits>

namespace root {

class buffer_stream final : public stream {
public:
    explicit buffer_stream(const buffer& b)
    :   backing(b),
        pointer(0) {}

    explicit buffer_stream(const buffer_slice& b)
    :   backing(b),
        pointer(0) {}

    auto read(void* dst, const u64& len) -> value_or_error<u64> override;
    auto write(const void* src, const u64& len) -> value_or_error<u64> override;
    auto seek(const i64& offset, const relative_to& relative_to = relative_to::start) -> error override;
    auto tell(const relative_to& relative_to = relative_to::start) const -> value_or_error<i64> override;
    
    ~buffer_stream() {}

private:
    // TODO: read & write should return number of bytes written
    inline auto memcpy_helper(void* dst, const void* src, const u64& len) -> value_or_error<u64> {
        if (pointer < 0 || pointer > static_cast<i64>(backing.size())) return error::INVALID_OPERATION;
        u64 remainder = backing.size() - pointer;
        u64 write_len = remainder < len ? remainder : len; 
        memcpy(dst, src, write_len);
        pointer+=write_len;
        return write_len;
    }

    buffer_slice backing;
    i64 pointer;
};

} // namespace root