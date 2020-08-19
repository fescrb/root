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

#include <root/io/input_file.h>
#include <root/io/private/file_interface.h>
#include <root/core/assert.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

namespace root {

auto input_file::read(buffer* dst) -> u64 {
    root_assert(m_file);
    return m_file->read(dst);
}

input_file::~input_file() {
    
}

} // namespace root