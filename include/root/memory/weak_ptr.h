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

#include <root/memory/strong_ptr.h>

namespace root {

template<typename C>
class weak_ptr final : managed_ptr<C> {
public:
    explicit weak_ptr(const strong_ptr<C>& ptr) 
    :   weak_ptr(ptr.m_memory, ptr.m_ref_count, ptr.m_allocator) {}

    explicit weak_ptr(const weak_ptr<C>& other) 
    :   weak_ptr(other.m_memory, other.m_ref_count, other.m_allocator) {}

    inline auto promote() const -> strong_ptr<C> {
        strong_ptr<C> ptr(m_memory, m_ref_count, m_allocator);
        if(!ptr) {
            abandon();
        }
        return ptr;
    }

    inline auto valid() const -> bool {
        return m_memory != nullptr;
    }

    inline operator bool() const {
        return valid();
    }

    virtual ~weak_ptr() {
        if(m_ref_count) {
            m_ref_count->decrement_weak();
        }
    }

private:
    auto abandon() -> void {
        if(m_ref_count) {
            if(m_ref_count->decrement_weak()) {
                if(m_ref_count->abandoned()) {
                    m_allocator->del<reference_counter>(m_ref_count);
                    m_ref_count = nullptr;
                    m_memory = nullptr;
                }
            }
        }
    }

    explicit weak_ptr(C* memory, reference_counter* ref_count, allocator& alloc) 
    :   managed_ptr(memory, ref_count, alloc) {
        if(!ref_count || !ref_count->try_increment_weak()) {
            m_memory = nullptr;
            m_ref_count = nullptr;
        }
    }

};
} // namespace root