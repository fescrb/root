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

#include <atomic>

#include <root/memory/allocator.h>

namespace root {
class reference_counter final {
public:
    /**
     * @return true iff we decremented the last strong refernce.
     */
    inline auto decrement_strong() -> bool {
        return --m_strong_references == 0;
    }

    /**
     * @return true iff successful.
     */
    inline auto try_increment_strong() -> bool {
        return m_strong_references.load() > 0 && ++m_strong_references;
    }

    /**
     * @return true iff successful
     */
    inline auto try_increment_weak() -> bool {
        return m_strong_references.load() > 0 && ++m_weak_references;
    }

    /**
     * @return true iff there are no more weak references.
     */
    inline auto decrement_weak() -> bool {
        return --m_weak_references == 0;
    }

    inline auto strong_refs() -> uint32_t {
        return m_strong_references.load();
    }

    inline auto weak_refs() -> uint32_t {
        return m_weak_references.load();
    }

    /**
     * @return true 
     */
    inline auto abandoned() -> bool {
        return (m_weak_references.load() == 0) && (m_strong_references.load() == 0);
    }

    inline auto can_release() -> bool {
        return --m_release_lock == 0;
    }

private:
    std::atomic<uint32_t>     m_strong_references{1};
    std::atomic<uint32_t>     m_weak_references{0};
    std::atomic<uint32_t>     m_release_lock{1};
};
} // namespace root