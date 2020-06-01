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
class weak_ptr final {
public:
    weak_ptr() {}

    explicit weak_ptr(const strong_ptr<C>& ptr) 
    :   weak_ptr(ptr.m_ptr.m_memory, ptr.m_ptr.m_ref_count, ptr.m_ptr.m_allocator) {}

    weak_ptr(const weak_ptr<C>& other) 
    :   weak_ptr(other.m_ptr.m_memory, other.m_ptr.m_ref_count, other.m_ptr.m_allocator) {}

    weak_ptr(weak_ptr<C>&& other) {
        m_ptr.m_memory = std::move(other.m_ptr.m_memory);
        m_ptr.m_ref_count = std::move(other.m_ptr.m_ref_count);
        m_ptr.m_allocator = std::move(other.m_ptr.m_allocator);
    }
    
    auto operator=(const weak_ptr<C>& other) -> weak_ptr<C>& {
        if(this != &other) {
            unlock();
            m_ptr.m_memory = other.m_ptr.m_memory;
            m_ptr.m_ref_count = other.m_ptr.m_ref_count;
            m_ptr.m_allocator = other.m_ptr.m_allocator;
            lock();
        } 
        return *this;
    }

    auto operator=(weak_ptr<C>&& other) -> weak_ptr<C>& {
        unlock();
        m_ptr.m_memory = std::move(other.m_ptr.m_memory);
        m_ptr.m_ref_count = std::move(other.m_ptr.m_ref_count);
        m_ptr.m_allocator = std::move(other.m_ptr.m_allocator);
        lock();
        return *this;
    }

    inline auto promote() -> strong_ptr<C>;

    inline auto valid() const -> bool {
        return m_ptr.m_memory != nullptr;
    }

    inline operator bool() const {
        return valid();
    }

    inline auto clear() -> void;

    inline ~weak_ptr() {
        unlock();
    }

private:
    auto unlock() -> void;
    auto lock() -> void;

    weak_ptr(C* memory, reference_counter* ref_count, allocator* alloc) 
    :   m_ptr(memory, ref_count, alloc) {
        lock();
    }

    managed_ptr<C> m_ptr;
};

template <typename C>
inline auto weak_ptr<C>::unlock() -> void {  
    if(m_ptr.m_ref_count && m_ptr.m_ref_count->decrement_weak()) {
        strong_ptr<C>::check_ref_count_for_deletion(m_ptr);
    }
}

template<typename C>
inline auto weak_ptr<C>::lock() -> void {
    if(!m_ptr.m_ref_count || !m_ptr.m_ref_count->try_increment_weak()) {
        m_ptr.m_memory = nullptr;
        m_ptr.m_ref_count = nullptr;
    }
}

template<typename C>
inline auto weak_ptr<C>::clear() -> void {
    unlock();
    m_ptr.m_memory = nullptr;
    m_ptr.m_ref_count = nullptr;
}

template<typename C>
inline auto weak_ptr<C>::promote() -> strong_ptr<C> {
    strong_ptr<C> ptr(m_ptr.m_memory, m_ptr.m_ref_count, m_ptr.m_allocator);
    ptr.lock(); // Increment strong
    if(!ptr) clear();
    return ptr;
}
} // namespace root