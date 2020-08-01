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
 * @file pair.h
 * @brief Provides the declaration & implementation of the pair container.
 * 
 * Provides the declaration and implementation of the templated class pair.
 */

#ifndef ROOT_PAIR_H_
#define ROOT_PAIR_H_

namespace root {
    
    //TODO make this a specialisation of tuple (when that's made)
    /**
     * @class pair
     * 
     * A templated container clasa that holds 2 items.
     * Provides constructors, accessor methods and 
     * standard asignment and comparison operators.
     * Warning: Comparison operators use lexicographical
     * ordering.
     */
    template<class first_type, class second_type>
    class pair {
        public:
                         pair() {}
            
            /**
             * Class constructor. Specify both elements that
             * the pair will hold.
             * 
             * @param first The first item.
             * @param second The second item.
             */
            explicit     pair(const first_type &first, const second_type &second) 
            {
                    m_first = first;
                    m_second = second;
            }
            
            /**
             * Obtain a reference to the first element in the pair.
             * Allows for asigning a value after the constructor is called.
             * @return A reference to the first item held by the class.
             */
            first_type&  first() const {
                return m_first;
            }
            
            /**
             * Similar to first(), but for the second element.
             * Obtain a reference to the second element in the pair.
             * Allows for asigning a value after the constructor is called.
             * @return A reference to the second item held by the class.
             */
            second_type  second() const {
                return m_second;
            }
            
            /**
             * Asignment operator. Will copy the contents of the right
             * hand side pair.
             * @param rhs The pair to copy.
             * @return A reference to this pair, with the elements copied
             * from rhs.
             */
            inline pair& operator=(const pair& rhs) {
                if(this != &rhs) {
                    this->m_first = rhs->m_first;
                    this->m_second = rhs->m_second;
                }
                return *this;
            }
            
            /**
             * Equality operator.
             * Will check for equality using the element's own equality
             * operator.
             * @param rhs The pair to compare to.
             * @return True iff this's first element is equal to rhs'
             * first AND ditto for second elements.
             */
            inline bool  operator==(const pair& rhs) const {
                if( this->m_first  == rhs->m_first &&
                    this->m_second == rhs->m_second )
                    return true;
                return false;
            }
            
            /**
             * Less operator.
             * Will check if this pair is less than the given one.
             * Uses standard operators and lexicographical order.
             * Meaning that (a,x) < (b,y) only iff a < b OR ( a == b AND
             * x < y ).
             * @param rhs The pair to compare to.
             * @return True iff this pair is lexicographically precedent
             * to the given one. False otherwise.
             */
            inline bool  operator<(const pair& rhs) const {
                if( this->m_first  < rhs->m_first ||
                    ( this->m_first == rhs->m_first &&
                      this->m_second < rhs->m_second ) )
                    return true;
                return false;
            }
            
            /**
             * Less-than-or-equals operator.
             * Will check if this pair is less than  or equals 
             * the given one. Warning: Uses lexicographical order,
             * check the less than operator description for further
             * info.
             * @param rhs The pair to compare to.
             * @return True iff this pair is lexicographically precedent
             * or equal to the given one. False otherwise.
             */
            inline bool  operator<=(const pair& rhs) const {
                return *this > rhs || *this == rhs;
            }
            
            /**
             * Bigger-than operator.
             * Will check if this pair is bigger than the given one.
             * Uses standard operators and lexicographical order.
             * Meaning that (a,x) > (b,y) only iff a > b OR ( a == b AND
             * x > y ).
             * @param rhs The pair to compare to.
             * @return True iff this pair is lexicographically bigger
             * to the given one. False otherwise.
             */
            inline bool  operator>(const pair& rhs) const {
                if( this->m_first  > rhs->m_first ||
                    ( this->m_first == rhs->m_first &&
                      this->m_second > rhs->m_second ) )
                    return true;
                return false;
            }
            
            /**
             * Bigger-than-or-equals operator.
             * Will check if this pair is bigger than  or equals 
             * the given one. Warning: Uses lexicographical order,
             * check the bigger than operator description for further
             * info.
             * @param rhs The pair to compare to.
             * @return True iff this pair is lexicographically bigger
             * or equal to the given one. False otherwise.
             */
            inline bool  operator>=(const pair& rhs) const {
                return *this > rhs || *this == rhs;
            }
            
        private:
            /**
             * Member variable. The first item.
             */
            first_type   m_first;
            /**
             * Member variable. The second item.
             */
            second_type  m_second;
        
    };
    
}//namespace root

#endif //ROOT_PAIR_H_
