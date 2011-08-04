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

#ifndef _ROOT_STRING_DATABASE_H
#define _ROOT_STRING_DATABASE_H

#include "String.h"
#include "HashMap.h"

#include "Hash.h"

namespace root {

	typedef struct {
		inline U32 		 operator()(String string) const{
			return crc32((const U8*)string.getCString(), string.getSize(), CRC_32_IEEE_802_3_POLYNOMIAL );
		}
	} StringCRC32Hash;
	
	class StringDatabase
	:	public HashMap<String,String,StringCRC32Hash> {
		public:
			
			// Singleton class.
			static inline StringDatabase	
									*getSingleton() {
				if(!m_pStringDataBaseInstance)
					m_pStringDataBaseInstance = new StringDatabase;
				return m_pStringDataBaseInstance;
			}
			
			
			inline void				*operator new( size_t size,
												   Allocator* allocator = DefaultAllocator::getStandardAllocator() ) {
				return allocator->allocate(size);
			}
			
		private:
			
			// Will allow custom allocators.
			explicit				 StringDatabase();
			
			static StringDatabase 	*m_pStringDataBaseInstance;
	};
	
}

#endif //_ROOT_STRING_DATABASE_H