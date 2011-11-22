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
 * @file MutableString.cpp
 * @brief Implements MutableString.
 * 
 * Provides the implementation of the class methods declared in
 * MutableString.h but which are not inline (or templated).
 */

#include "MutableString.h"

#include "Math.h"
#include "String.h"

using namespace root;

MutableString::MutableString(Allocator* allocator)
:	DynamicArray<I8>(0,allocator),
	m_hasBeenInterned(false),
	m_internID(0) {
}

MutableString::MutableString(const I8* data, 
							 const I32 arraySize, 
							 Allocator* allocator)
:	DynamicArray<I8>(data,arraySize < 0? strlen(data):arraySize,0,allocator),
	m_hasBeenInterned(false),
	m_internID(0) {
}

MutableString::MutableString(const MutableString* string, 
							 Allocator* allocator)
:	DynamicArray<I8>(string,0,allocator),
	m_hasBeenInterned(false),
	m_internID(0){
}

MutableString::MutableString(const String* string, 
							 Allocator* allocator)
:	DynamicArray<I8>(string->getCString(),string->getSize(),0,allocator),
	m_hasBeenInterned(false),
	m_internID(0){
}

void MutableString::replaceOcurrences(const MutableString* occurenceString,
									  const MutableString* replacingString) {
	iterator it = start();
	// While there are occurrences of the string in this string.
	while(it.find(occurenceString->getCString(),occurenceString->getSize())) {
		// We replace the occurrence.
		swap(it,it+occurenceString->getSize()-1,replacingString);
		// We skip the string we just replaced just in case it contains an occurrence.
		it+=replacingString->getSize();
	}
}

bool MutableString::operator<(const MutableString& rightHandSide){
	// Get the shortest length.
	U32 shortestLength = minimum<U32>(getSize(),rightHandSide.getSize());
	
	// Get iterators for both arrays.
	iterator ownIterator = start();
	iterator otherIterator = rightHandSide.start();
	
	// Iterate over both arrays at the same time.
	for(ownIterator; ownIterator < shortestLength; ++ownIterator, ++otherIterator) {
		// If this item is smaller. Return true.
		if(ownIterator.element() < otherIterator.element())
			return true;
		// If this item is bigger. Return false.
		if(ownIterator.element() > otherIterator.element())
			return false;
	}
	// All items so far were equal, so shortest is smaller.
	if(getSize() < rightHandSide.getSize())
		return true;
	return false;
}
			
bool MutableString::operator>(const MutableString& rightHandSide){
	// Get the shortest length.
	U32 shortestLength = minimum<U32>(getSize(),rightHandSide.getSize());
	
	// Get iterators for both arrays.
	iterator ownIterator = start();
	iterator otherIterator = rightHandSide.start();
	
	// Iterate over both arrays at the same time.
	for(ownIterator; ownIterator < shortestLength; ++ownIterator, ++otherIterator) {
		// If this item is bigger. Return true.
		if(ownIterator.element() > otherIterator.element())
			return true;
		// If this item is smaller. Return false.
		if(ownIterator.element() < otherIterator.element())
			return false;
	}
	// All items so far were equal, so shortest is smaller.
	// If they are of equal lenght, they are equal.
	if(getSize() <= rightHandSide.getSize())
		return false;
	return true;
}
			
bool MutableString:: operator==(const MutableString& rightHandSide){
	if(getSize() != rightHandSide.getSize())
		return false;
	
	// Get iterators for both arrays.
	iterator ownIterator = start();
	iterator otherIterator = rightHandSide.start();
	
	// Iterate over both arrays at the same time.
	for(ownIterator; ownIterator < getSize(); ++ownIterator, ++otherIterator) {
		// If this item is different. Return False.
		if(ownIterator.element() != otherIterator.element())
			return true;
	}
	// All items so far were equal, both arrays are equal.
	return true;
}
			
bool MutableString::operator<=(const MutableString& rightHandSide){
	// Get the shortest length.
	U32 shortestLength = minimum<U32>(getSize(),rightHandSide.getSize());
	
	// Get iterators for both arrays.
	iterator ownIterator = start();
	iterator otherIterator = rightHandSide.start();
	
	// Iterate over both arrays at the same time.
	for(ownIterator; ownIterator < shortestLength; ++ownIterator, ++otherIterator) {
		// If this item is smaller. Return true.
		if(ownIterator.element() < otherIterator.element())
			return true;
		// If this item is bigger. Return false.
		if(ownIterator.element() > otherIterator.element())
			return false;
	}
	// All items so far were equal, so if this is shorter,
	// or they are of equal length, we return true.
	if(getSize() <= rightHandSide.getSize())
		return true;
	return false;
}
			
bool MutableString::operator>=(const MutableString& rightHandSide){
	// Get the shortest length.
	U32 shortestLength = minimum<U32>(getSize(),rightHandSide.getSize());
	
	// Get iterators for both arrays.
	iterator ownIterator = start();
	iterator otherIterator = rightHandSide.start();
	
	// Iterate over both arrays at the same time.
	for(ownIterator; ownIterator < shortestLength; ++ownIterator, ++otherIterator) {
		// If this item is bigger. Return true.
		if(ownIterator.element() > otherIterator.element())
			return true;
		// If this item is smaller. Return false.
		if(ownIterator.element() < otherIterator.element())
			return false;
	}
	// All items so far were equal, so shortest is smaller.
	if(getSize() < rightHandSide.getSize())
		return false;
	return true;
}
