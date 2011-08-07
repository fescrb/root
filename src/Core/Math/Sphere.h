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

#ifndef _ROOT_SPHERE_H
#define _ROOT_SPHERE_H

#include "Float4.h"

namespace root {

	struct sphere {
		public:
			
							 sphere()
			:	m_positionAndRadius(){}
							 
			explicit 		 sphere(const sphere& other)
			:	m_positionAndRadius(other.m_positionAndRadius){
			}
			
			explicit 		 sphere(const F32 x, F32 y, F32 z, F32 radius)
			: 	m_positionAndRadius(x,y,z,radius){
			}
			
			inline bool		 intersects(const float4& point) const {
				return getRadius() > mag(sub(getCenterPosition(),point));
			}
			
			bool			 intersects(const sphere& other) const;
			
			inline F32		 getRadius() const {
				return m_positionAndRadius.getW();
			}
			
			inline float4	 getCenterPosition() const {
				float4 position(m_positionAndRadius);
				position.setW(1.0f);
				return position;
			}
			
		private:
			float4			 m_positionAndRadius;
	};

}

#endif //_ROOT_SPHERE_H