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

#ifndef FLOAT3_H
#define FLOAT3_H

#include "BasicTypes.h"
#include <cmath>
#include <cstdlib>

namespace root{
	struct float3{
		public:
			explicit float3(): x(0.0f), y(0.0f), z(0.0f){}
			explicit float3(F32 value): x(value), y(value), z(value){}
			explicit float3(F32 _x, F32 _y, F32 _z): x(_x), y(_y), z(_z){}
					float3(const float3 &vector): x(vector.x), y(vector.y), z(vector.z){}

			inline float3 & operator=(const float3 &rhs){
				if(this != &rhs){
					x = rhs.x;
					y = rhs.y;
					z = rhs.z;
				}
				return *this;
			}

			inline F32 operator[](const I32 index) const{
				switch(index){
					case 0:
						return x;
					case 1:
						return y;
					case 2:
						return z;
				}
			}

			inline float3 operator+(const float3 &rhs) const{
				return float3(x+rhs.x, y+rhs.y, z+rhs.z);
			}

			inline float3 operator-(const float3 &rhs) const{
				return float3(x-rhs.x, y-rhs.y, z-rhs.z);
			}

			inline float3 operator*(const F32 &rhs) const{
				return float3(x*rhs, y*rhs, z*rhs);
			}

			inline float3 operator*(const float3 &rhs) const{
				return float3(x*rhs.x,y*rhs.y,z*rhs.z);
			}

			inline float3 operator/(const F32 &rhs) const{
				return float3(x/rhs,y/rhs,z/rhs);
			}

			inline bool operator==(const float3 &rhs)const{
				return x==rhs.x && y==rhs.y && z==rhs.z;
			}

			friend F32 sum(const float3 &vector);
			friend float3 cross(const float3 &lhs, const float3 &rhs);

		private:
			F32 x, y, z;
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
		return vector.x + vector.y + vector.z;
	}

	inline F32 dot(const float3 &lhs, const float3 &rhs){
		return sum(mul(lhs,rhs));
	}

	inline F32 mag(const float3 &vector){
		return sqrt(fabs(dot(vector,vector)));
	}

	float3 cross(const float3 &lhs, const float3 &rhs){
		return float3((lhs.y*rhs.z) - (lhs.z*rhs.y),
					-((lhs.x*rhs.z) - (lhs.z*rhs.x)),
					(lhs.x*rhs.y)-(lhs.y*rhs.x));
	}
}//namespace root

#endif //FLOAT3_H
