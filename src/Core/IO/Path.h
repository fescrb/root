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

class P;
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
				static bool 	 isValid(const String path);
				static bool		 exists(const String path);
				static bool		 isFile(const String path);
				static bool		 isDirectory(const String path);
				static bool		 isFullPath(const String path);
				static Path		 getFullPath(const String path);
				static String	 getFilename(const String path, 
											 Allocator* allocator = DefaultAllocator::getStandardAllocator() );
				static String	 getFilenameWithoutExtension(const String path, 
															 Allocator* allocator = DefaultAllocator::getStandardAllocator());
				static String	 getExtension(const String path, 
											  Allocator* allocator = DefaultAllocator::getStandardAllocator());
				static String	 getDirectory(const String path, 
											  Allocator* allocator = DefaultAllocator::getStandardAllocator());
				static String	 getInvalidPathCharacters();
				
				
				void		 	 setPath(const String path);
				void			 copy(const Path* path);
				
				inline bool		 isValid() {
					if( !hasBeenValidityChecked() ) 
						setValidity( isValid( m_pathString ) );
					return getValidity();
				}
				
				inline bool		 exists() {
					if( !hasBeenExistanceChecked() )
						setExistance( exists( m_pathString ) );
					return getExistance();
				}
				
				inline bool 	 isFile() {
					if( !hasBeenTypeChecked() )
						setIsFileType( isFile(m_pathString) );
					return getIsFileType();
				}
				
				inline bool 	 isDirectory() {
					if( !hasBeenTypeChecked() )
						setIsFileType( isFile(m_pathString) );
					return !getIsFileType();
				}
				
				String			 getFullPath() const;
				String			 getFilename() const;
				String			 getFilenameWithoutExtension() const;
				String			 getExtension() const;
				String			 getDirectory() const;
				File			*getFile() ;
				
				void			*operator new(size_t size, 
											  Allocator* allocator = DefaultAllocator::getStandardAllocator() ) {
					return allocator->allocate(size);
				}
				
								 operator String() const {
					return m_pathString;				 
				}
			
			private:
				
				/* ********************
				 * Validity functions *
				 **********************/
				
				bool 			 hasBeenValidityChecked() const {
					return m_pathState & ValidityChecked;
				}
				
				bool 			 setValidity( bool isValid ) {
					// We set that we have validity checked the path.
					m_pathState |= ValidityChecked;
					
					// We set whether we are valid or not. We do this by flipping 
					// the bit if it's not what it's supposed to be.
					if(!( isValid ^ getValidity() ) ) {
						m_pathState ^= IsValid;
					}
				}
				
				bool			 getValidity() const {
					return m_pathState & IsValid;
				}
				
				/* *********************
				 * Existance functions *
				 ***********************/
				
				bool 			 hasBeenExistanceChecked() const {
					return m_pathState & ExistanceChecked;
				}
				
				bool 			 setExistance( bool exists ) {
					// We set that we have validity checked the path.
					m_pathState |= ExistanceChecked;
					
					// We set whether we exists or not, how philosophical. We do 
					// this by flipping the bit if it's not what it's supposed to be.
					if(!( exists ^ getExistance() ) ) {
						m_pathState ^= Exists;
					}
				}
				
				bool			 getExistance() const {
					return m_pathState & Exists;
				}
				
				/* ****************
				 * Type functions *
				 ******************/
				
				bool			 hasBeenTypeChecked() const {
					return m_pathState & TypeChecked;
				}
				
				bool 			 setIsFileType( bool isFileType ) {
					// We set that we have validity checked the path.
					m_pathState |= TypeChecked;
					
					// We set whether we exists or not, how philosophical. We do 
					// this by flipping the bit if it's not what it's supposed to be.
					if(!( isFileType ^ getIsFileType() ) ) {
						m_pathState ^= IsFileType;
					}
				}
				
				bool			 getIsFileType() const {
					return m_pathState & IsFileType;
				}
				
				enum ProgramStateFlags {
					ValidityChecked = 1,
					IsValid = 2,
					ExistanceChecked = 4,
					Exists = 8,
					TypeChecked = 16,
					IsFileType = 32
				};
				
				String			 m_pathString;
			
				/**
				 * Encodes the state of the path (for example, whether it has a file/directory,
				 * or whether any of those qualities has been checked already).
				 */
				U8 				 m_pathState;
				
				static String	 m_invalidPathCharacters;
		};
		
	}//namespace io
	
}//namespace root

#endif //_ROOT_IO_PATH_H
