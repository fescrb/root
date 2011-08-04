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

#ifndef FLOAT4_H
#define FLOAT4_H

#include "BasicTypes.h"
#include <cmath>
#include <cstdlib>

namespace root{
	struct float4{
		public:
			explicit float4(): x(0.0f), y(0.0f), z(0.0f), w(0.0f){}
			explicit float4(F32 value): x(value), y(value), z(value), w(value){}
			explicit float4(F32 _x, F32 _y, F32 _z, F32 _w): x(_x), y(_y), z(_z), w(_w){}
					float4(const float4 &vector): x(vector.x), y(vector.y), z(vector.z), w(vector.w){}

			inline float4 & operator=(const float4 &rhs){
				if(this != &rhs){
					x = rhs.x;
					y = rhs.y;
					z = rhs.z;
					w = rhs.w;
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
					case 3:
						return w;
				}
			}

			inline float4 operator+(const float4 &rhs) const{
				return float4(x+rhs.x, y+rhs.y, z+rhs.z, w+rhs.w);
			}

			inline float4 operator-(const float4 &rhs) const{
				return float4(x-rhs.x, y-rhs.y, z-rhs.z, w-rhs.w);
			}

			inline float4 operator*(const F32 &rhs) const{
				return float4(x*rhs, y*rhs, z*rhs, w*rhs);
			}

			inline float4 operator*(const float4 &rhs) const{
				return float4(x*rhs.x,y*rhs.y,z*rhs.z,w*rhs.w);
			}

			inline float4 operator/(const F32 &rhs) const{
				return float4(x/rhs,y/rhs,z/rhs, w/rhs);
			}

			inline bool operator==(const float4 &rhs)const{
				return x==rhs.x && y==rhs.y && z==rhs.z && w==rhs.w;
			}

			friend F32 sum(const float4 &vector);
			friend float4 cross(const float4 &lhs, const float4 &rhs);

		private:
			F32 x, y, z, w;
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
		return vector.x + vector.y + vector.z + vector.w;
	}

	inline F32 dot(const float4 &lhs, const float4 &rhs){
		return sum(mul(lhs,rhs));
	}

	inline F32 mag(const float4 &vector){
		return sqrt(fabs(dot(vector,vector)));
	}
}//namespace root

#endif //FLOAT4_H
