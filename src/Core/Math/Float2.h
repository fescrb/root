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

#ifndef FLOAT2_H
#define FLOAT2_H

#include "BasicTypes.h"
#include <cmath>
#include <cstdlib>

namespace root{
	struct float2{
		public:
			explicit float2(): x(0.0f), y(0.0f){}
			explicit float2(F32 value): x(value), y(value){}
			explicit float2(F32 _x, F32 _y): x(_x), y(_y){}
					float2(const float2 &vector): x(vector.x), y(vector.y){}

			inline float2 & operator=(const float2 &rhs){
				if(this != &rhs){
					x = rhs.x;
					y = rhs.y;
				}
				return *this;
			}

			inline F32 operator[](const I32 index) const{
				switch(index){
					case 0:
						return x;
					case 1:
						return y;
				}
			}

			inline float2 operator+(const float2 &rhs) const{
				return float2(x+rhs.x, y+rhs.y);
			}

			inline float2 operator-(const float2 &rhs) const{
				return float2(x-rhs.x, y-rhs.y);
			}

			inline float2 operator*(const F32 &rhs) const{
				return float2(x*rhs,y*rhs);
			}

			inline float2 operator*(const float2 &rhs) const{
				return float2(x*rhs.x,y*rhs.y);
			}

			inline float2 operator/(const F32 &rhs) const{
				return float2(x/rhs,y/rhs);
			}

			inline bool operator==(const float2 &rhs)const{
				return x==rhs.x && y==rhs.y;
			}

			friend F32 sum(const float2 &vector);

		private:
			F32 x,y;
	};

	inline float2 add(const float2 &lhs, const float2 &rhs){
		return lhs + rhs;
	}

	inline float2 sub(const float2 &lhs, const float2 &rhs){
		return lhs - rhs;
	}

	inline float2 mul(const float2 &lhs, const F32 &rhs){
		return lhs * rhs;
	}

	inline float2 mul(const float2 &lhs, const float2 &rhs){
		return lhs * rhs;
	}

	inline float2 div(const float2 &lhs, const F32 &rhs){
		return lhs / rhs;
	}

	inline F32 sum(const float2 &vector){
		return vector.x + vector.y;
	}

	inline F32 dot(const float2 &lhs, const float2 &rhs){
		return sum(mul(lhs,rhs));
	}

	inline F32 mag(const float2 &vector){
		return sqrt(fabs(dot(vector,vector)));
	}
}//namespace root
#endif //FLOAT2_h
