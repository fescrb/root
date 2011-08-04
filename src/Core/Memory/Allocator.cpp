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
 * @file Allocator.cpp
 * @brief Implements Allocator's methods. Plus helper structs and 
 * functions.
 */

#include "Allocator.h"

#include <cstdlib> // Used for malloc and free routines.
#include <cstring> // Used for memcpy.

using namespace root;


namespace root {
	/**
	 * @struct MemoryHeader 
	 * 
	 * Provides standard information about a block of 
	 * memory, including size, alignment and the original miss alignment 
	 * when allocated.
	 */
	typedef struct {
		//! The alignment required for a block of memory.
		U8		m_alignment;
		//! The missalignment correction performed on a block of memory. 
		U8		m_missAlignment;
		//! The size of a block of memory.
		size_t		m_size;
	} MemoryHeader;
}

/**
 * @param data The address of the start of the block of data as used
 * by the program.
 * @return The position where the MemoryHeader is located.
 */
inline MemoryHeader* getMemoryHeaderPosition(const I8 *data){
	I8* temp = (I8*) data;
	temp -= sizeof(MemoryHeader); 
	return (MemoryHeader*) temp;
}

/**
 * An alias for the free method, since it cannot be used within the Allocator class.
 * 
 * @param pointer A pointer to the memory to be deallocated.
 */
inline void	 		 deallocate(void* pointer) {
	free(pointer);
}

void* Allocator::allocate(const size_t size) {
	/*
	 * Uses alocateAligned to allocate the memory, this causes a small
	 * overhead due to having to store a MemoryHeader object, but allows
	 * reallocate and free to be standarized.
	 */
	allocateAligned(size, 1);
}

void* Allocator::allocateAligned(const size_t size, const U8 alignment) {
	
	// Allocate memory with extra space for MemoryHeader and the alignment.
	I8 *data = (I8*) malloc(size + (alignment-1) + sizeof(MemoryHeader));
	
	// Leave spac for the Memory Header.
	data+=sizeof(MemoryHeader);
	// Work out missalignment.
	U8 missAlignment = *data % alignment;
	// Align memory block.
	data+=missAlignment;
	
	// Find out where we will put the MemoryHeader.
	MemoryHeader *memHeaderPosition = getMemoryHeaderPosition(data);
	
	// Create ad MemoryHeader and include the book-keeping info.
	MemoryHeader memHeader;
	memHeader.m_size = size;
	memHeader.m_alignment = alignment;
	memHeader.m_missAlignment = missAlignment;
	
	// Store the MemoryHeader.
	memHeaderPosition[0] = memHeader;
	
	return (void*)data;
}

void* Allocator::reallocate(const void *object, const size_t newSize) {
	// Get a non-const byte pointer.
	I8 *data = (I8*) object;
	
	// Retrieve the MemoryHeader info.
	MemoryHeader memHeader = getMemoryHeaderPosition(data)[0];
	
	// Allocate memory for the new data.
	void *newData = allocateAligned(newSize, memHeader.m_alignment);
	
	// Work out how many bytes we can copy.
	U32 bytesToCopy = newSize > memHeader.m_size ? 
									memHeader.m_size :
									newSize;
	
	// Copy the memory across.
	memcpy(newData, object, bytesToCopy);
	
	// Free the old memory array-
	this->free(object);
	
	return newData;
}

void Allocator::free(const void *object) {
	// Get a non-const byte pointer.
	I8* data = (I8*) object;
	
	// Retrieve the MemoryHeader info.
	MemoryHeader memHeader = getMemoryHeaderPosition(data)[0];
	
	// Find the real start of the memory block.
	data -= (sizeof(MemoryHeader) + memHeader.m_missAlignment);
	
	// Free memory block.
	deallocate(data);
}