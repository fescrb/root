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
 * @file Allocator.h
 * @brief Implements Allocator class, a standard allocator.
 */

#ifndef ROOT_ALLOCATOR_H
#define ROOT_ALLOCATOR_H

#include "BasicTypes.h"

namespace root {
	
	/**
	 * @class Allocator 
	 * 
	 * Provides a standard allocator which makes use of the standard 
	 * library's dynamic memory allocation routines, while adding extra 
	 * features: aligned memory allocation, making sure reallocated 
	 * memory is copied and the ability to log memory usage.
	 * Memory allocated by an Allocator must be freed by an instance of the
	 * same class. The allocator cannot manipulate memory allocated by any 
	 * other allocator class or library.
	 */
	
	class Allocator {
		
		public:
			/**
			 * Allocate memory without alignment.
			 * @param size The amount of bytes to allocate.
			 * @return A pointer to the start of the allocated memory.
			 */
			virtual void 	*allocate(const size_t size);
			
			/**
			 * Allocate memory with the given alignment.
			 * @param size The amount of bytes to allocate.
			 * @param alignment The alignment of the memory in bytes.
			 * @return A pointer to the start of the allocated memory.
			 */
			virtual void	*allocateAligned(const size_t size, const U8 alignment);
			
			/**
			 * Reallocates a block of memory, copying as much of the 
			 * data as possible (ie. if new block of memory is bigger,
			 * all data is copied. If it's smaller, it will only copy to
			 * the end of the array. If it's the same, why are you
			 * reallocating?).
			 * Please note that only full blocks of memory, as allocated
			 * by the class, can be reallocated successfully.
			 * @param object A pointer to the start of the memory object
			 * as given by an instance of Allocator.
			 * @param newSize The new size to be allocated in bytes.
			 * @return A pointer to the start of the reallocated memory.
			 */
			virtual void	*reallocate(const void *object, const size_t newSize);
			
			/**
			 * Frees a block of memory. 
			 * Please note that only full blocks of memory, as allocated
			 * by the class, can be freed successfully.
			 * @param object A pointer to the start of the memory object
			 * as given by an instance of Allocator.
			 */
			virtual void	 free(const void *object);
			
			/**
			 * Call the destructor of a class and free it memory.
			 * Please note that only full blocks of memory, as allocated
			 * by the class, can be freed successfully. And only by
			 * the same instance (in the case of a memory pool allocator)
			 * or the same class (if you use this class) as it was
			 * allocated with.
			 * @param object A pointer to the start of the memory object
			 * as given by an instance of Allocator.
			 */
			template <class Class>
			void	 		 free(const Class *object) {
				object->~Class();
				free((void*)object);
			}
		
	};
	
}

#endif //ROOT_ALLOCATOR_H
