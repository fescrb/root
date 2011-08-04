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

#include <fcntl.h> // File io.

using namespace root;
using namespace root::io;

File::File() {
	
}

File::File(const String& path) 
:	m_fileSize(-1),
	m_seekPos(-1),
	m_fileHandle(-1) {
	setFile(path);
}

File::File(const Path& path) {
	setFile(path);
}

bool File::setFile(const String& path) {
	setFile(Path(path));
}

bool File::setFile(const Path& path) {
	m_filePath = path;
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