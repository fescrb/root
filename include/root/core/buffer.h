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

#include <root/memory/allocator.h>
#include <root/core/primitives.h>
#include <root/core/assert.h>

#include <utility>
#include <cstring>

namespace root {

class buffer {
public:
    inline buffer()
    :   m_data(nullptr),
        m_byte_size(0),
        m_alloc(nullptr) {}

    explicit buffer(const u64& byte_size,  allocator* alloc = allocator::default_allocator())
    :   m_byte_size(byte_size),
        m_alloc(alloc) {
        root_assert(byte_size != 0);
        m_data = reinterpret_cast<u8*>(alloc->malloc(byte_size, ALIGNMENT));
    }

    buffer(const buffer& other) = delete;
    inline buffer(buffer&& other)
    :   m_data(std::move(other.m_data)),
        m_byte_size(std::move(other.m_byte_size)),
        m_alloc(std::move(other.m_alloc)) {
        other.clear();
    }

    inline auto operator=(const buffer& other) -> buffer& = delete;
    inline auto operator=(buffer&& other) -> buffer&{
        m_data = std::move(other.m_data);
        m_byte_size = std::move(other.m_byte_size);
        m_alloc = std::move(other.m_alloc);
        other.clear();
        return *this;
    }

    inline auto raw() const -> void* {
        return reinterpret_cast<void*>(m_data);
    }

    inline auto size() const -> u64 {
        return m_byte_size;
    }

    // TODO: write a named function equivalent
    inline operator bool() const {
        return m_data && m_byte_size && m_alloc; 
    }

    inline operator void*() const {
        return raw();
    }

    ~buffer() {
        root_assert((m_data && m_alloc && m_byte_size) ^ (!m_data && !m_alloc && !m_byte_size)); 
        if(m_data && m_alloc && m_byte_size) {
            m_alloc->free(m_data, m_byte_size, ALIGNMENT);
        }
        m_data = nullptr;
        m_alloc = nullptr;
        m_byte_size = 0;
    }

    class view {
    public:
        inline view(view&& other) 
        :   target(other.target),
            offset(std::move(other.offset)),
            limit(std::move(other.limit)) {}

        inline view(const view& other)
        :   target(other.target),
            offset(other.offset),
            limit(other.limit) {}

        auto operator=(const view&) -> view& = delete;
        auto operator=(view&&) -> view& = delete;

        inline auto size() const -> u64 {
            return limit - offset;
        }

        inline auto raw() const -> void* {
            return reinterpret_cast<void*>(reinterpret_cast<u8*>(target.raw()) + offset);
        }

        inline operator void*() const {
            return raw();
        }

        inline operator bool() const {
            return target;
        }
        
        template<typename T>
        inline auto at(const T& extra_offset) const -> view {
            root_assert(offset + extra_offset < size());
            return view(target, static_cast<u64>(offset + extra_offset), limit);
        } 

        template<typename T1, typename T2>
        inline auto range(const T1& start, const T2& end) const -> view {
            root_assert(start + offset < size());
            root_assert(end + offset < size());
            return view(target, static_cast<u64>(offset+start), static_cast<u64>(offset+end));
        }

        template<typename T>
        inline auto operator+(const T& extra_offset) const -> view {
            return at(extra_offset);
        }

        const buffer& target;
        const u64 offset;
        const u64 limit;
    private:
        inline view(const buffer& b, const u64& o, const u64& l) 
        :  target(b), offset(o), limit(l) {}

        friend class buffer;
    };

    template<typename T>
    inline auto at(const T& offset) const -> view {
        root_assert(offset < m_byte_size);
        return view(*this, static_cast<u64>(offset), m_byte_size);
    } 

    // TODO ensure that T is unsigned
    template<typename T>
    inline auto operator+(const T& offset) const -> view {
        return at(offset);
    }

    template<typename T1, typename T2>
    inline auto range(const T1& start, const T2& end) const -> view {
        root_assert(start < m_byte_size);
        root_assert(end < m_byte_size);
        return view(*this, static_cast<u64>(start), static_cast<u64>(end));
    }

    template<typename T>
    inline auto limit(const T& size) const -> view {
        root_assert(size < m_byte_size);
        return view(*this, static_cast<u64>(0), static_cast<u64>(size));
    }

    inline operator view() const {
        return view(*this, static_cast<u64>(0), m_byte_size);
    }

    static constexpr u64 ALIGNMENT = 0; // TODO should probably be a conservative aligment

private:
    u8 *m_data;
    u64 m_byte_size;
    allocator* m_alloc;

    inline auto clear() -> void {
        m_data = nullptr;
        m_byte_size = 0;
        m_alloc = nullptr;
    }
};
} // namespace root