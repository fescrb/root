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

using namespace root;
using namespace root::io;

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

I32 openFileC( const Path& path, File::FileModeFlags flags ) {
	return open( ((String)path).getCString(), translateFlagsToFileStatusFlags(flags) );
}

I32 closeFileC( I32 fileDescriptor ) {
	return close(fileDescriptor);
}

File::File() 
:	m_fileSize(-1),
	m_seekPos(-1),
	m_fileHandle(-1) {
	
}

File::File(const String& path) 
:	m_fileSize(-1),
	m_seekPos(-1),
	m_fileHandle(-1) {
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
		return m_fileHandle > 0;
	}
}

String File::getFileName() {
	
}

bool File::open(FileModeFlags fileFlags) {
	m_fileHandle = openFileC(m_filePath,fileFlags);
	
	return m_fileHandle > 0;
}

bool File::close() {
	if (isOpen()) {
		return 0 == closeFileC(m_fileHandle);
	}
	// Nothing to close.
	return false;
}

U8*	File::mapToMemory(U64 offsetFromStart, U64 bytesToMap, Allocator* allocator) {
	
}

bool File::unmapFromMemory() {
}