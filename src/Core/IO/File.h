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

#ifndef _ROOT_IO_FILE_H
#define _ROOT_IO_FILE_H

#include "Path.h"

namespace root{
	
	namespace io{
		
		class File {
			public:
									 File();
				explicit			 File(const String& path);
				explicit 			 File(const Path& path);
				
									~File();
			
				enum FileModeFlags {
					Read  = 1,
					Write = 2,
					Create = 4
				};
				
				/* **************************
				 * Filepath setters/getters *
				 ****************************/
				bool				 setFile(const String& path);
				bool				 setFile(const Path& path);
				bool 				 exists();
				String 				 getFileName();
				
				/* *******************************
				 * Open/close file & check state *
				 *********************************/
				bool 				 open(FileModeFlags fileFlags);
				inline bool 		 isOpen() const {
					return m_isOpen;
				}
				inline I32			 getFileHandle() {
					return m_fileHandle;
				}
				bool				 close();
				
				/* ************************************
				 * Map/unmap fro memory & check state *
				 **************************************/
				U8*					 mapToMemory(U64 offsetFromStart, 
												 U64 bytesToMap, 
												 Allocator* allocator = DefaultAllocator::getStandardAllocator());
				inline bool			 isMemoryMapped() const {
					return m_isMemoryMapped;
				}
				bool				 unmapFromMemory();
				
				/* *****************************
				 * File info setters/modifiers *
				 *******************************/
				inline I64			 getSize() const {
					return m_fileSize;
				}
				bool				 resize(U64 newSize);
				inline I64			 getPosition() const {
					return m_seekPos;
				}
				bool				 seek(I64 offsetFromStart);
				
				/* **********************
				 * Read & write to file *
				 ************************/
				U64 				 read(I8* dataArray, U64 maxRead);
				U64					 readLine(I8* dataArray, U64 maxRead);
				DynamicArray<I8>	*readAll(Allocator *allocator = DefaultAllocator::getStandardAllocator());
				U64					 write(I8* dataArray, U64 arraySize);
				
			private:
				Path				 m_filePath;
				
				I64 				 m_fileSize;
				I64 				 m_seekPos;
				I32 				 m_fileHandle;
				
				bool 				 m_isOpen;
				bool				 m_isMemoryMapped;
		};
	}//namespace io
}//namespace root

#endif //FILE_H
