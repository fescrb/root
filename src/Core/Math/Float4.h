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

#ifndef _ROOT_FLOAT4_H
#define _ROOT_FLOAT4_H

#include "BasicTypes.h"
#include <cmath>
#include <cstdlib>

#include "Float3.h" // For converting between the two.

#ifdef _ROOT_USE_SIMD
	#include "SSE2/SIMD_float4.h"
#endif //_ROOT_USE_SIMD

namespace root{
	
	#ifdef _ROOT_USE_SIMD
	
	struct float4 {
		public:
			explicit 			 float4()
			: 	m_data(simd_float4_zeros()){}
			explicit 			 float4(const F32 value)
			: 	m_data(simd_float4_replicate(value)){}
			explicit 			 float4(const F32 x, const F32 y, 
										const F32 z, const F32 w)
			:   m_data(simd_float4_fromValues(x, y, z, w)){}
								 float4(const simd_float4& vector)
			:   m_data(vector){}
								 float4(const float4 &vector)
			:	m_data(vector.m_data) {}
			
			inline float4 & operator=(const float4 &rhs){
				if(this != &rhs){
					m_data = rhs.m_data;
				}
				return *this;
			}

			inline float4 operator+(const float4 &rhs) const{
				return simd_add(m_data,rhs.m_data);
			}

			inline float4 operator-(const float4 &rhs) const{
				return simd_sub(m_data,rhs.m_data);
			}

			inline float4 operator*(const F32 &rhs) const{
				return simd_mul(m_data,rhs);
			}

			inline float4 operator*(const float4 &rhs) const{
				return simd_mul(m_data,rhs.m_data);
			}

			inline float4 operator/(const F32 &rhs) const{
				return simd_div(m_data,rhs);
			}

			inline bool operator==(const float4 &rhs)const{
				return simd_equals(m_data, rhs.m_data);
			}
			
			inline float4 replicateX() const{
				return float4(simd_replicateX(m_data));
			}
			
			inline float4 replicateY() const{
				return float4(simd_replicateY(m_data));
			}
			
			inline float4 replicateZ() const{
				return float4(simd_replicateZ(m_data));
			}
			
			inline float4 replicateW() const{
				return float4(simd_replicateZ(m_data));
			}
			
			inline void   setX(const F32 newX) {
				simd_setX(m_data,newX);
			}
			
			inline void   setY(const F32 newY) {
				simd_setY(m_data,newY);
			}

			inline void   setZ(const F32 newZ) {
				simd_setZ(m_data,newZ);
			}
			
			inline void   setW(const F32 newW) {
				simd_setW(m_data,newW);
			}
			
			inline F32   getX() const {
				return simd_getX(m_data);
			}
			
			inline F32   getY() const {
				return simd_getY(m_data);
			}

			inline F32   getZ() const {
				return simd_getZ(m_data);
			}
			
			inline F32   getW() const {
				return simd_getW(m_data);
			}
			
			inline void 	 copyToArray(F32 *array) const {
				simd_copyToArray(m_data, array);
			}
			
			friend float4 add(const float4 &lhs, const float4 &rhs);
			friend float4 sub(const float4 &lhs, const float4 &rhs);
			friend float4 mul(const float4 &lhs, const float4 &rhs);
			friend float4 mul(const float4 &lhs, const F32 &rhs);
			friend float4 div(const float4 &lhs, const float4 &rhs);
			friend float4 div(const float4 &lhs, const F32 &rhs);
			friend F32 sum(const float4 &vector);
			friend F32 dot(const float4 &lhs, const float4 &rhs);
			friend float4 cross(const float4 &lhs, const float4 &rhs);
			
		private:
			simd_float4 		 m_data;
	};
	
	inline float4 add(const float4 &lhs, const float4 &rhs){
		return simd_add(lhs.m_data, rhs.m_data);
	}

	inline float4 sub(const float4 &lhs, const float4 &rhs){
		return simd_sub(lhs.m_data, rhs.m_data);
	}

	inline float4 mul(const float4 &lhs, const float4 &rhs){
		return simd_mul(lhs.m_data, rhs.m_data);
	}
	
	inline float4 mul(const float4 &lhs, const F32 &rhs){
		return simd_mul(lhs.m_data, rhs);
	}

	inline float4 div(const float4 &lhs, const float4 &rhs){
		return simd_div(lhs.m_data, rhs.m_data);
	}

	inline float4 div(const float4 &lhs, const F32 &rhs){
		return simd_div(lhs.m_data, rhs);
	}

	inline F32 sum(const float4 &vector){
		return simd_sum(vector.m_data);
	}

	inline F32 dot(const float4 &lhs, const float4 &rhs){
		return simd_dot(lhs.m_data,rhs.m_data);
	}

	inline F32 mag(const float4 &vector){
		return sqrt(fabs(dot(vector,vector)));
	}
	
	inline float4 cross(const float4 &lhs, const float4 &rhs){
		return simd_cross(lhs.m_data,rhs.m_data);
	}
	
	#else //_ROOT_USE_SIMD
	
	/* ************************************
	 * If we don't want to/can't use SIMD *
	 **************************************/
	
	struct float4{
		public:
			explicit float4()
			: 	m_x(0.0f), m_y(0.0f), m_z(0.0f), m_w(0.0f){}
			explicit float4(F32 value)
			: 	m_x(value), m_y(value), m_z(value), m_w(value){}
			explicit float4(F32 x, F32 y, F32 z, F32 w)
			:	m_x(x), m_y(y), m_z(z), m_w(w){}
			explicit float4(const float3& vector, F32 w)
			:	m_x(vector.getX()), m_y(vector.getY()), m_z(vector.getZ()), m_w(w){}
					 float4(const float4 &vector)
			: 	m_x(vector.m_x), m_y(vector.m_y), m_z(vector.m_z), m_w(vector.m_w){}

			inline float4 & operator=(const float4 &rhs){
				if(this != &rhs){
					m_x = rhs.m_x;
					m_y = rhs.m_y;
					m_z = rhs.m_z;
					m_w = rhs.m_w;
				}
				return *this;
			}

			inline float4 operator+(const float4 &rhs) const{
				return float4(m_x+rhs.m_x, m_y+rhs.m_y, m_z+rhs.m_z, m_w+rhs.m_w);
			}

			inline float4 operator-(const float4 &rhs) const{
				return float4(m_x-rhs.m_x, m_y-rhs.m_y, m_z-rhs.m_z, m_w-rhs.m_w);
			}

			inline float4 operator*(const F32 &rhs) const{
				return float4(m_x*rhs, m_y*rhs, m_z*rhs, m_w*rhs);
			}

			inline float4 operator*(const float4 &rhs) const{
				return float4(m_x*rhs.m_x,m_y*rhs.m_y,m_z*rhs.m_z,m_w*rhs.m_w);
			}

			inline float4 operator/(const F32 &rhs) const{
				return float4(m_x/rhs,m_y/rhs,m_z/rhs, m_w/rhs);
			}

			inline bool operator==(const float4 &rhs)const{
				return m_x==rhs.m_x && m_y==rhs.m_y && m_z==rhs.m_z && m_w==rhs.m_w;
			}
			
			inline float4 	 replicateX() const{
				return float4(m_x);
			}
			
			inline float4 	 replicateY() const{
				return float4(m_y);
			}
			
			inline float4 	 replicateZ() const{
				return float4(m_z);
			}
			
			inline float4 	 replicateW() const{
				return float4(m_w);
			}
			
			inline void   setX(const F32 newX) {
				m_x = newX;
			}
			
			inline void   setY(const F32 newY) {
				m_y = newY;
			}

			inline void   setZ(const F32 newZ) {
				m_z = newZ;
			}
			
			inline void   setW(const F32 newW) {
				m_w = newW;
			}
			
			inline F32   getX() const {
				return m_x;
			}
			
			inline F32   getY() const {
				return m_y;
			}

			inline F32   getZ() const {
				return m_z;
			}
			
			inline F32   getW() const {
				return m_w;
			}

			inline void 	 copyToArray(F32 *array) const {
				array[0] = m_x;
				array[1] = m_z;
				array[2] = m_y;
				array[3] = m_w;
			}
			
		private:
			
			F32 m_x, m_y, m_z, m_w;
	};
	
	inline float4 add(const float4 &lhs, const float4 &rhs){
		return lhs + rhs;
	}

	inline float4 sub(const float4 &lhs, const float4 &rhs){
		return lhs - rhs;
	}

	inline float4 mul(const float4 &lhs, const F32 &rhs){
		return lhs * rhs;
	}

	inline float4 mul(const float4 &lhs, const float4 &rhs){
		return lhs * rhs;
	}

	inline float4 div(const float4 &lhs, const F32 &rhs){
		return lhs / rhs;
	}

	inline F32 sum(const float4 &vector){
		return vector.getX() + vector.getY() + vector.getZ() + vector.getW();
	}

	inline F32 dot(const float4 &lhs, const float4 &rhs){
		return sum(mul(lhs,rhs));
	}

	inline F32 mag(const float4 &vector){
		return sqrt(fabs(dot(vector,vector)));
	}
	
	inline float4 cross(const float4 &lhs, const float4 &rhs){
		return float4(cross( float3(lhs.getX(), lhs.getY(), lhs.getZ()),
							 float3(rhs.getX(), rhs.getY(), rhs.getZ())),0 );
	}
	
	#endif //_ROOT_USE_SIMD
	
}//namespace root

#endif //_ROOT_FLOAT4_H
