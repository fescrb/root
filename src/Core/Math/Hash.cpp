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
 * @file Hash.cpp
 * @brief Implements the hashing routines delared in Hash.h
 * 
 * Provides the implementation of a few Hashing algorithms,
 * for example CRC32 and BSD Checksum.
 */

#include "Hash.h"

#include "Math.h" // For basic math functions such as getBitAt and setBitAt

using namespace root;

U32 root::crc32(const U8* array, U32 arraySize, U32 polynomialKey) {
	// Make sure the LSB is 1. The MSB is assumed to be 1.
	U32 divisor = polynomialKey | 1;
    U32 dividend = 0;
	
	if(arraySize > U32_SIZE){
		dividend = *(U32*)array;
	}
	
	for(U32 byteIndex = U32_SIZE; byteIndex < arraySize; ++byteIndex) {
		U8 thisByte = array[byteIndex];
		
		for(U8 bitIndex = 0; bitIndex < U8_SIZE; ++bitIndex) {
			bool oneAtEnd = getBitAt<U32>(dividend,31);
			
			dividend = (dividend << 1) | (getBitAt<U8>(thisByte,U8_SIZE - (bitIndex + 1) ) ? 1 : 0 );
			
			if(oneAtEnd){
				dividend ^= divisor;
			}
		}
	}
	
    return dividend;
}