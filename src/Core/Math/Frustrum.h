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

#ifndef _ROOT_FRUSTRUM_H
#define _ROOT_FRUSTRUM_H

#include "Plane.h"

namespace root {

	struct frustrum {
		public:
							 frustrum(){}
							 
			explicit 		 frustrum(const frustrum& other)
			: 	m_near(other.m_near), m_far(other.m_far), m_up(other.m_up),
				 m_down(other.m_down), m_left(other.m_left), m_right(other.m_right){}
				 
			explicit 		 frustrum(const float4& eyePosition,
									  const float4& lookingDirection,
									  const float4& centre,
									  const float4& upVector);
		
		private:
			plane			 m_near, m_far, m_up, m_down, m_left, m_right; // B A Start!
			
	};
	
}

#endif //_ROOT_FRUSTRUM_H