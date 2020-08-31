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

#include <limits>

namespace root {

class buffer_stream final : public stream {
public:

    u64 read(void* dst, const u64& len) override;
    u64 write(void* src, const u64& len) override;
    void seek(const i64& offset, const relativity& offset_relativity = relativity::start) override;
    u64 tell(const relativity& tell_relativity = relativity::start) override;

    virtual ~buffer_stream() {}
};

} // namespace root