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

#include <root/memory/private/reference_counter.h>

#include <iostream>

namespace root {
template<typename C>
class managed_ptr {
public:
    auto operator=(const managed_ptr& other) -> managed_ptr& = delete;
    auto operator=(managed_ptr&& other) -> managed_ptr& = delete;
    
protected:
    virtual ~managed_ptr() {
        if(m_ref_count && m_ref_count->abandoned()) {
            m_allocator.del<reference_counter>(m_ref_count);
        }
    }

    managed_ptr(const managed_ptr& other)
    :   managed_ptr(other.m_memory, other.m_ref_count, other.m_allocator) {}

    managed_ptr(managed_ptr&& other) 
    :   managed_ptr(other.m_memory, other.m_ref_count, other.m_allocator) {}

    managed_ptr(C* memory, reference_counter* ref_counter, allocator& alloc)
    :   m_memory(memory),
        m_ref_count(ref_counter),
        m_allocator(alloc) {}

    C                   *m_memory;
    reference_counter   *m_ref_count;
    allocator           &m_allocator;
};
} // namespace root