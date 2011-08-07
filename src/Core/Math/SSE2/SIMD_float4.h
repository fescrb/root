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

#ifndef _ROOT_SIMD_FLOAT4_H
#define _ROOT_SIMD_FLOAT4_H

#include "BasicTypes.h"
#include <cmath>
#include <cstdlib>

#include <xmmintrin.h>

namespace root {
	
	// Stored a0 = x, a1 = y, a2 = z, a3 = w
	typedef __m128 simd_float4;

	inline simd_float4  simd_float4_zeros(){
		return _mm_setzero_ps();
	}
	
	inline simd_float4  simd_float4_replicate(const F32 value){
		return _mm_set1_ps(value);
	}
	
	inline simd_float4  simd_float4_fromValues(const F32 x, const F32 y, const F32 z, const F32 w) {
		return _mm_setr_ps(x,y,z,w);
	}
	
	inline simd_float4  simd_float4_copy(const simd_float4& other) {
		return simd_float4(other);
	}
	
	inline simd_float4  simd_replicateX(const simd_float4& vector){
		return _mm_shuffle_ps( vector, vector, _MM_SHUFFLE(0,0,0,0));
	}
	
	inline simd_float4  simd_replicateY(const simd_float4& vector){
		return _mm_shuffle_ps( vector, vector, _MM_SHUFFLE(1,1,1,1));
	}
	
	inline simd_float4  simd_replicateZ(const simd_float4& vector){
		return _mm_shuffle_ps( vector, vector, _MM_SHUFFLE(2,2,2,2));;
	}
	
	inline simd_float4  simd_replicateW(const simd_float4& vector){
		return _mm_shuffle_ps( vector, vector, _MM_SHUFFLE(3,3,3,3));
	}
	
	inline void 	 	simd_copyToArray(const simd_float4& vector ,F32 *array) {
		_mm_store_ps(array, vector);
	}
	
	inline simd_float4 	 simd_add(const simd_float4 &lhs, const simd_float4 &rhs){
		return _mm_add_ps(lhs,rhs);
	}

	inline simd_float4   simd_sub(const simd_float4 &lhs, const simd_float4 &rhs){
		return _mm_sub_ps(lhs,rhs);
	}

	inline simd_float4   simd_mul(const simd_float4 &lhs, const simd_float4 &rhs){
		return _mm_mul_ps(lhs,rhs);
	}
	
	inline simd_float4   simd_mul(const simd_float4 &lhs, const F32 &rhs){
		simd_float4 rightHandSide = simd_float4_replicate(rhs);
		return simd_mul(lhs, rightHandSide);
	}

	inline simd_float4   simd_div(const simd_float4 &lhs, const simd_float4 &rhs){
		return _mm_div_ps(lhs,rhs);
	}

	inline simd_float4   simd_div(const simd_float4 &lhs, const F32 &rhs){
		simd_float4 rightHandSide = simd_float4_replicate(rhs);
		return simd_div(lhs,rightHandSide);
	}
	
	inline bool 	 	 simd_equals(const simd_float4 &lhs, const simd_float4 &rhs){
		simd_float4 equals = _mm_cmpeq_ps(lhs , rhs );
		F32 array[4];
		simd_copyToArray(equals,array);
		return ((array[0] != 0 && array[1] != 0) && array[2] != 0) && array[3] != 0;
	}

	inline F32 			 simd_sum(const simd_float4 &vector){
		F32 sumResult = 0;
		simd_float4 y = simd_replicateY(vector);
		simd_float4 z = simd_replicateZ(vector);
		simd_float4 w = simd_replicateW(vector);
		simd_float4 result = simd_add( simd_add( simd_add(vector, z ) , y ) ,w);
		_mm_store_ss(&sumResult, result);
		return sumResult;
	}
	
	inline simd_float4 	 simd_sum_vector(const simd_float4 &vector){
		simd_float4 x = simd_replicateX(vector);
		simd_float4 y = simd_replicateY(vector);
		simd_float4 z = simd_replicateZ(vector);
		simd_float4 w = simd_replicateW(vector);
		return simd_add( simd_add( simd_add(x, z ) , y ) ,w);
	}
	
	inline simd_float4 	 simd_sqrt_vector(const simd_float4 &vector){
		return _mm_sqrt_ps(vector);
	}

	inline F32 			 simd_dot(const simd_float4 &lhs, const simd_float4 &rhs){
		return simd_sum(simd_mul(lhs,rhs));
	}
	
	inline simd_float4	 simd_dot_vector(const simd_float4 &lhs, const simd_float4 &rhs){
		return simd_sum_vector(simd_mul(lhs,rhs));
	}

	inline F32			 simd_mag(const simd_float4 &vector){
		return sqrt(simd_dot(vector,vector));
	}
	
	inline simd_float4	 simd_mag_vector(const simd_float4 &vector){
		return simd_sqrt_vector(simd_dot_vector(vector,vector));
	}
	
	inline simd_float4	 simd_cross(const simd_float4 &lhs, const simd_float4 &rhs){
		simd_float4 a1 = _mm_shuffle_ps(lhs,lhs, _MM_SHUFFLE(3,0,2,1));
		simd_float4 b1 = _mm_shuffle_ps(rhs,rhs, _MM_SHUFFLE(3,1,0,2));
		simd_float4 a2 = _mm_shuffle_ps(lhs,lhs, _MM_SHUFFLE(3,1,0,2));
		simd_float4 b2 = _mm_shuffle_ps(rhs,rhs, _MM_SHUFFLE(3,0,2,1));
		return simd_sub(simd_mul(a1, b1), simd_mul(a2, b2));
	}
	
	inline simd_float4	 simd_normalize(const simd_float4 &vector) {
		return simd_div(vector,simd_mag_vector(vector));
	}
	
	inline void  		 simd_setX(simd_float4& vector, const F32 newX) {
		simd_float4 x = simd_float4_replicate(newX);
		x = _mm_shuffle_ps(x,vector, _MM_SHUFFLE(1,1,0,0));
		vector = _mm_shuffle_ps(x,vector, _MM_SHUFFLE(3,2,3,0));
	}
	
	inline void  		 simd_setY(simd_float4& vector, const F32 newY) {
		simd_float4 y = simd_float4_replicate(newY);
		y = _mm_shuffle_ps(y, vector, _MM_SHUFFLE(0,0,0,0));
		vector = _mm_shuffle_ps(y, vector, _MM_SHUFFLE(3,2,0,3));
	}

	inline void  		 simd_setZ(simd_float4& vector, const F32 newZ) {
		simd_float4 z = simd_float4_replicate(newZ);
		z = _mm_shuffle_ps(z, vector, _MM_SHUFFLE(3,3,0,0));
		vector = _mm_shuffle_ps(vector, z, _MM_SHUFFLE(3,0,1,0));
	}
	
	inline void  		 simd_setW(simd_float4& vector, const F32 newW) {
		simd_float4 w = simd_float4_replicate(newW);
		w = _mm_shuffle_ps(w, vector, _MM_SHUFFLE(2,2,0,0));
		vector = _mm_shuffle_ps(vector, w, _MM_SHUFFLE(0,3,1,0));
	}
	
	inline F32  		 simd_getX(const simd_float4& vector) {
		F32 array[4];
		simd_copyToArray(vector, array);
		return array[0];
	}
	
	inline F32  		 simd_getY(const simd_float4& vector) {
		F32 array[4];
		simd_copyToArray(vector, array);
		return array[1];
	}

	inline F32  		 simd_getZ(const simd_float4& vector) {
		F32 array[4];
		simd_copyToArray(vector, array);
		return array[2];
	}
	
	inline F32  		 simd_getW(const simd_float4& vector) {
		F32 array[4];
		simd_copyToArray(vector, array);
		return array[3];
	}
}

#endif //_ROOT_SIMD_FLOAT4_H