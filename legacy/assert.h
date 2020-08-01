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
 * @file assert.h
 * @brief Provides the definition of the ROOT_ASSERT macro.
 * 
 * Provides the definition of the ROOT_ASSERT macro and the means
 * to turn it on and off.
 */

#ifndef ROOT_ASSERT_H_
#define ROOT_ASSERT_H_

#include "root/core/basic_types.h"
#include "root/core/debug_utils.h"

namespace root 
{   
    void print_assertion_failure(const I8 * const &expression_str, 
                                 const I8 * const &file, 
                                 const I32 &line);
}

/**
 * @def ROOT_USE_ASSERTIONS
 * 
 * Set to true if assertions are to be used. If set to
 * false all ROOT_ASSERT macros will be resolved to nothing.
 * As a rule of thumb set to true on Debug builds and false
 * in Release builds.
 */
#ifdef ROOT_USE_ASSERTIONS
    /**
     * @def ROOT_ASSERT
     * 
     * Will assert the given expression.
     */
    #define ROOT_ASSERT(_expression_) \
        if(!(_expression_)) \
        { \
            root::print_assertion_failure(#_expression_, __FILE__, __LINE__);\
        }
#else
	#define ROOT_ASSERT(_expression_)
#endif //ROOT_USE_ASSERTIONS

#endif //_ROOT_ASSERT_H
