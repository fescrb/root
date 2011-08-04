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
 * @file ReferenceCountedMutableString.h
 * @brief Declares a reference counted string class.
 * 
 * Provides the declaration of ReferenceCountedMutableString.
 * ReferenceCountedMutableString is a subclass of MutableString with
 * added reference counting capabilities.
 */

#ifndef _ROOT_REFERENCE_COUNTED_MUTABLE_STRING_H
#define _ROOT_REFERENCE_COUNTED_MUTABLE_STRING_H

#include "MutableString.h"

namespace root {
	
	/**
	 * @class ReferenceCountedMutableString
	 * 
	 * Subclass of MutableString. It behaves exactly like its 
	 * parent class, but with added reference counting capabilities.
	 * It provides the methods hold and release, to allow its 
	 * (ideally multiple) owners to increment and decrement the reference
	 * count.
	 * The owner that decrements the reference count to 0 is tasked with
	 * deleting the instance.
	 */
	class ReferenceCountedMutableString :
		public MutableString {
			
		public:
			/**
			 * Empty constructor.
			 * Will create an empty string. 
			 * @param allocator The allocator with which to allocate string data.
			 * Default is the default Allocator. (As provided by DefaultAllocator. 
			 */
						 ReferenceCountedMutableString(Allocator* allocator = DefaultAllocator::getStandardAllocator() );
			
			/**
			 * Class constructor.
			 * Will copy the data from the provided C-style string.
			 * @param data Pointer to the C-style string to copy data from.
			 * @param arraySize Size of the C-style string. Or the amount of data
			 * you want to copy.
			 * @param allocator The allocator with which to allocate string data.
			 * Default is the default Allocator. (As provided by DefaultAllocator. 
			 */
			explicit	 ReferenceCountedMutableString(const I8* data, 
													   const I32 arraySize = -1,
													   Allocator* allocator = DefaultAllocator::getStandardAllocator() );
			explicit	 ReferenceCountedMutableString(const MutableString* string, 
													   Allocator* allocator = DefaultAllocator::getStandardAllocator() );
			explicit	 ReferenceCountedMutableString(const String* string, 
													   Allocator* allocator = DefaultAllocator::getStandardAllocator() );
			
			/**
			 * Increment the reference count.
			 */
			inline void	 hold() {
				m_referenceCount++;
			}
			
			/**
			 * Decrement the reference count.
			 */
			inline void	 release() {
				m_referenceCount--;
			}
			
			/**
			 * Return the value of the reference count.
			 */
			inline U16	 referenceCount() {
				return m_referenceCount;
			}
			
		private:
			U16			 m_referenceCount;
	};
	
}//namespace root

#endif //_ROOT_REFERENCE_COUNTED_MUTABLE_STRING_H
