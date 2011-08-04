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

#ifndef _ROOT_SEARCH_H
#define _ROOT_SEARCH_H

#include "BasicTypes.h"

namespace root {
	
	template <class Type>
	struct LessOperator {
		inline bool		operator()(const Type& leftHandSide, const Type& rightHandSide) {
			return leftHandSide < rightHandSide;
		}
	};
	
	template <class Type>
	struct EqualityOperator {
		inline bool		operator()(const Type& leftHandSide, const Type& rightHandSide) {
			return leftHandSide == rightHandSide;
		}
	};
	
	template <class Type, 
			  class PrecedenceComparison /*= LessOperator<Type>*/, 
			  class EqualityComparison /*= EqualityOperator<Type>*/ >
	bool			 dictionarySearch( const Type& elementToFind, const Type* array, const U32 arraySize, U32& index) {
		U32 high = arraySize;
		U32 low = 0;
		
		PrecedenceComparison less;
		EqualityComparison equals;
		
		index = 0 ;
		
		while( ( less(array[low],elementToFind)   || equals(array[low],elementToFind) ) &&
			   ( !less(array[high],elementToFind) || equals(array[high],elementToFind) ) ) {
			index = (high - low)/ 2;
			
			// If we have found what we were looking for.
			if( equals(array[index],elementToFind) ) {
				// Go to the first occurrence.
				while( index > 0 && equals(array[index-1],elementToFind) ) {
					--index;
				}
				// Once we have the first occurrence, we're done!
				return true;
				
			// If we're below what we intend to find.
			} else if ( less(array[index],elementToFind)) {
				low = index+1; 
				
			// If we're above what we intend to find.
			} else {
				high = index-1;
			}
		}
		
		return false;
	}
	
	
}//namespace root

#endif //_ROOT_SEARCH_H