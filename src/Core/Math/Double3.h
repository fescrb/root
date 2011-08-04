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

#ifndef DOUBLE3_H
#define DOUBLE3_H

#include "BasicTypes.h"
#include <cmath>
#include <cstdlib>

namespace root{
	struct double3{
		public:
			explicit double3(): x(0.0f), y(0.0f), z(0.0f){}
			explicit double3(F64 value): x(value), y(value), z(value){}
			explicit double3(F64 _x, F64 _y, F64 _z): x(_x), y(_y), z(_z){}
					double3(const double3 &vector): x(vector.x), y(vector.y), z(vector.z){}

			inline double3 & operator=(const double3 &rhs){
				if(this != &rhs){
					x = rhs.x;
					y = rhs.y;
					z = rhs.z;
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
				}
			}

			inline double3 operator+(const double3 &rhs) const{
				return double3(x+rhs.x, y+rhs.y, z+rhs.z);
			}

			inline double3 operator-(const double3 &rhs) const{
				return double3(x-rhs.x, y-rhs.y, z-rhs.z);
			}

			inline double3 operator*(const F64 &rhs) const{
				return double3(x*rhs, y*rhs, z*rhs);
			}

			inline double3 operator*(const double3 &rhs) const{
				return double3(x*rhs.x,y*rhs.y,z*rhs.z);
			}

			inline double3 operator/(const F64 &rhs) const{
				return double3(x/rhs,y/rhs,z/rhs);
			}

			inline bool operator==(const double3 &rhs)const{
				return x==rhs.x && y==rhs.y && z==rhs.z;
			}

			friend F64 sum(const double3 &vector);
			friend double3 cross(const double3 &lhs, const double3 &rhs);

		private:
			F64 x, y, z;
	};

	inline double3 add(const double3 &lhs, const double3 &rhs){
		return lhs + rhs;
	}

	inline double3 sub(const double3 &lhs, const double3 &rhs){
		return lhs - rhs;
	}

	inline double3 mul(const double3 &lhs, const F64 &rhs){
		return lhs * rhs;
	}

	inline double3 mul(const double3 &lhs, const double3 &rhs){
		return lhs * rhs;
	}

	inline double3 div(const double3 &lhs, const F64 &rhs){
		return lhs / rhs;
	}

	inline F64 sum(const double3 &vector){
		return vector.x + vector.y + vector.z;
	}

	inline F64 dot(const double3 &lhs, const double3 &rhs){
		return sum(mul(lhs,rhs));
	}

	inline F64 mag(const double3 &vector){
		return sqrt(fabs(dot(vector,vector)));
	}

	double3 cross(const double3 &lhs, const double3 &rhs){
		return double3((lhs.y*rhs.z) - (lhs.z*rhs.y),
					-((lhs.x*rhs.z) - (lhs.z*rhs.x)),
					(lhs.x*rhs.y)-(lhs.y*rhs.x));
	}
}//namespace root

#endif //DOUBLE3_H
