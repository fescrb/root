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

#ifndef _ROOT_DOUBLE2_H
#define _ROOT_DOUBLE2_H

#include "BasicTypes.h"
#include <cmath>
#include <cstdlib>

namespace root {
	struct double2{
		public:
			explicit double2(): x(0.0f), y(0.0f){}
			explicit double2(F64 value): x(value), y(value){}
			explicit double2(F64 _x, F64 _y): x(_x), y(_y){}
					double2(const double2 &vector): x(vector.x), y(vector.y){}

			inline double2 & operator=(const double2 &rhs){
				if(this != &rhs){
					x = rhs.x;
					y = rhs.y;
				}
				return *this;
			}

			inline F64 operator[](const I32 index) const{
				switch(index){
					case 0:
						return x;
					case 1:
						return y;
				}
			}

			inline double2 operator+(const double2 &rhs) const{
				return double2(x+rhs.x, y+rhs.y);
			}

			inline double2 operator-(const double2 &rhs) const{
				return double2(x-rhs.x, y-rhs.y);
			}

			inline double2 operator*(const F64 &rhs) const{
				return double2(x*rhs,y*rhs);
			}

			inline double2 operator*(const double2 &rhs) const{
				return double2(x*rhs.x,y*rhs.y);
			}

			inline double2 operator/(const F64 &rhs) const{
				return double2(x/rhs,y/rhs);
			}

			inline bool operator==(const double2 &rhs)const{
				return x==rhs.x && y==rhs.y;
			}

			friend F64 sum(const double2 &vector);

		private:
			F64 x,y;
	};

	inline double2 add(const double2 &lhs, const double2 &rhs){
		return lhs + rhs;
	}

	inline double2 sub(const double2 &lhs, const double2 &rhs){
		return lhs - rhs;
	}

	inline double2 mul(const double2 &lhs, const F64 &rhs){
		return lhs * rhs;
	}

	inline double2 mul(const double2 &lhs, const double2 &rhs){
		return lhs * rhs;
	}

	inline double2 div(const double2 &lhs, const F64 &rhs){
		return lhs / rhs;
	}

	inline F64 sum(const double2 &vector){
		return vector.x + vector.y;
	}

	inline F64 dot(const double2 &lhs, const double2 &rhs){
		return sum(mul(lhs,rhs));
	}

	inline F64 mag(const double2 &vector){
		return sqrt(fabs(dot(vector,vector)));
	}
}//namespace root

#endif //_ROOT_DOUBLE2_H
