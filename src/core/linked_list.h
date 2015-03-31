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
 * @file linked_list.h
 * @brief < A brief description of the file's contents >
 * 
 * < A more in depth description >
 */

#ifndef ROOT_LINKED_LIST_H_ 
#define ROOT_LINKED_LIST_H_

#include "root/core/allocator.h"
#include "root/core/assert.h"

namespace root
{
    template <class data_type>
    class linked_list
    {
        public:
            
            inline                       linked_list(allocator *alloc = allocator::get_default_allocator())
            {
                m_p_head = NULL;
                m_p_tail = NULL;
                m_p_allocator = alloc;
            }
             
            class node 
            {
                public:
                    inline               node(const data_type &data)
                    {
                        m_data = data;
                        m_p_next = NULL;
                    }
                                         
                    data_type            m_data;
                    node                *m_p_next;
            };
                         
            class iterator
            {
                public:
                                         iterator(const iterator &copy_iterator)
                    {
                        m_current_node = copy_iterator.m_current_node;
                    }
                    
                    inline iterator&     operator++()
                    {
                        if(m_current_node)
                            m_current_node = m_current_node->m_p_next;
                        return *this;
                    }
                    
                    inline iterator      operator++(int)
                    {
                        iterator temp = *this;
                        this->operator++();
                        return temp;
                    }
                    
                    inline data_type&    operator*() const
                    {
                        ROOT_ASSERT(m_current_node != NULL;)
                        return m_current_node->m_data;
                    }
                    
                    inline iterator&     operator=(const iterator &rhs)
                    {
                        if(this != &rhs)
                        {
                            this->m_current_node = rhs.m_current_node;
                        }
                        return *this;
                    }
                    
                    inline bool          operator==(const iterator &rhs) const
                    {
                        return m_current_node == rhs.m_current_node;
                    }
                    
                    inline bool          operator!=(const iterator &rhs) const
                    {
                        return !this->operator==(rhs);
                    }
                    
                    friend class linked_list;
                private:
                    inline               iterator(node *starting_node);
                    
                    node                *m_current_node;
            };
            
            inline iterator      begin()
            {
                return iterator(m_p_head);
            }
            
            inline iterator      end()
            {
                return iterator(NULL);
            }
            
            inline void          push_back(data_type &data)
            {
                m_p_tail->m_p_next = m_p_allocator->malloc(sizeof(node));
                m_p_tail = m_p_tail->m_p_next;
            }
        private:
            
            node                *m_p_head;
            // Makes insertion easier easier
            node                *m_p_tail;
            allocator           *m_p_allocator;
    };
} //namespace root

#endif //ROOT_LINKED_LIST_H_