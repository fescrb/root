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
 * @file Hash.h
 * @brief Declares a few hashing algorithms.
 * 
 * Provides the declaration of BSD Checksum and CRC32.
 */

#ifndef _ROOT_HASH_UTILITIES_H
#define _ROOT_HASH_UTILITIES_H

#include "BasicTypes.h"

#define CRC_32_IEEE_802_3_POLYNOMIAL 0x04C11DB7

namespace root {
	/**
	 * Function to calculate the CRC32 checksum of the given array. The checksum
     * is calculated byte by byte. 
	 * @param array The array of bytes to checksum.
	 * @param arraySize The number of bytes in the array.
	 * @param polynomialKey The 32-bit polynomial by which to divide the array. NOTE:
	 * To calculate a 32-bit CRC a 33-bit polynomial is needed, and both the most significant
	 * bit and least significant bit must be one. So the 33rd bit is assumed to be 1 in this case.
	 * @return The 32-bit CRC checksum of the array.
	 */
	U32		 crc32(const U8* array, U32 arraySize, U32 polynomialKey);
    
}

#endif //_ROOT_HASH_UTILITIES_H