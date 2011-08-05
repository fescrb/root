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

#ifndef _ROOT_FLOAT4_4_H
#define _ROOT_FLOAT4_4_H

#include "Float4.h"

namespace root {
	
	struct float4x4 {
		public:
						 float4x4(){}
			explicit 			 float4x4(const float4x4& other)
			:	m_column1(other.m_column1),
				m_column2(other.m_column2),
				m_column3(other.m_column3),
				m_column4(other.m_column4) {
			}
			
			explicit		 	 float4x4(const float4& col1,
										  const float4& col2,
										  const float4& col3,
										  const float4& col4)
			:	m_column1(col1),
				m_column2(col2),
				m_column3(col3),
				m_column4(col4) {
			}
			
			inline float4x4 	 operator+(const float4x4& rightHandSide) {
				return float4x4(m_column1+rightHandSide.m_column1,
								m_column2+rightHandSide.m_column2,
								m_column3+rightHandSide.m_column3,
								m_column4+rightHandSide.m_column4 );
			}
			
			inline float4x4 	 operator-(const float4x4& rightHandSide) {
				return float4x4(m_column1-rightHandSide.m_column1,
								m_column2-rightHandSide.m_column2,
								m_column3-rightHandSide.m_column3,
								m_column4-rightHandSide.m_column4 );
			}
			
			inline float4x4 	 operator*(const float4x4& rightHandSide) {
				return float4x4(operator*(rightHandSide.m_column1),
								operator*(rightHandSide.m_column2),
								operator*(rightHandSide.m_column3),
								operator*(rightHandSide.m_column4) );
			}
			
			inline float4x4 	 operator*(const float4& rightHandSide) {
				float4 x = replicateX(rightHandSide);
				float4 y = replicateY(rightHandSide);
				float4 z = replicateZ(rightHandSide);
				float4 w = replicateW(rightHandSide);
				return (m_column1*x) + (m_column2*y) + (m_column3*z) + (m_column4*w);
			}
			
			inline float4x4 	 transpose() {
				float4 col1Copy(column1), 
					   col2Copy(column2), 
					   col3Copy(column3), 
					   col4Copy(column4);
				m_column1 = float4(col1Copy[0],col2Copy[0],col3Copy[0],col4Copy[0]);
				m_column2 = float4(col1Copy[1],col2Copy[1],col3Copy[1],col4Copy[1]);
				m_column3 = float4(col1Copy[2],col2Copy[2],col3Copy[2],col4Copy[2]);
				m_column4 = float4(col1Copy[3],col2Copy[3],col3Copy[3],col4Copy[3]);
			}
			
			inline float4x4 	 getTransposed() const {
				float4x4 transposed(*this);
				transposed.transpose();
				return transposed;
			}
			
			/* *************************
			 * Static member functions *
			 ***************************/
			
			static float4x4		 identityMatrix() {
				return float4x4(float4( 1, 0, 0, 0),
								float4( 0, 1, 0, 0),
								float4( 0, 0, 1, 0),
								float4( 0, 0, 0, 1) );
			}
			
			static float4x4		 translationMatrix(F32 x, F32 y, F32 z) {
				return float4x4(float4( 1, 0, 0, 0),
								float4( 0, 1, 0, 0),
								float4( 0, 0, 1, 0),
								float4( x, y, z, 1) );
			}
			
			static float4x4		 rotationAroundX(F32 radians) {
				return float4x4(float4( 1,             0,            0, 0),
								float4( 0,  cos(radians), sin(radians), 0),
								float4( 0, -sin(radians), cos(radians), 0),
								float4( 0,             0,            0, 1) );
			}
			
			static float4x4		 rotationAroundY(F32 radians) {
				return float4x4(float4( cos(radians), 0, -sin(radians), 0),
								float4(            0, 1,             0, 0),
								float4( sin(radians), 0,  cos(radians), 0),
								float4(            0, 0,             0, 1) );
			}
			
			static float4x4		 rotationAroundZ(F32 radians) {
				return float4x4(float4( cos(radians), sin(radians), 0, 0),
								float4(-sin(radians), cos(radians), 0, 0),
								float4(            0,            0, 1, 0),
								float4(            0,            0, 0, 1) );
			}
			
			static float4x4		 scalingMatrix(F32 scalingFactor) {
				return float4x4(float4( scalingFactor,             0,             0, 0),
								float4(             0, scalingFactor,             0, 0),
								float4(             0,             0, scalingFactor, 0),
								float4(             0,             0,             0, 1) );
			}
			
		private:
			float4 		 		 m_column1;
			float4 		 		 m_column2;
			float4 		 		 m_column3;
			float4 		 		 m_column4;
	};
	
}// namespace root

#endif _ROOT_FLOAT4_4_H