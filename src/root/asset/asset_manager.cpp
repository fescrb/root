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

#include <root/asset/asset_manager.h>

#include <root/io/file_stream.h>
#include <root/io/log.h>

namespace root {

asset_manager* asset_manager::m_manager = nullptr;

auto asset_manager::raw_load(const string_view& id) -> buffer {
    if(!m_manager) {
        m_manager = new asset_manager();
    }

    return m_manager->load_buffer(id);
}

auto asset_manager::load_buffer(const string_view& id) -> buffer {
    string full_path = path::join(m_asset_root, id, m_alloc);
    FILE* file = fopen(full_path.data(), "r");
    log::d("asset_manager", "Opening {} {}", static_cast<string_view>(full_path), file);
    root_assert(file);
    file_stream stream(file);
    stream.seek(0, relative_to::end);
    u64 size = stream.tell();
    stream.seek(0, relative_to::start);
    log::d("asset_manager", "File is {} bytes", size);
    buffer buff(size, alignof(u8), m_alloc);
    stream.read(buff, size);
    return buff;
}

asset_manager::asset_manager(const string_view& asset_root, allocator* alloc) 
:   m_asset_root(asset_root.size(), alloc), m_alloc(alloc) {
    memcpy(m_asset_root.data(), asset_root.data(), asset_root.size());
}

} // namespace root