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

#include "File.h"

#include "FileUtils.h"

using namespace root;
using namespace root::io;

File::File() 
:	m_fileSize(-1),
	m_seekPos(-1) {
	
}

File::File(const String& path) 
:	m_fileSize(-1),
	m_seekPos(-1) {
	setFile(path);
}

File::~File() {
	close();
}

/*File::File(const Path& path) {
	setFile(path);
}*/

bool File::setFile(const String& path) {
	if(!isOpen())
		m_filePath = path;
	return !isOpen();
}

/*bool File::setFile(const Path& path) {
	m_filePath.copy(&path);
}*/

bool File::exists() {
	if(!isOpen()) {
		bool canOpen = open(Read);
		close();
		return canOpen;
	}
	return true;
}

String File::getFileName() {
	
}

bool File::open(FileModeFlags fileFlags) {
	m_fileHandle = openFile(m_filePath,fileFlags);
	
	return m_fileHandle > 0;
}

bool File::close() {
	if (isOpen()) {
		return 0 == closeFile(m_fileHandle);
	}
	// Nothing to close.
	return false;
}

void*	File::mapToMemory(U64 offsetFromStart, U64 bytesToMap, FileModeFlags mappingFlags, Allocator* allocator) {
	// Check if we can map to memory.
	if(!isOpen())
		if(!open(mappingFlags))
			return NULL;
	if(isMemoryMapped())
		if(!unmapFromMemory())
			return NULL;
	
	// Allocate memory.
	void *mapAddress = allocator->allocate(bytesToMap);
	
	// Map to memory, check for success and return.
	if(!mapToMemoryAddress(mapAddress, offsetFromStart, bytesToMap, mappingFlags)) {
		allocator->free(mapAddress);
		return NULL;
	} else {
		return mapAddress;
	}
}

bool File::mapToMemoryAddress(void* memoryAddress, U64 offsetFromStart,  U64 bytesToMap, FileModeFlags mappingFlags) {
	// Check if we can map to memory.
	if(!isOpen())
		if(!open(mappingFlags))
			return false;
	if(isMemoryMapped())
		if(!unmapFromMemory())
			return false;
		
	m_isMemoryMapped = memoryMap( m_fileHandle ,memoryAddress, offsetFromStart, bytesToMap, mappingFlags);
	
	return isMemoryMapped();
}

bool File::unmapFromMemory() {
	if(!isMemoryMapped()) {
		
	}
}

bool File::resize(U64 newSize) {
	// TODO
}

bool File::seek(I64 offsetFromStart) {
	// TODO
}

U64 File::read(I8* dataArray, U64 maxRead) {
	I64 amountRead = readFile( m_fileHandle, (void*)dataArray, maxRead, m_seekPos);
	m_seekPos+=amountRead;
	return amountRead;
}

U64	File::readLine(I8* dataArray, U64 maxRead) {
	bool foundLine = false;
	while(!foundLine) {
		I64 amountRead = readFile( m_fileHandle, (void*)dataArray, maxRead, m_seekPos);
		if(amountRead!=0){

		} else {

		}
	}
}

DynamicArray<I8>* File::readAll(Allocator *allocator) {
	
}

U64	File::write(I8* dataArray, U64 arraySize) {
	
}
