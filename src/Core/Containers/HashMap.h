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

#ifndef _ROOT_CONTAINERS_HASHMAP_H
#define _ROOT_CONTAINERS_HASHMAP_H

#include "DynamicArray.h"
#include "Pair.h"

#include "Search.h"

namespace root{
	
	template <class HashType, class ValueType>
	struct HashCompareLessOperator {
		inline bool		 operator()(const Pair<HashType,ValueType>& leftHandSide, 
									const Pair<HashType,ValueType>& rightHandSide){
			return leftHandSide.first() < rightHandSide.first();
		}
	};
	
	template <class HashType, class ValueType>
	struct HashCompareEqualityOperator {
		inline bool		 operator()(const Pair<HashType,ValueType>& leftHandSide,
									const Pair<HashType,ValueType>& rightHandSide) const{
			return leftHandSide.first() == rightHandSide.first();				
		}
	};
	
	template <class HashType, class ValueType>
	struct ValueCompareEqualityOperator {
		inline bool		 operator()(const Pair<HashType,ValueType>& leftHandSide,
									const Pair<HashType,ValueType>& rightHandSide) const{
			return leftHandSide.second() == rightHandSide.second();				
		}
	};
	
	template <class Key, 
			  class Value, 
			  class HashFunc, 
			  class HashType = U32,
			  class HashTypePrecedence = HashCompareLessOperator<HashType,Value> >
	class HashMap {
		public:
		
			explicit		 HashMap( U32 preallocateSize = 0,
									  Allocator* allocator = DefaultAllocator::getStandardAllocator() )
			: m_data(preallocateSize, allocator) {
			}
			
			template <class AnyHashFunc, class AnyHashTypePrecedence>
			explicit		 HashMap( const HashMap<Key,Value,AnyHashFunc,HashType,AnyHashTypePrecedence> *other,
									  U32 preallocateSize = 0,
									  Allocator* allocator = DefaultAllocator::getStandardAllocator() )
			: m_data(preallocateSize, allocator) {
			}
			
			/* **********************
			 * Misc setters/getters *
			 ************************/
			
			inline U32		 getSize() const {
				return m_data.getSize();
			}
			
			inline bool		 isEmpty() const {
				return m_data.isEmpty();
			}
			
			inline U32		 getAllocatedSpace() const {
				return m_data.getAllocatedSpace();
			}
			
			Allocator* 		 getAllocator() const {
				return m_data.getAllocator();
			}
			
			void			 reallocate(U32 newSize) const {
				m_data.reallocate();
			}
			
			inline HashType	 hash(const Key& key) const {
				HashFunc hF;
				return hF(key);
			}
			
			inline bool		 getAddsAutomatically() const {
				return m_addAutomatically;
			}
			
			inline void		 setAddsAutomatically(const bool addAutomatically) {
				m_addAutomatically = addAutomatically;
			}
			
			/* *********************
			 * Add/remove elements *
			 ***********************/
			void			 add(const Key& key, const Value& value) {
				HashType hashValue = hash(key);
				iterator it = start();
				
				if(!it.findHash(hashValue)) {
					addAt(it,hashValue,value);
				} else
					it.element() = value;
			}
			
			void			 add(const Pair<Key,Value>& pair) {
				add(pair.first(), pair.second());
			}
			
			void			 erase(Key key) {
				HashType hashValue = hash(key);
				iterator it = start();
				
				if(it.findHash(hashValue)) 
					m_data.erase(it);
			}
			
			void			 clear() {
				m_data.clear();
			}
			
			class iterator {
				public:
					
					inline HashType	 hash() const {
						return m_pHashMap->m_data[m_index].first();
					}
					
					inline Value&	 element() const{
						return m_pHashMap->m_data[m_index].second();
					}
					
					bool 		 find(const Key& key){
						HashType hashValue = hash(key);
						return findHash(hashValue);
					}
					
					bool 		 findHash(const HashType& keyHash){
						U32 closestIndex = 0;
						bool result = dictionarySearch<Pair<HashType,Value>,HashTypePrecedence,HashCompareEqualityOperator>(Pair<HashType,Value>(keyHash,Value()),
																															m_pHashMap->m_pData.getCArray(),
																															m_pHashMap->getSize(), 
																															closestIndex);
						m_index = closestIndex;
					}
					
					bool 		 findValue(const Value& keyHash) {
						// Iterate over the array to search for the item.
						while(m_index < m_pHashMap->getSize()){
							// If the hash is found. We are now pointing to it so we return true.
							if(keyHash==element())
								return true;
							++m_index;
						}
						// If the index becomes m_pHashMap.getSize() we 
						// didn't find the item.
						return false;
					}
					
					/**
					 * Addition operator.
					 * 
					 * @return An iterator pointing to this one's current index + right
					 * hand side.
					 */
					inline iterator		 operator+(const iterator rightHandSide) {
						return iterator(m_index+rightHandSide);
					}
					
					/**
					 * Subtraction operator.
					 * 
					 * @return An iterator pointing to this one's current index - right
					 * hand side.
					 */
					inline iterator		 operator-(const iterator rightHandSide) {
						return iterator(m_index-rightHandSide);
					}
					
					/**
					 * Asignment operator.
					 * 
					 * @return A reference to this iterator having copied the right
					 * hand side iterator.
					 */
					inline iterator&	 operator=(const iterator& rightHandSide) {
						if(this != &rightHandSide) {
							this->m_index = rightHandSide->m_index;
							this->m_pHashMap = rightHandSide->m_pHashMap;
						}
						return *this;
					}
					
					/**
					 * Compound assignment - addition operator.
					 * 
					 * @return This iterator pointing to index + right hand side.
					 */
					inline iterator&	 operator+=(const I32 rightHandSide) {
						this->m_index += rightHandSide;
						return *this;
					}
					
					/**
					 * Compound assignment - substraction operator.
					 * 
					 * @return This iterator pointing to index - right hand side.
					 */
					inline iterator&	 operator-=(const I32 rightHandSide) {
						this->m_index -= rightHandSide;
						return *this;
					}
					
					/**
					 * Prefix increment operator.
					 * 
					 * @return This iterator pointing to index + 1.
					 */
					inline iterator&	 operator++() {
						++(this->m_index);
						return *this;
					}
					
					/**
					 * Postfix increment operator.
					 * 
					 * @return A copy of this iterator. While this iterator
					 * changes to point to index + 1.
					 */
					inline iterator 	 operator++(int) {
						iterator it(*this);
						this->m_index++;
						return it;
					}
					
					/**
					 * Prefix decrement operator.
					 * 
					 * @return This iterator pointing to index - 1.
					 */
					inline iterator&	 operator--() {
						--(this->m_index);
						return *this;
					}
					
					/**
					 * Postfix decrement operator.
					 * 
					 * @return A copy of this iterator. While this iterator
					 * changes to point to index - 1.
					 */
					inline iterator 	 operator--(int) {
						iterator it(*this);
						this->m_index--;
						return it;
					}
					
					/**
					 * Equality operator.
					 * 
					 * @return True iff the iterators are equal. Ie, they iterate
					 * over the same array and are pointing at the same index.
					 */
					inline bool			 operator==(const iterator& rightHandSide) {
						if(this != &rightHandSide) {
							if( this->m_index != rightHandSide->m_index && 
								this->m_pHashMap != rightHandSide->m_pHashMap )
									return false;
						}
						return true;
					}
					
					inline 		 operator I32() {
						return m_index;
					}
					
					
				private:
					
					explicit	 iterator(U32 startingIndex,
										  const HashMap<Key,Value,HashFunc,HashType,HashTypePrecedence> 
											  *hashMap)
					:	m_index(startingIndex),
						m_pHashMap(hashMap) {
					}
					
					I32			 m_index;
					
					const HashMap<Key,Value,HashFunc,HashType,HashTypePrecedence> 
								*m_pHashMap;
					friend class HashMap<Key,Value,HashFunc,HashType,HashTypePrecedence>;
			};
			
			/* ********************
			* Iterator functions *
			**********************/
			
			inline iterator	 start() const {
				return iterator(0,this);
			}
			
			iterator		 end() const {
				return iterator(getSize(),this);
			}
			
			Pair<iterator,bool> find(const Key& key) const {
				iterator it = start();
				return Pair<iterator,bool>(it,it.find(key));
			}
			
			/* *******************
			* Element accessors *
			*********************/
			
			Value&			 get(const Key& key) const {
				HashType hashValue = hash(key);
				iterator it = start();
				
				if(!it.findHash(key)) {
					if(m_addAutomatically)
						add(it,hashValue,Value());
					else
						return Value();
				}
				return it.element();
			}
			
			inline Value&	 operator[](const Key& key) const {
				return get(key);
			}
			
			/* ****************************
			* Copy methods and operators *
			******************************/
			
			template <class AnyHashFunc, class AnyHashTypePrecedence>
			inline void		 copy(const HashMap<Key,Value,AnyHashFunc,HashType,AnyHashTypePrecedence>& other) {
				copy(&other);
			}
			
			template <class AnyHashFunc, class AnyHashTypePrecedence>
			inline HashMap<Key,Value,HashFunc,HashType,HashTypePrecedence>& 
							operator=(const HashMap<Key,Value,AnyHashFunc,HashType,AnyHashTypePrecedence>& other) {
				if(this != &other)
					copy(&other);
				return *this;
			}
		
		protected:
			
			inline void		 addAt(U32 index, const HashType& hashValue, Value& value){
				m_data.insert(index, Pair<HashType,Value>(hashValue,value));
			};
			
			bool			 m_addAutomatically;
			
			DynamicArray<Pair<HashType,Value> >	 
							 m_data;
		
	};
	
}//namespace root

#endif //_ROOT_CONTAINERS_HASHMAP_H
