/*
 * Copyright (C) 2015  Fernando Escribano Macias 
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

/** TODO: Fill file documentation
 * @file <file_name> 
 * @brief < A brief description of the file's contents >
 * 
 * < A more in depth description >
 */

#ifndef ROOT_STRING_H_ 
#define ROOT_STRING_H_

#include "root/code/basic_types.h"
#include "root/code/static_array.h"

#include <cstring>

namespace root 
{
    // TODO docu
    class string : public static_array<I8>
    {
        public:
            explicit inline          string(const char * const &c_str) :
                static_array<I8>(c_str, strlen(c_str)){}
                
            inline                   string(const string &copy_string) :
                static_array<I8>(copy_string) {}
                
            inline HASHTYPE          hash() const;
    };
}

#endif //ROOT_STRING_H_