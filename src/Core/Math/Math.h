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
 * @file Math.h
 * @brief Provides a small set of basic mathematical functions.
 * 
 * Declares and implements a few basic mathematical functions.
 * Such as: minimum, squareRoot, etc.
 */

#ifndef _ROOT_MATH_UTILITIES_H
#define _ROOT_MATH_UTILITIES_H

namespace root {
	
	/**
	 * Returns a reference to the given parameter with the lowest value.
	 * Comparison is done with the less-than operator.
	 * @return The value of the argument with the lowest value.
	 */
	template <class Type>
	Type 		 minimum(const Type& leftHandSide, const Type& rightHandSide) {
		return leftHandSide < rightHandSide ?
				   leftHandSide :
				   rightHandSide;
	}

	/**
	 * Get the value of the bit at the given position.
	 * Since the position is given as an unsigned 8-bit
	 * integer, the maximum bit position is 255.
	 * 
	 * @param num The data.
	 * @param bitPosition The position of the bit.
	 * @return True iff the bit is set. False iff unset.
	 */
	template <class Type>
	inline bool  getBitAt(const Type& num, const U8 bitPosition) {
		return num & ( 1 << bitPosition);
	}
	
	/**
	 * Set the bit at the given position.
	 * Since the position is given as an unsigned 8-bit
	 * integer, the maximum bit position is 255.
	 * 
	 * @param num The data.
	 * @param bitPosition The position of the bit.
	 * @return A reference to the resulting data.
	 */
	template <class Type>
	inline Type&  setBitAt(const Type& num, const U8 bitPosition){
		return num | ( 1 << bitPosition);
	}
	
	/**
	 * Unset the bit at the given position.
	 * Since the position is given as an unsigned 8-bit
	 * integer, the maximum bit position is 255.
	 * 
	 * @param num The data.
	 * @param bitPosition The position of the bit.
	 * @return A reference to the resulting data.
	 */
	template <class Type>
	inline Type&  unsetBitAt(const Type& num, const U8 bitPosition){
		return num & !( 1 << bitPosition);
	}
	
}

#endif