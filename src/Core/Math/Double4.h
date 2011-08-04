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

#ifndef DOUBLE4_H
#define DOUBLE4_H

#include "BasicTypes.h"
#include <cmath>
#include <cstdlib>

namespace root {
	struct double4{
		public:
			explicit double4(): x(0.0f), y(0.0f), z(0.0f), w(0.0f){}
			explicit double4(F64 value): x(value), y(value), z(value), w(value){}
			explicit double4(F64 _x, F64 _y, F64 _z, F64 _w): x(_x), y(_y), z(_z), w(_w){}
					double4(const double4 &vector): x(vector.x), y(vector.y), z(vector.z), w(vector.w){}

			inline double4 & operator=(const double4 &rhs){
				if(this != &rhs){
					x = rhs.x;
					y = rhs.y;
					z = rhs.z;
					w = rhs.w;
				}
				return *this;
			}

			inline F64 operator[](const I32 index) const{
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

			inline double4 operator+(const double4 &rhs) const{
				return double4(x+rhs.x, y+rhs.y, z+rhs.z, w+rhs.w);
			}

			inline double4 operator-(const double4 &rhs) const{
				return double4(x-rhs.x, y-rhs.y, z-rhs.z, w-rhs.w);
			}

			inline double4 operator*(const F64 &rhs) const{
				return double4(x*rhs, y*rhs, z*rhs, w*rhs);
			}

			inline double4 operator*(const double4 &rhs) const{
				return double4(x*rhs.x,y*rhs.y,z*rhs.z,w*rhs.w);
			}

			inline double4 operator/(const F64 &rhs) const{
				return double4(x/rhs,y/rhs,z/rhs, w/rhs);
			}

			inline bool operator==(const double4 &rhs)const{
				return x==rhs.x && y==rhs.y && z==rhs.z && w==rhs.w;
			}

			friend F64 sum(const double4 &vector);
			friend double4 cross(const double4 &lhs, const double4 &rhs);

		private:
			F64 x, y, z, w;
	};

	inline double4 add(const double4 &lhs, const double4 &rhs){
		return lhs + rhs;
	}

	inline double4 sub(const double4 &lhs, const double4 &rhs){
		return lhs - rhs;
	}

	inline double4 mul(const double4 &lhs, const F64 &rhs){
		return lhs * rhs;
	}

	inline double4 mul(const double4 &lhs, const double4 &rhs){
		return lhs * rhs;
	}

	inline double4 div(const double4 &lhs, const F64 &rhs){
		return lhs / rhs;
	}

	inline F64 sum(const double4 &vector){
		return vector.x + vector.y + vector.z + vector.w;
	}

	inline F64 dot(const double4 &lhs, const double4 &rhs){
		return sum(mul(lhs,rhs));
	}

	inline F64 mag(const double4 &vector){
		return sqrt(fabs(dot(vector,vector)));
	}
}//namespace root

#endif //DOUBLE4_H
