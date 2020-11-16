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

#include <malloc.h>

#include <root/memory/system_allocator.h>

namespace root {
system_allocator system_allocator::universal_instance = system_allocator();

auto system_allocator::malloc(const u64& byte_size, const u64& alignment) -> void* {
#if defined(ROOT_WIN)
    return _aligned_malloc(byte_size, alignment);
#else
    return memalign(alignment, byte_size);
#endif
}

auto system_allocator::free(void* mem) -> void {
#if defined(ROOT_WIN)
    return _aligned_free(mem);
#else
    return ::free(mem);
#endif
}
} // namespace root