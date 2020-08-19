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

#include <cstdlib>
#include <root/core/primitives.h>

namespace root {

class allocator {
public:
    template<typename C, typename... Args>
    inline auto make(Args... args) -> C* {
        C* ptr = static_cast<C*>(malloc(sizeof(C), alignof(C)));
        new (ptr) C(args...);
        return ptr;
    }

    template<typename C>
    inline auto del(C* ptr) -> void {
        ptr->~C();
        free(ptr, sizeof(C), alignof(C));
    }

    virtual auto malloc(const u64& bytes, const u64& alignment) -> void* = 0;
    virtual auto free(void* mem, const u64& bytes, const u64& alignment) -> void = 0;

    inline static auto default_allocator() -> allocator* {
        return m_default_allocator;
    }

    inline static auto set_default_allocator(allocator* alloc) -> void{
        m_default_allocator = alloc;
    }

    virtual ~allocator() {}

private:
    static allocator* m_default_allocator;
};
} // namespace root