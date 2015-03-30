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
 * @file debug_utils.cpp
 * @brief Defines debug methods.
 * 
 * This file provides the definition of methods and other symbols declared in 
 * debug_utils.h and assert.h
 */

#include "root/core/debug_utils.h"
#include "root/core/assert.h"

#include <cstdio>

namespace root 
{
    void debug_break()
    {
        
    }
    
    //TODO
    /** @fn void root::print_assertion_failure(const I8 * const &,
     * 
     */
    void print_assertion_failure(const I8 * const &expression_str, 
                                 const I8 * const &file, 
                                 const I32 &line)
    {
        std::printf("root error! ROOT_ASSERT(%s) failed! At %s:%d\n",
                        expression_str, file, line);
    }
}