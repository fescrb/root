/*
 * Copyright (C) 2011  Fernando Escribano Macias
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

/**
 * @file allocator.cpp
 * @brief Implements os_allocator's methods. 
 */

#include "root/core/allocator.h"

#include <cstdlib> // Used for malloc and free routines.

using namespace root;

allocator* _global_alocator = NULL;

namespace root 
{
    /*
     * allocator static functions
     */
    allocator* allocator::get_default_allocator()
    {
        if(!_global_alocator)
            _global_alocator = new os_allocator();
        return _global_alocator;
    }
    
    /*
     * 
     */
    void* os_allocator::malloc(const size_t& num_bytes)
    {
        return std::malloc(num_bytes);
    }
    
    void* os_allocator::calloc(const size_t& num_bytes)
    {
        return std::calloc(num_bytes);
    }
    
    void* os_allocator::realloc(void* from, const size_t& new_num_bytes)
    {
        return std::realloc(from, new_num_bytes);
    }
    
    void os_allocator::free(void* object)
    {
        std::free(object);
    }
} //namespace root