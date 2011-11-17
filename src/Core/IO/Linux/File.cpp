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

#include <unistd.h> // close, etc.
#include <fcntl.h> // open, etc.
#include <sys/mman.h> // mmap, etc.

using namespace root;
using namespace root::io;

/* ******************************************************************************
 * To allow compilation (and make our lives easier) we provide a layer over the *
 * system's io API. This is needed since we use functions with the same names.  *
 ********************************************************************************/

typedef struct LinuxFileData {
	I32			fileDescriptor;
};

I32	translateFlagsToFileStatusFlags( File::FileModeFlags flags ) {
	I32 statusFlags = 0;
	if( flags & File::Read && flags & File::Write )
		statusFlags |= O_RDWR;
	else if( flags & File::Write )
		statusFlags |= O_WRONLY;
	else if( flags & File::Read )
		statusFlags |= O_RDONLY;
	if( flags & File::Create )
		statusFlags |= O_CREAT;
	return statusFlags;
}

I32	translateFlagsToProtectFlags( File::FileModeFlags flags ) {
	I32 protectFlags = 0;
	if( flags & File::Write )
		protectFlags |= PROT_WRITE;
	if( flags & File::Read )
		protectFlags |= PROT_READ;
	return protectFlags;
}

inline I32 openFileC( const Path& path, File::FileModeFlags flags ) {
	return open( ((String)path).getCString(), translateFlagsToFileStatusFlags(flags) );
}

inline I32 closeFileC( I32 fileDescriptor ) {
	return close(fileDescriptor);
}

inline bool memoryMapC( I32 fileDescriptor, void* memoryAddress, U64 offsetFromStart, U64 bytesToMap, File::FileModeFlags mappingFlags) {
	I32 protectFlags = translateFlagsToProtectFlags(mappingFlags);
	return 0 < mmap( memoryAddress, bytesToMap, protectFlags, MAP_FIXED | MAP_SHARED, fileDescriptor, offsetFromStart);
}

inline I32 readFileC( ) {
	
}

inline I32 getFileHandle(void* fileData) {
	return ((LinuxFileData*)fileData)->fileDescriptor;
}

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

File::File(const Path& path) {
	setFile(path);
}

bool File::setFile(const String& path) {
	setFile(Path(path));
}

bool File::setFile(const Path& path) {
	m_filePath.copy(&path);
}

bool File::exists() {
	if(!isOpen()) {
		bool canOpen = open(Read);
		close();
		return canOpen;
	} else {
		//return m_fileHandle > 0;
	}
}

String File::getFileName() {
	
}

bool File::open(FileModeFlags fileFlags) {
	//m_fileHandle = openFileC(m_filePath,fileFlags);
	
	//return m_fileHandle > 0;
}

bool File::close() {
	if (isOpen()) {
		//return 0 == closeFileC(m_fileHandle);
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
		
	//m_isMemoryMapped = memoryMapC( getFileHandle() ,memoryAddress, offsetFromStart, bytesToMap, mappingFlags);
	
	return isMemoryMapped();
}

bool File::unmapFromMemory() {
	if(!isMemoryMapped()) {
		
	}
}

bool File::resize(U64 newSize) {
	
}

bool File::seek(I64 offsetFromStart) {
	
}

U64 File::read(I8* dataArray, U64 maxRead) {
	
}

U64	File::readLine(I8* dataArray, U64 maxRead) {
	
}

DynamicArray<I8>* File::readAll(Allocator *allocator) {
	
}

U64	File::write(I8* dataArray, U64 arraySize) {
	
}