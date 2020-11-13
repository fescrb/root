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

#include <root/core/primitives.h>
#include <root/memory/allocator.h>

namespace root {
// TODO: most of the functionality
class monotonic_allocator : public allocator {
public:
    monotonic_allocator(const u64& bytes, allocator* backing_resource = allocator::get_default())
    :   m_size(bytes),
        m_memory(static_cast<u8*>(backing_resource->malloc(bytes, 1))),
        m_head(m_memory),
        m_backing_resource(backing_resource){}

    virtual auto malloc(const u64& bytes, const u64& alignment) -> void* override {
        
    }

    virtual auto free(void* mem) -> void override {}

    virtual ~monotonic_allocator() {
        m_backing_resource->free(m_memory);
    }

protected:
    const u64 m_size;
    u8* const m_memory;
    u8* m_head;
    allocator* m_backing_resource;
};

} // namespace root