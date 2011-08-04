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

#ifndef _ROOT_IO_PATH_H
#define _ROOT_IO_PATH_H

#include "String.h"

namespace root {
	
	namespace io {
		
		class File;
		
		class Path {
			
			public:
				// Will return root dir.
								 Path();
				
				explicit 	 	 Path(const String path);
				
				// Release allocator.
				virtual			~Path();
			
				// Static utility functions. If custom allocator is used,
				// it must be able to allocate any size chunks.
				static bool		 exists(const String path);
				static bool		 isFullPath(const String path);
				static String	 getFilename(const String path, 
											 Allocator* allocator = DefaultAllocator::getStandardAllocator() );
				static String	 getFilenameWithoutExtension(const String path, 
															 Allocator* allocator = DefaultAllocator::getStandardAllocator());
				static String	 getExtension(const String path, 
											  Allocator* allocator = DefaultAllocator::getStandardAllocator());
				static String	 getDirectory(const String path, 
											  Allocator* allocator = DefaultAllocator::getStandardAllocator());
				static String	 getInvalidPathCharacters();
				
				// Will check for file & correctness.
				void		 	 setPath(const String path);
				void			 copy(const Path* path);
				
				bool			 exists() const;
				String			 getFullPath() const;
				String			 getFilename() const;
				String			 getFilenameWithoutExtension() const;
				String			 getExtension() const;
				String			 getDirectory() const;
				
				File			*openFile() const;
				
				void			*operator new(size_t size, 
											  Allocator* allocator) {
					return allocator->allocate(size);
				}
			
			private:
				String			 m_fullPath;
				
				bool			 m_hasFile;
			
				static String	 m_invalidPathCharacters;
		};
		
	}//namespace io
	
}//namespace root

#endif //_ROOT_IO_PATH_H
