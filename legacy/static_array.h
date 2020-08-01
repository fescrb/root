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
 * @file static_array.h
 * @brief Declares the array class.
 */

#ifndef ROOT_STATIC_ARRAY_H_ 
#define ROOT_STATIC_ARRAY_H_ 

#include "root/core/basic_types.h"
#include "root/core/allocator.h"

#include <cstdio>

namespace root
{
    // TODO documentation and allocator stuff
    /** @class 
     * An array class that acts much like C++'s bracket syntax array, with 
     * extra utilities and overhead (since it keeps length as a variable).
     * This difference means it is not called simply array, thus avoiding 
     * confusion.
     */
    template <class data_type>
    class static_array
    {
        public:
            inline           static_array(const data_type * const &array_data, 
                                          const U32 num_elements,
                                          allocator *alloc = allocator::get_default_allocator())
            {
                m_size = num_elements;
                m_a_data = alloc.calloc(sizeof(data_type)*m_size);
                copy_array_data(array_data);
            }
        
            inline           static_array(const static_array &copy_array,
                                          allocator *alloc = allocator::get_default_allocator())
            {
                m_size = copy_array.m_size;
                m_a_data = alloc.calloc(sizeof(data_type)*m_size);
                copy_array_data(copy_array.m_a_data);
            }
                             
            inline const data_type  *get_data() const 
            {
                return m_a_data;
            }
                             
            inline U32       get_size() const
            {
                return m_size;
            }
            
            inline static_array<data_type>
                            &operator=(const static_array<data_type> &rhs)
            {
                if(&rhs != this)
                {
                    m_size = rhs.m_size;
                    copy_array_data(rhs.m_a_data);
                }
                return *this;
            }
                             
            inline data_type        &operator[](const U32 &index)
            {
                return m_a_data[index];
            }
            
            inline static_array<data_type>
                             operator+(const static_array<data_type> &rhs) const
            {
                U32 combined_size = this->m_size + rhs.m_size;
                static_array<data_type> combination = 
                                static_array<data_type>(this->m_a_data, 
                                                        combined_size);
                for(U32 i = this->m_size; i < combined_size; i++)
                {
                    combination.m_a_data[i] = rhs.m_a_data[i];
                }
                
                return combination;
            }
            
        private:
            void             copy_array_data(const data_type * const &array_data)
            {
                std::memcpy(m_a_data, array_data, m_size * sizeof(t));
            }
                             
        protected:
            t               *m_a_data;
            allocator       *m_p_allocator;
            U32              m_size;
    };
} //namespace root

#endif //ROOT_STATIC_ARRAY_H_