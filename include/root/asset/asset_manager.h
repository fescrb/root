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
#include <root/core/string.h>
#include <root/core/string_view.h>
#include <root/io/path.h>

namespace root {

class asset_manager {
public:
    // TODO: May be temporary
    static auto raw_load(const string_view& id) -> buffer;

    // Might need to uncomment this if all default parameters are removed
    //asset_manager() = delete;
    asset_manager(const asset_manager&) = delete;
    asset_manager(asset_manager&&) = delete;
private:
    explicit asset_manager(const string_view& asset_root = path::binary_location(), 
                           allocator* alloc = allocator::default_allocator());

    auto load_buffer(const string_view& id) -> buffer;

    static asset_manager* m_manager;

    allocator* m_alloc;
    string m_asset_root;
};

} // namespace root