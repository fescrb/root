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
 * @file Pair.h
 * @brief Provides the declaration & implementation of the Pair container.
 * 
 * Provides the declaration and implementation of the templated class Pair.
 */

#ifndef _ROOT_CONTAINERS_PAIR_H
#define _ROOT_CONTAINERS_PAIR_H

namespace root {
	
	/**
	 * @class Pair
	 * 
	 * A templated container clas that holds 2 items.
	 * Provides constructors, accessor methods and 
	 * standard asignment and comparison operators.
	 * Warning: Comparison operators use lexicographical
	 * ordering.
	 */
	template<class First, class Second>
	class Pair {
		public:
			/**
			 * Empty constructor, will call the empty
			 * constructors of both templated types.
			 */
						 Pair() 
			: 	m_first(First()), 
				m_second(Second()) {
			}
			
			/**
			 * Class constructor. Specify both elements that
			 * the Pair will hold.
			 * 
			 * @param first The first item.
			 * @param second The second item.
			 */
			explicit	 Pair(First first, Second second) 
			:	m_first(first), 
				m_second(second) {
			}
			
			/**
			 * Obtain a reference to the first element in the Pair.
			 * Allows for asigning a value after the constructor is called.
			 * @return A reference to the first item held by the class.
			 */
			First&		 first() const {
				return &m_first;
			}
			
			/**
			 * Similar to first(), but for the second element.
			 * Obtain a reference to the second element in the Pair.
			 * Allows for asigning a value after the constructor is called.
			 * @return A reference to the second item held by the class.
			 */
			Second&		 second() const {
				return &m_second;
			}
			
			/**
			 * Asignment operator. Will copy the contents of the right
			 * hand side Pair.
			 * @param rightHandSide The Pair to copy.
			 * @return A reference to this Pair, with the elements copied
			 * from rightHandSide.
			 */
			inline Pair& operator=(const Pair& rightHandSide) {
				if(this != &rightHandSide) {
					this->m_first = rightHandSide->m_first;
					this->m_second = rightHandSide->m_second;
				}
				return *this;
			}
			
			/**
			 * Equality operator.
			 * Will check for equality using the element's own equality
			 * operator.
			 * @param rightHandSide The Pair to compare to.
			 * @return True iff this's first element is equal to rightHandSide's
			 * first AND ditto for second elements.
			 */
			inline bool	 operator==(const Pair& rightHandSide) const {
				if( this->m_first  == rightHandSide->m_first &&
					this->m_second == rightHandSide->m_second )
					return true;
				return false;
			}
			
			/**
			 * Less operator.
			 * Will check if this Pair is less than the given one.
			 * Uses standard operators and lexicographical order.
			 * Meaning that (a,x) < (b,y) only iff a < b OR ( a == b AND
			 * x < y ).
			 * @param rightHandSide The Pair to compare to.
			 * @return True iff this Pair is lexicographically precedent
			 * to the given one. False otherwise.
			 */
			inline bool	 operator<(const Pair& rightHandSide) const {
				if( this->m_first  < rightHandSide->m_first ||
					( this->m_first == rightHandSide->m_first &&
					  this->m_second < rightHandSide->m_second ) )
					return true;
				return false;
			}
			
			/**
			 * Less-than-or-equals operator.
			 * Will check if this Pair is less than  or equals 
			 * the given one. Warning: Uses lexicographical order,
			 * check the less than operator description for further
			 * info.
			 * @param rightHandSide The Pair to compare to.
			 * @return True iff this Pair is lexicographically precedent
			 * or equal to the given one. False otherwise.
			 */
			inline bool	 operator<=(const Pair& rightHandSide) const {
				return *this > rightHandSide || *this == rightHandSide;
			}
			
			/**
			 * Bigger-than operator.
			 * Will check if this Pair is bigger than the given one.
			 * Uses standard operators and lexicographical order.
			 * Meaning that (a,x) > (b,y) only iff a > b OR ( a == b AND
			 * x > y ).
			 * @param rightHandSide The Pair to compare to.
			 * @return True iff this Pair is lexicographically bigger
			 * to the given one. False otherwise.
			 */
			inline bool	 operator>(const Pair& rightHandSide) const {
				if( this->m_first  > rightHandSide->m_first ||
					( this->m_first == rightHandSide->m_first &&
					  this->m_second > rightHandSide->m_second ) )
					return true;
				return false;
			}
			
			/**
			 * Bigger-than-or-equals operator.
			 * Will check if this Pair is bigger than  or equals 
			 * the given one. Warning: Uses lexicographical order,
			 * check the bigger than operator description for further
			 * info.
			 * @param rightHandSide The Pair to compare to.
			 * @return True iff this Pair is lexicographically bigger
			 * or equal to the given one. False otherwise.
			 */
			inline bool	 operator>=(const Pair& rightHandSide) const {
				return *this > rightHandSide || *this == rightHandSide;
			}
			
		private:
			/**
			 * Member variable. The first item.
			 */
			First		 m_first;
			/**
			 * Member variable. The second item.
			 */
			Second		 m_second;
		
	};
	
}//namespace root

#endif //ROOT_PAIR_H
