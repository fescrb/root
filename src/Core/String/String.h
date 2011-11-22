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

#ifndef _ROOT_STRING_H
#define _ROOT_STRING_H

#include "ReferenceCountedMutableString.h"

namespace root{
	
	class String {
		public:
		
								 String(Allocator* allocator = DefaultAllocator::getStandardAllocator() );
								 String(const I8* string,
										const I32 arraySize = -1,
										Allocator* allocator = DefaultAllocator::getStandardAllocator() );
			explicit 	 		 String(const MutableString* string,
										Allocator* allocator = DefaultAllocator::getStandardAllocator() );
			explicit 			 String(const String* string,
										Allocator* allocator = DefaultAllocator::getStandardAllocator() );
			
			inline bool	 		 isEmpty() const {
				return m_pPrivateString->isEmpty();
			}
			
			inline const I8		*getCString() const {
				return m_pPrivateString->getCString();
			}
			
			inline const U32	 getSize() const {
				return m_pPrivateString->getSize();
			}
			
			inline String 		*getSubtring(U32 start, 
											 U32 end, 
											 Allocator *stringDataAllocator = NULL,
											 Allocator *instanceAllocator = DefaultAllocator::getStandardAllocator()) {
				return new (instanceAllocator) String(m_pPrivateString->getSubtring(start, end,stringDataAllocator,instanceAllocator));
			}
			
			/* ***********
			 * Operators *
			 *************/
			
			inline void 		*operator new(size_t sizeInBytes,
											  Allocator* allocator){
				return allocator->allocate(sizeInBytes);
			}
			
			/* *********************
			 * Interning functions *
			 ***********************/
			
			inline bool 		 isInterned() const {
				
			}
			
			inline bool 		 intern() { 
				
			}
			
		
		private:
		
			
			
			ReferenceCountedMutableString* m_pPrivateString;
		
	};
	
}//namespace root

#endif //_ROOT_STRING_H
