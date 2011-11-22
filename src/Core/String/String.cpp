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

#include "String.h"

using namespace root;

String::String(Allocator* allocator)
:	m_pPrivateString(new ReferenceCountedMutableString(allocator)) {
	m_pPrivateString->hold();
}

String::String(const I8* string,
			   const I32 arraySize,
			   Allocator* allocator)
:	m_pPrivateString(new ReferenceCountedMutableString(string,
													   arraySize < 0? strlen(string):arraySize,
													   allocator)) {
	m_pPrivateString->hold();
}

String::String(const MutableString* string,
			   Allocator* allocator)
:	m_pPrivateString(new ReferenceCountedMutableString(string,allocator)) {
	m_pPrivateString->hold();
}

String::String(const String* string,
			   Allocator* allocator)
:	m_pPrivateString(string->m_pPrivateString) {
	m_pPrivateString->hold();
}
