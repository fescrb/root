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

#include <root/core/buffer.h>
#include <root/memory/strong_ptr.h>

namespace root {

class file_interface;

class input_file {
public:
    auto read(buffer* dst) -> u64;

    ~input_file();

    input_file()
    : m_file() {}

    input_file(input_file&& other)
    :   m_file(std::move(other.m_file)) {}

    input_file(const input_file&) = delete;

    inline auto valid() const -> bool {
        return m_file.valid();
    }

private:
    explicit input_file(strong_ptr<file_interface>& f)
    :   m_file(f) {}

    strong_ptr<stream> m_stream;

    friend class asset_manager;
};

} // namespace root