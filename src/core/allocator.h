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
 * @file allocator.h
 * @brief Implements Allocator class, a standard allocator.
 */

#ifndef ROOT_ALLOCATOR_H_
#define ROOT_ALLOCATOR_H_

#include "root/core/basic_types.h"

namespace root {

    /**
     * @class allocator 
     * 
     * Provides a standard allocator which makes use of the standard 
     * library's dynamic memory allocation routines, while adding extra 
     * features: aligned memory allocation, making sure reallocated 
     * memory is copied and the ability to log memory usage.
     * Memory allocated by an Allocator must be freed by an instance of the
     * same class. The allocator cannot manipulate memory allocated by any 
     * other allocator class or library.
     */

    class allocator 
    {
        public:
            /**
             * Allocate memory without alignment.
             * @param num_bytes The amount of bytes to allocate.
             * @return A pointer to the start of the allocated memory.
             */
            virtual void        *malloc(const size_t &num_bytes) = 0;
            
            /**
             * Allocates a block of memory initializing that memory to zeroes.
             * @param num_bytes The amount of bytes to allocate.
             * @return A pointer to the start of the allocated memory.
             */
            virtual void        *calloc(const size_t &num_bytes) = 0;
            
            /**
             * Reallocates a block of memory, copying as much of the 
             * data as possible (ie. if new block of memory is bigger,
             * all data is copied. If it's smaller, it will only copy to
             * the end of the array. If it's the same, why are you
             * reallocating?).
             * Please note that only full blocks of memory, as allocated
             * by the class, can be reallocated successfully.
             * @param from A pointer to the start of the memory object
             * as given by the instance of Allocator.
             * @param new_num_bytes The new size to be allocated in bytes.
             * @return A pointer to the start of the reallocated memory.
             */
            virtual void        *realloc(void *from, 
                                             const size_t new_num_bytes) = 0;
            
            /**
             * Frees a block of memory. 
             * Please note that only full blocks of memory, as allocated
             * by the class, can be freed successfully.
             * @param object A pointer to the start of the memory object
             * as given by the instance of Allocator.
             */
            virtual void         free(void *object) = 0;
            
            static allocator    *get_default_allocator();
            
        private:
            static allocator    *m_p_default_allocator = NULL;
    };
    
    class os_allocator 
    {
        public:
                                 os_allocator() {}
            
            void                *malloc(const size_t &num_bytes);
            
            void                *calloc(const size_t &num_bytes);
            
            void                *realloc(void *from, 
                                         const size_t &new_num_bytes);
            void                 free(void *object);
    };
}

#endif //ROOT_ALLOCATOR_H_
