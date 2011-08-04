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
 * @file ReferenceCountedMutableString.cpp
 * @brief Provides the implementation of ReferenceCountedMutableString.
 * 
 * Provides the implementation of the ReferenceCountedMutableString class's 
 * constructors.
 */

#include "ReferenceCountedMutableString.h"

using namespace root;

ReferenceCountedMutableString::ReferenceCountedMutableString(Allocator* allocator)
:	MutableString(allocator) {
}

ReferenceCountedMutableString::ReferenceCountedMutableString(const I8* data, 
															 const I32 arraySize,
															 Allocator* allocator)
:	MutableString(data,arraySize < 0? strlen(data):arraySize,allocator) {
}

ReferenceCountedMutableString::ReferenceCountedMutableString(const MutableString* string, 
															 Allocator* allocator)
:	MutableString(string, allocator) {
}

ReferenceCountedMutableString::ReferenceCountedMutableString(const String* string, 
															 Allocator* allocator)
:	MutableString(string, allocator) {
}
