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

/**
 * @file BasicTypes.h
 * @brief A small layer over Unix's stdc file manipulation functions.
 *
 * To allow compilation (and make our lives easier) we provide a layer over the *
 * system's io API. This is needed since we use functions with the same names.  *
 */

#include "BasicTypes.h"

#include "File.h"

#include <unistd.h> // close, etc.
#include <fcntl.h> // open, etc.
#include <sys/mman.h> // mmap, etc.

namespace root {

	namespace io {

		I32	translateFlagsToFileStatusFlags( File::FileModeFlags flags );

		I32	translateFlagsToProtectFlags( File::FileModeFlags flags );

		inline I32 openFile( const String& path, File::FileModeFlags flags ) {
			return open( path.getCString(), translateFlagsToFileStatusFlags(flags) );
		}

		inline I32 closeFile( I32 fileDescriptor ) {
			return close(fileDescriptor);
		}

		inline bool memoryMap( I32 fileDescriptor, void* memoryAddress, U64 offsetFromStart, U64 bytesToMap, File::FileModeFlags mappingFlags) {
			I32 protectFlags = translateFlagsToProtectFlags(mappingFlags);
			return 0 < mmap( memoryAddress, bytesToMap, protectFlags, MAP_FIXED | MAP_SHARED, fileDescriptor, offsetFromStart);
		}

		inline I32 readFile(I32 fileDescriptor, void* memoryAddress, I32 sizeOfBuffer, U64 offsetFromStart) {
			return pread(fileDescriptor, memoryAddress, sizeOfBuffer, offsetFromStart);
		}

		inline I32 writeFile(I32 fileDescriptor, void* memoryAddress, I32 sizeOfBuffer, U64 offsetFromStart) {
			return pwrite(fileDescriptor, memoryAddress, sizeOfBuffer, offsetFromStart);
		}
	}

}
