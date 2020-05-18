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
#include <root/memory/allocator.h>

namespace root {

template<typename C>
class strong_ptr final : public managed_ptr<C> {
public:
    template<typename... Args>
    static strong_ptr<C> make(Args... args, allocator& alloc) {
        C* memory = alloc<C>.make(args);
        reference_counter* ref_counter = alloc<reference_counter>.make();
        strong_ptr<C> ptr = strong_ptr<C>(memory, ref_counter, alloc);
        ref_counter->decrement_strong();
    }

    strong_ptr(const strong_ptr& other)
    :   strong_ptr(other.m_memory, other.m_ref_counter, other.m_allocator){}

    virtual ~strong_ptr() {
        if(m_ref_count && m_ref_count->decrement_strong()) {
            m_allocator.del<C>(m_memory);
        }
    }

    inline auto operator*() const -> C& {
        return *m_memory;
    }

    inline auto operator->() const -> C* {
        return m_memory;
    }

    inline auto valid() const -> bool {
        return m_memory != nullptr;
    }

    inline operator bool() const {
        return valid();
    }

private:
    strong_ptr(C* memory, reference_counter* counter, allocator& alloc)
    :   managed_ptr(memory, counter, alloc) {
        if(!m_ref_count || !m_ref_count->try_increment_strong()) {
            m_memory = nullptr;
            m_ref_count = nullptr;
        }

    }

    friend class weak_ptr<C>;
};
} // namespace root