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

#include <root/memory/private/managed_ptr.h>
#include <root/memory/allocator.h>

namespace root {

template<typename C> class weak_ptr;

template<typename C>
class strong_ptr final {
public:
    strong_ptr(const strong_ptr& other)
    :   m_ptr(other.m_ptr){
        lock();
    }

    strong_ptr(strong_ptr&& other) {
        m_ptr.m_memory = std::move(other.m_ptr.m_memory);
        m_ptr.m_ref_count = std::move(other.m_ptr.m_ref_count);
        m_ptr.m_allocator = std::move(other.m_ptr.m_allocator);
    };

    strong_ptr() {}

    auto operator=(const strong_ptr<C>& other) -> strong_ptr<C>& {
        if(this != &other) {
            unlock();
            m_ptr.m_memory = other.m_ptr.m_memory;
            m_ptr.m_ref_count = other.m_ptr.m_ref_count;
            m_ptr.m_allocator = other.m_ptr.m_allocator;
            lock();
        } 
        return *this;
    }

    auto operator=(strong_ptr<C>&& other) -> strong_ptr<C>& {
        unlock();
        m_ptr.m_memory = std::move(other.m_ptr.m_memory);
        m_ptr.m_ref_count = std::move(other.m_ptr.m_ref_count);
        m_ptr.m_allocator = std::move(other.m_ptr.m_allocator);
        lock();
        return *this;
    }

    ~strong_ptr() {
        unlock();
    }

    inline auto operator*() const -> C& {
        return *m_ptr.m_memory;
    }

    inline auto operator->() const -> C* {
        return m_ptr.m_memory;
    }

    inline auto valid() const -> bool {
        return m_ptr.m_memory != nullptr;
    }

    inline operator bool() const {
        return valid();
    }

    inline auto clear() -> void {
        unlock();
        m_ptr.m_memory = nullptr;
        m_ptr.m_ref_count = nullptr;   
    }

private:
    strong_ptr(C* memory, reference_counter* counter, allocator* alloc)
    :   m_ptr(memory, counter, alloc) {
    }

    auto lock() -> void ;
    inline auto unlock() -> void;

    static auto check_ref_count_for_deletion(managed_ptr<C>& man_ptr) -> void;

    managed_ptr<C> m_ptr;
    friend class weak_ptr<C>;
    friend class allocator;
};

template <typename C>
inline auto strong_ptr<C>::check_ref_count_for_deletion(managed_ptr<C>& man_ptr) -> void {
    if(man_ptr.m_ref_count && man_ptr.m_allocator && man_ptr.m_ref_count->abandoned() &&  man_ptr.m_ref_count->can_release()) {
        man_ptr.m_allocator->template del<reference_counter>(man_ptr.m_ref_count);
    }
}

template <typename C>
inline auto strong_ptr<C>::unlock() -> void {
    if(m_ptr.m_ref_count && m_ptr.m_allocator && m_ptr.m_ref_count->decrement_strong()) {
        m_ptr.m_allocator->template del<C>(m_ptr.m_memory);
        check_ref_count_for_deletion(m_ptr);
    }
}

template <typename C>
inline auto strong_ptr<C>::lock() -> void {
    if(!m_ptr.m_ref_count || !m_ptr.m_ref_count->try_increment_strong()) {
        m_ptr.m_memory = nullptr;
        m_ptr.m_ref_count = nullptr;
    }
}

template<typename C, typename... Args>
inline auto make_strong(Args... args) -> strong_ptr<C> {
    return allocator::default_allocator()->make_strong<C>(args...);
}
} // namespace root