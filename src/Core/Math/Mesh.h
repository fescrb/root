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

#ifndef _ROOT_MESH_H_
#define _ROOT_MESH_H_

#include <Float4.h>
#include <Int3.h>

#include <DynamicArray.h>

namespace root {

	struct mesh {
		public:
			explicit 		 	 mesh();
			virtual 			~mesh();

			void				 addVertex(float4 vertex);
			void				 addTriangle(int3 triangle);

			float4				 getVertex(U32 index);
			void				 getTriangle(U32 index);


		private:
			DynamicArray<float4> m_aVertices;
			DynamicArray<int3> 	 m_aTriangles;
	};

}

#endif // _ROOT_MESH_H_
