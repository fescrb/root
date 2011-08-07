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

#ifndef _ROOT_PLANE_H
#define _ROOT_PLANE_H

#include "Float4.h"
#include "Sphere.h"

namespace root {

	struct plane {
		
							 plane() {}
							 
			explicit 		 plane(const float4& pointInPlane,
								   const float4& planeNormal )
			:	m_pointInPlane(pointInPlane),
				m_normal(planeNormal) {
			}
			
			explicit		 plane(const plane& other)
			: 	m_pointInPlane(other.m_pointInPlane),
				m_normal(other.m_normal) {
			}
			
			inline bool		 liesOnPlane(const float4& point) {
				return 0 == isInFront(point);
			}
			
			/**
			 * @return Bigger than 0 if point is in front. 0 iff point
			 * lies on the plane. And less than 0 if it's behind.
			 */
			inline F32		 isInFront(const float4& point) {
				return dot(m_normal, point);
			}
			
			/**
			 * @return Bigger than 0 if sphere is in front or intersects 
			 * the plane. 0 if its in contact and less than one if its completely
			 * behind the plane.
			 */
			inline F32  	 isInFront(const sphere& sph) {
				F32 sphereRadius = sph.getRadius();
				// Move the centre of the sphere a <radius> distance towards the front of
				// the plane.
				float4 spherePoint = ( m_normal*sphereRadius ) + sph.getCenterPosition();
				
				return isInFront(spherePoint);
			}
		
		private:
			float4 			 m_pointInPlane;
			float4 			 m_normal;
	};
	
}

#endif //_ROOT_PLANE_H