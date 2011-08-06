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

#ifndef _ROOT_FLOAT3_H
#define _ROOT_FLOAT3_H

#include "BasicTypes.h"
#include <cmath>
#include <cstdlib>

namespace root{
	struct float3{
		public:
			explicit float3(): m_x(0.0f), m_y(0.0f), m_z(0.0f){}
			explicit float3(F32 value): m_x(value), m_y(value), m_z(value){}
			explicit float3(F32 x, F32 y, F32 z): m_x(x), m_y(y), m_z(z){}
					 float3(const float3 &vector): m_x(vector.m_x), m_y(vector.m_y), m_z(vector.m_z){}

			inline float3 & operator=(const float3 &rhs){
				if(this != &rhs){
					m_x = rhs.m_x;
					m_y = rhs.m_y;
					m_z = rhs.m_z;
				}
				return *this;
			}

			inline float3 operator+(const float3 &rhs) const{
				return float3(m_x+rhs.m_x, m_y+rhs.m_y, m_z+rhs.m_z);
			}

			inline float3 operator-(const float3 &rhs) const{
				return float3(m_x-rhs.m_x, m_y-rhs.m_y, m_z-rhs.m_z);
			}

			inline float3 operator*(const F32 &rhs) const{
				return float3(m_x*rhs, m_y*rhs, m_z*rhs);
			}

			inline float3 operator*(const float3 &rhs) const{
				return float3(m_x*rhs.m_x,m_y*rhs.m_y,m_z*rhs.m_z);
			}

			inline float3 operator/(const F32 &rhs) const{
				return float3(m_x/rhs,m_y/rhs,m_z/rhs);
			}

			inline bool operator==(const float3 &rhs)const{
				return m_x==rhs.m_x && m_y==rhs.m_y && m_z==rhs.m_z;
			}
			
			inline float3 	 replicateX() const{
				return float3(m_x);
			}
			
			inline float3 	 replicateY() const{
				return float3(m_y);
			}
			
			inline float3 	 replicateZ() const{
				return float3(m_z);
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
			
			inline F32   getX() const {
				return m_x;
			}
			
			inline F32   getY() const {
				return m_y;
			}

			inline F32   getZ() const {
				return m_z;
			}

			inline void 	 copyToArray(F32 *array) {
				array[0] = m_x;
				array[1] = m_z;
				array[2] = m_y;
			}

			friend F32 sum(const float3 &vector);
			friend float3 cross(const float3 &lhs, const float3 &rhs);
			
		private:
			F32 m_x, m_y, m_z;
	};

	inline float3 add(const float3 &lhs, const float3 &rhs){
		return lhs + rhs;
	}

	inline float3 sub(const float3 &lhs, const float3 &rhs){
		return lhs - rhs;
	}

	inline float3 mul(const float3 &lhs, const F32 &rhs){
		return lhs * rhs;
	}

	inline float3 mul(const float3 &lhs, const float3 &rhs){
		return lhs * rhs;
	}

	inline float3 div(const float3 &lhs, const F32 &rhs){
		return lhs / rhs;
	}

	inline F32 sum(const float3 &vector){
		return vector.getX() + vector.getY() + vector.getZ();
	}

	inline F32 dot(const float3 &lhs, const float3 &rhs){
		return sum(mul(lhs,rhs));
	}

	inline F32 mag(const float3 &vector){
		return sqrt(fabs(dot(vector,vector)));
	}

	float3 		 cross(const float3 &lhs, const float3 &rhs);
}//namespace root

#endif //FLOAT3_H
