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
 * @file DefaultAllocator.h
 * @brief Implements the DefaultAllocator class.
 * 
 * Provides an implementation of the DefaultAllocator class, a class which
 * contains the global Allocator instance.
 */

#ifndef _ROOT_DEFAULT_ALLOCATOR_H
#define _ROOT_DEFAULT_ALLOCATOR_H

#include "Allocator.h"

namespace root {
	/**
	 * @class DefaultAllocator
	 * 
	 * The sole purpose of this class is to contain a pointer a global
	 * Allocator instance, to be used by any class to dynamically
	 * allocate memory using the system's malloc/free.
	 * 
	 * This class was created to prevent the need to dynamically allocate
	 * space for a standard Allocator for every object, instead keeping
	 * a global instance to be used by every class.
	 */
	class DefaultAllocator {
		public:
			/**
			 * Return the global standard Allocator instance. 
			 * 
			 * It will initialise the instance if it wasn't previously done.
			 * @return The global Allocator instance.
			 */
			static inline Allocator				*getStandardAllocator() {
				if(!m_pStandardAllocatorInstance)
					m_pStandardAllocatorInstance = new Allocator;
				return m_pStandardAllocatorInstance;
			}
			
		private:
			/**
			 * The global Allocator instance, declared here and implemented in
			 * DefaultAllocator.cpp.
			 */
			static Allocator		 			*m_pStandardAllocatorInstance;
	};
	
}//namespace root


#endif //_ROOT_DEFAULT_ALLOCATOR_H
