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

#include "Path.h"

#include "ApplicationEnvironment.h"
#include "File.h"

using namespace root;
using namespace root::io;

Path::Path() {
	copy(ApplicationEnvironment::getRootDirectory());
}
				
Path::Path(const String path) {
	setPath(path);
}

void Path::setPath(const String path) {
	m_pathString = path;
}

void Path::copy(const Path* path) {
	setPath(path->m_pathString);
	m_pathState = path->m_pathState;
}

String Path::getFullPath() const {
	return m_pathString;
}

String Path::getFilename() const {
	return getFilename(m_pathString);
}

String Path::getFilenameWithoutExtension() const {
	return getFilenameWithoutExtension(m_pathString);
}

String Path::getExtension() const {
	return getExtension(m_pathString);
}

String Path::getDirectory() const {
	return getDirectory(m_pathString);
}

File* Path::getFile()  {
	if( isFile() )
		return new File(*this);
	return NULL;
}

/* *************************
 * Static member functions *
 ***************************/

//! @todo Characters 0 - 31 are also invalid, need to encode those. 
String Path::m_invalidPathCharacters = String("<>:\"|?*");

bool Path::exists(const String path) {
	
}

bool Path::isFullPath(const String path) {
	
}

String Path::getFilename(const String path, 
						 Allocator* allocator ) {
	
}

String Path::getFilenameWithoutExtension(const String path, 
										 Allocator* allocator) {
	
}

String Path::getExtension(const String path, 
						  Allocator* allocator) {
	
}

String Path::getDirectory(const String path, 
						  Allocator* allocator) {
	
}

String Path::getInvalidPathCharacters(){
	return m_invalidPathCharacters;
}