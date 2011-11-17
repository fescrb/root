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
 * @file MutableString.h
 * @brief Provides the declaration of the MutableString class.
 * 
 * Provides the declaration if the MutableString class.
 */

#ifndef _ROOT_MUTABLE_STRING_H
#define _ROOT_MUTABLE_STRING_H

#include "DynamicArray.h"
#include "StringID.h"

namespace root {
	
	class String;
	
	/**
	 * @class MutableString
	 * 
	 * MutableString provides a complete String class, it is 
	 * a subclass of DynamicArray, and allows all array
	 * manipulation methods provided by that class, along with
	 * other more String-related methods.
	 * 
	 * Unlike the String class, this class is mutable, so changing its
	 * contents with its methods or any provided by DynamicArray will not
	 * create another String instance, but assingment will copy the entire
	 * String, and there is no reference counting.
	 */
	class MutableString : 
		public DynamicArray<I8> {
		public:
			/**
			 * Class constructor.
			 * Creates an empty string, only assigning the desired allocator.
			 * @param allocator The allocator with which to allocate memory for string data.
			 */
								 MutableString(Allocator* allocator = DefaultAllocator::getStandardAllocator() );
			
			/**
			 * Class constructor.
			 * Gives the initial string data as a C-style string.
			 * Will copy the data.
			 * @param data The string data.
			 * @param arraySize The size of the given array. Or 
			 * the amount of data you want copied. Default is -1. If
			 * a value less than 0 is given. The constructor will 
			 * use strlen to figure out the size.
			 * @param allocator The allocator with which to allocate memory for string data.ata.
			 */
			explicit			 MutableString(const I8* data, 
											   const I32 arraySize = -1,
											   Allocator* allocator = DefaultAllocator::getStandardAllocator() );
			
			/**
			 * Class constructor.
			 * Copies the data from the given MutableString.
			 * @param string The MutableString from which to copy the data.
			 * @param allocator The allocator with which to allocate memory for string data.
			 */
			explicit			 MutableString(const MutableString* string, 
											   Allocator* allocator = DefaultAllocator::getStandardAllocator() );
			
			/**
			 * Class constructor.
			 * Copies the data from the given String.
			 * @param string The String from which to copy the data.
			 * @param allocator The allocator with which to allocate memory for string data.
			 */
			explicit			 MutableString(const String* string, 
											   Allocator* allocator = DefaultAllocator::getStandardAllocator() );
			
			/**
			 * Get a pointer to the C-style string. Alias
			 * for getCArray.
			 * @return A pointer to the first character of
			 * the C string.
			 */
			const I8   			*getCString() const {
				return getCArray();
			}
			
			/**
			 * Get a substring of this string. The substring
			 * is the string between indices start and end
			 * including both. 
			 * @param start The first character of the substring.
			 * @param end The last character of the substring.
			 * @param stringDataAllocator The allocator used
			 * to allocate string data (NOT the string istance).
			 * Default value is NULL. If null is used, it will used
			 * the same allocator as this string.
			 * @param instanceAllocator The allocator used to 
			 * allocate space for the string instance itself (NOT
			 * the character array). The default is the default
			 * allocator instance.
			 */
			inline MutableString *getSubtring(U32 start, 
											  U32 end, 
											  Allocator *stringDataAllocator = NULL,
											  Allocator *instanceAllocator = DefaultAllocator::getStandardAllocator()) const {
				return new (instanceAllocator) MutableString(&getCString()[start],
															 (end-start)+1,
															 stringDataAllocator?stringDataAllocator:m_pAllocator);
			}
			
			/**
			 * Replace all occurrences of the given string inside this string by
			 * another string.
			 * Unless both strings are the same size, there is a risk of 
			 * dynamic memory reallocation.
			 * @param occurenceString The string we want to replace.
			 * @param replacingString The string it will be replaced by.
			 */
			void 				 replaceOcurrences(const MutableString* occurenceString,
												   const MutableString* replacingString);
			
			inline bool 		 isInterned() {
				return m_hasBeenInterned;
			}
			
			inline bool 		 intern() {
				
			}
			
			/**
			 * Less-than operator.
			 * NOTE: May have to search the whole string for differences.
			 * @param rightHandSide The string to compare this to.
			 * @return True if this string is lexicographically less than
			 * the given one.
			 */
			bool				 operator<(const MutableString& rightHandSide);
			
			/**
			 * Bigger-than operator.
			 * NOTE: May have to search the whole string for differences.
			 * @param rightHandSide The string to compare this to.
			 * @return True if this string is lexicographically biggen than
			 * the given one.
			 */
			bool 				 operator>(const MutableString& rightHandSide);
			
			/**
			 * Equality operator.
			 * NOTE: May have to search the whole string for differences.
			 * @param rightHandSide The string to compare this to.
			 * @return True if this string is equal to the given one.
			 */
			bool 				 operator==(const MutableString& rightHandSide);
			
			/**
			 * Inequality operator.
			 * NOTE: May have to search the whole string for differences.
			 * @param rightHandSide The string to compare this to.
			 * @return True if this string is different to the given one.
			 */
			bool 				 operator!=(const MutableString& rightHandSide) {
				return ! this->operator==(rightHandSide);
			}
			
			/**
			 * Less-than-or-equals operator.
			 * NOTE: May have to search the whole string for differences.
			 * @param rightHandSide The string to compare this to.
			 * @return True if this string is lexicographically less or equal
			 * to the given one.
			 */
			bool				 operator<=(const MutableString& rightHandSide);
			
			/**
			 * Bigger-than-or-equals operator.
			 * NOTE: May have to search the whole string for differences.
			 * @param rightHandSide The string to compare this to.
			 * @return True if this string is lexicographically bigger or equal
			 * to the given one.
			 */
			bool 				 operator>=(const MutableString& rightHandSide);
			
		private:
			
			bool				 m_hasBeenInterned;
			StringID			 m_internID;
	}; 
	
}//namespace root

#endif //_ROOT_MUTABLE_STRING_H
