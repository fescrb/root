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

#include <WavefrontOBJFile.h>

#include <File.h>
#include <Mesh.h>

using namespace root;
using namespace asset;

WavefrontOBJFile::WavefrontOBJFile(String path)
:	m_pFile(new io::File(path)){
}

mesh* WavefrontOBJFile::getMathMesh() {
	mesh *objMesh = new mesh();

	// Parse file
	// For all vertices
	// objMesh.addVertex(vertex);
	// For all faces
	// objMesh.addTriangle(triangle);

	return objMesh;
}
