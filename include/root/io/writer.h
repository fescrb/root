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

#include <root/io/stream.h>

namespace root {

template<typename stream_class = stream>
class writer {
public:
    inline explicit writer(stream* s) : m_stream(s) {}

    inline auto write(void* src, const u64& len) -> error {
        return stream->write(src, len);
    }

    inline auto seek(const i64& offset, const relative_to& relative_to = relative_to::start) -> error {
        return stream->seek(offset, relative_to);
    }

    inline auto tell(const relative_to& relative_to = relative_to::start) const -> value_or_error<i64> {
        return stream->tell(relative_to);
    }

private:
    stream* m_stream;
};

} // namespace root