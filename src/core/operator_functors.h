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
 * @file operator_functors.h
 * @brief < A brief description of the file's contents >
 * 
 * < A more in depth description >
 */

#ifndef ROOT_OPERATOR_FUNCTORS_H_ 
#define ROOT_OPERATOR_FUNCTORS_H_

namespace root
{
    template <class data_type>
    struct equals {
        inline bool      operator()(const data_type& lhs,
                                    const data_type& rhs) const{
            return lhs == rhs;               
        }
    };
    
    template <class data_type>
    struct less {
        inline bool      operator()(const data_type& lhs,
                                    const data_type& rhs) const{
            return lhs < rhs;               
        }
    };
}

#endif //ROOT_OPERATOR_FUNCTORS_H_