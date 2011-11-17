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
 * @file DynamicArray.h
 * @brief Implements the DynamicArray class.
 * 
 * Provides the implementation of the DynamicArray class. An array which
 * resizes itself on the fly as needed.
 */

#ifndef _ROOT_CONTAINERS_DYNAMIC_ARRAY_H
#define _ROOT_CONTAINERS_DYNAMIC_ARRAY_H

#include "BasicTypes.h"
#include "Assert.h"
#include "DefaultAllocator.h"

#include <cstring> // Included for memcpy.

namespace root {
	
    /**
     * @struct DoubleLengthWhenNeeded
     * 
     * The default structure in charge of increasing the size of DynamicArrays
     * when an element is inserted. When the array needs more space, 
     * it will double its allocated space.
     */
	typedef struct {
        /**
         * The operator in charge of calculating how much to increase the size
         * of the array when an element is added.
         * @param allocatedSpace The current amount of allocated space in the 
         * DynamicArray.
         * @param newSize The new size of the array after the element we want
         * to add is inserted/appended.
         * @return The new size we need to allocate. 
         */
		U32 operator()(U32 allocatedSpace, U32 newSize) {
			U32 newAllocatedSpace= allocatedSpace;
			while(newAllocatedSpace < newSize)
				newAllocatedSpace*=2;
			return newAllocatedSpace;
		}
	}DoubleLengthWhenNeeded;
	
    /**
     * @struct DoNotDecreaseLength
     * 
     * The default structure in charge of decreasing the size of DynamicArrays
     * when an element is removed. It will just return the present allocated space.
     */
	typedef struct {
        /**
         * The operator in charge of calculating how much to decrease the size
         * of the array when an element is removed.
         * @param allocatedSpace The current amount of allocated space in the 
         * DynamicArray.
         * @param newSize The new size of the array after the element we want
         * to delete is removed.
         * @return The new size we need to allocate. 
         */
		U32 operator()(U32 allocatedSpace, U32 newSize) {
			return allocatedSpace;
		}
	}DoNotDecreaseLength;
	
	/**
	 * @class DynamicArray 
	 * 
	 * Provides an array which resizes itself when more space is needed.
	 */
	template <class Item, 
			  class IncreaseSize = DoubleLengthWhenNeeded,
			  class DecreaseSize = DoNotDecreaseLength>
	class DynamicArray {
		public:
			/**
			 * Class constructor. Takes the array's initial size and the
			 * allocator with which to allocate array memory.
			 * @param initialSize The array's initial allocated space.The default 
			 * is 0, so no dynamic memory allocation happens within the
			 * constructor.
			 * @param allocator The Allocator instance which will be in 
			 * charge of allocating memory for the array. The default
			 * is the default allocator. Which uses the OS's dynamic
			 * memory allocator.
			 */
			explicit	 DynamicArray(const U32 initialSize = 0, 
									  Allocator *allocator = DefaultAllocator::getStandardAllocator() )
			:	m_pAllocator(allocator) {
				// Initialize the array.
				reallocate(initialSize);
			}
			
			/**
             * Class constructor. Takes an array of elements and its size. As well
             * as the initial allocated space and an allocator to allocate memory
             * with. It will copy the data in the array. 
             * @param data The array to copy.
             * @param arraySize The size of the array, or the amount of elements we
             * want to copy from it. Any value less than 0 will make the constructor 
			 * calculate the size of the array using strlen.
             * @param initialSize The array's initial allocated space.The default 
             * is 0, so no dynamic memory allocation happens within the
             * constructor.
             * @param allocator The Allocator instance which will be in 
             * charge of allocating memory for the array. The default
             * is the default allocator. Which uses the OS's dynamic
             * memory allocator.
             */
			explicit	 DynamicArray( const Item* data, 
									   const I32 arraySize,
									   const U32 initialSize = 0, 
									   Allocator *allocator = DefaultAllocator::getStandardAllocator() )
			:	m_pAllocator(allocator) {
				// Use the given initialSize.
				reallocate(initialSize);
				// Copy data from array.
				copy(data,arraySize < 0 ? strlen(data) : arraySize);
			}
			
			/**
			 * Class copy constructor. Copies the array data from another
			 * DynamicArray.
			 * @param other The DynamicArray from which we copy the 
			 * data.
			 * @param initialSize The array's initial allocated space.The default 
			 * is 0, which will mean that the initial size will be 
			 * increased to that of the other DynamicArray, unless it is
			 * also 0, in which case I do not know why you'd use this.
			 * @param allocator The Allocator instance which will be in 
			 * charge of allocating memory for the array. The default
			 * is the default allocator. Which uses the OS's dynamic
			 * memory allocator.
			 */
			template<class AnyIncreaseSize, class AnyDecraseSize>
			explicit	 DynamicArray(const DynamicArray<Item,AnyIncreaseSize,AnyDecraseSize> *other,
									  const U32 initialSize = 0,
									  Allocator *allocator = DefaultAllocator::getStandardAllocator() )
			:	m_pAllocator(allocator){
				// Use the given initialSize.
				reallocate(initialSize);
				// Copy the other DynamicArray.
				copy(other);
			}
			
			/**
			 * Virtual destructor, in charge of freeing the memory the
			 * DynamicArray owns.
			 */
			virtual 			~DynamicArray() {
				m_pAllocator->free(m_pData);
			}
			
			/**
			 * Get the number of elements in the array, NOT how much 
			 * memory the array has allocated, which may be more.
			 * @return The size of the array.
			 */
			inline U32	 			 getSize() const {
				return m_size;
			}
			
			/**
			 * Returns whether the array has 0 elements, will return
			 * true even if there is still memory allocated.
			 * @return True iff the array has no elements.
			 */
			inline bool	 			 isEmpty() const {
				return getSize();
			}
			
			/**
             * Returns the amount of allocated space, NOT the number of
             * elements in the array.
             * @return The allocated space of the array.
             */
			inline U32	 			 getAllocatedSpace() const {
				return m_allocatedSpace;
			}
			
			/**
             * @return The allocator instance used by the array.
             */
			inline const Allocator	*getAllocator() const {
				return m_pAllocator;
			}
			
			/**
			 * Resize the array. It will be resized in terms of 
			 * allocated memory. If the new given size is smaller than
			 * the ammount of elements, the elements at the tail will be
			 * lost.
			 * @param newSize The desired size of the array.
			 */
			void		 		 reallocate(const U32 newSize) {
				// Prevent unnecessary dynamic allocations.
				if( !( newSize == getAllocatedSpace() ) ) {
					// If the array was initiated, reallocate.
					if(m_pData)
						m_pData = (Item*)m_pAllocator->reallocate(m_pData, newSize*sizeof(Item)+1);
					else
					// Else allocate a new array.
						m_pData = (Item*)m_pAllocator->allocate(newSize*sizeof(Item)+1);
					
					// Update allocated space.
					setAllocatedSpace(newSize);
				}
			}
			
			/**
			 * Appends an element to end of the array. Iff the array 
			 * already has the maximum number of elements, the array 
			 * will have to be resized. Possibly incurring dynamic memory
			 * allocation costs and memory copy costs. In a tight loop
			 * I would recommend to preallocate.  
			 * @param item The element to append.
			 */
			void		 		 pushBack(const Item &item) {
				// Get the new number of items in the Dynamic Array.
				U32 newSize = getSize()+1;
				
				// Check if we need to resize.
				IncreaseSize iS;
				reallocate(iS(getAllocatedSpace(),newSize));
				
				// If there is enough space, add the new item and change the size.
				if(getAllocatedSpace()>newSize)
				{
					getCArray()[getSize()] = item;
					setSize(newSize);
				}
			}
			
			/**
			 * Append the array of elements to the back of the
			 * DynamicArray. Iff the resulting array will exceed the
			 * maximum number of elements, the DynamicArray
			 * will have to be resized. Possibly incurring dynamic memory
			 * allocation costs and memory copy costs. In a tight loop
			 * I would recommend to preallocate.  
			 * @param array The data to append.
			 * @param arraySize The size of the array to append, or
			 * the number of elements from the array you want to append.
			 */
			void 				 append(const Item* array, U32 arraySize) {
				// Get the new number of items in the Dynamic Array.
				U32 newSize = getSize()+arraySize;
				
				// Check if we need to resize.
				IncreaseSize iS;
				reallocate(iS(getAllocatedSpace(),newSize));
				
				// If there is enough space, append the items and change the size.
				if(getAllocatedSpace()>newSize)
				{
					memcpy(&(getCArray()[getSize()-1]),array,arraySize*sizeof(Item));
					setSize(newSize);
				}
			}
			
			/**
			 * Append the given DynamicArray to this DynamicArray. 
			 * Iff the resulting array will exceed the
			 * maximum number of elements, the DynamicArray
			 * will have to be resized. Possibly incurring dynamic memory
			 * allocation costs and memory copy costs. In a tight loop
			 * I would recommend to preallocate.  
			 * @param other The DynamicArray to append.
			 */
			template<class AnyIncreaseSize, class AnyDecraseSize>
			void		 		 append(const DynamicArray<Item,AnyIncreaseSize,AnyDecraseSize> *other) {
				append(other->getCArray(),other->getSize());
			}
			
			/**
			 * Insert the given element at the specified position. 
			 * Aside from a possible memory reallocation and copy, like
			 * with appending, inserting elements at any point but the 
			 * end always carries the extra cost of having to displace
			 * some elements. This is to make space for the new item
			 * and needs a memory copy. Again, in a tight loop, I would
			 * recommend using preallocation and random access.
			 * @param position The position at which to insert the new 
			 * element.
			 * @param item The element to insert.
			 */
			void		 insert(U32 position, const Item &item) {
				/* If an attempt is made to insert to a position which
				 * is not in the array or inmediately after it,
				 * we fail.*/
				ROOT_ASSERT(position <= getSize())
				
				// Get the new number of items in the Dynamic Array.
				U32 newSize = getSize()+1;
				
				// Check if we need to resize.
				IncreaseSize iS;
				reallocate(iS(getAllocatedSpace(),newSize));
				
				// If there is enough space, displace the existing items,
				// add the new item and change the size.
				if(getAllocatedSpace()>newSize)
				{
					// Displacement is done backwards to prevent having to allocate 
					// a buffer to prevent overwriting elements. No displacement 
					// will be done if we try to insert at the end of the array.
					iterator currentItemToDisplace = end();
					while( !(currentItemToDisplace <  position) ) {
						getCArray()[currentItemToDisplace+1] = getCArray()[currentItemToDisplace];
						--currentItemToDisplace;
					}
					
					getCArray()[position] = item;
					setSize(newSize);
				}
			}
			
			/**
			 * Insert the given array of elements into this DynamicArray
			 * in positions between start and end. Including both.
			 * Aside from a possible memory reallocation and copy, like
			 * with appending, inserting elements at any point but the 
			 * end always carries the extra cost of having to displace
			 * some elements. This is to make space for the new items
			 * and needs a memory copy. Again, in a tight loop, I would
			 * recommend using preallocation and random access.
			 * 
			 * @param start The starting position where to insert the elements.
			 * @param end The position where the last item will be inserted.
			 * @param array The array containing the elements to be inserted.
			 */
			void		 insert(U32 start, U32 end, const Item *array) {
				/* If an attempt is made to insert to a position which
				 * is not in the array or inmediately after it,
				 * or start and end are given backwards,
				 * we fail.*/
				ROOT_ASSERT(start <= getSize() || end > start)
				
				U32 itemsToInsert = (end - start) + 1;
				
				// Get the new number of items in the Dynamic Array.
				U32 newSize = getSize() + itemsToInsert;
				
				// Check if we need to resize.
				IncreaseSize iS;
				reallocate(iS(getAllocatedSpace(),newSize));
				
				// If there is enough space, displace the existing items,
				// add the new items and change the size.
				if(getAllocatedSpace()>newSize)
				{
					// Displacement is done backwards to prevent having to allocate 
					// a buffer to prevent overwriting elements. No displacement 
					// will be done if we try to insert at the end of the array.
					iterator currentItemToDisplace = this->end();
					while( !(currentItemToDisplace <  start) ) {
						getCArray()[currentItemToDisplace+itemsToInsert] = getCArray()[currentItemToDisplace];
						--currentItemToDisplace;
					}
					
					memcpy(&(getCArray()[start]),array,itemsToInsert*sizeof(Item));
					setSize(newSize);
				}
			}
			
			/**
			 * Insert the given array of elements into this DynamicArray
			 * starting at the given position. Aside from a possible memory
			 * reallocation and copy, like with appending, inserting elements 
			 * at any point but the end always carries the extra cost of 
			 * having to displace some elements. This is to make space for 
			 * the new items and needs a memory copy. Again, in a tight loop, 
			 * I would recommend using preallocation and random access.
			 * 
			 * @param position The starting position where to insert the elements.
			 * @param array The array containing the elements to be inserted.
			 * @param arraySize The size of the array. Or, alternatively, the
			 * number of items you want to insert.
			 */
			void 		 insert(U32 position, const Item* array, U32 arraySize) {
				// We already have an awesome function which does exactly this,
				// why let it go to waste?
				insert( position, position + arraySize -1, array);
			}
			
			/**
			 * Insert the given DynamicArray of elements into this DynamicArray
			 * starting at the given position. Aside from a possible memory
			 * reallocation and copy, like with appending, inserting elements 
			 * at any point but the end always carries the extra cost of 
			 * having to displace some elements. This is to make space for 
			 * the new items and needs a memory copy. Again, in a tight loop, 
			 * I would recommend using preallocation and random access.
			 * 
			 * @param position The starting position where to insert the elements.
			 * @param other The DynamicArray containing the elements to be inserted.
			 * @param numberOfItemsToCopy The amount of items to copy. Default value is -1. 
			 * If the number is less than 0, the whole DynamicArray is used.
			 */
			template<class AnyIncreaseSize, class AnyDecraseSize>
			void 		 insert(U32 position, 
								const DynamicArray<Item,AnyIncreaseSize,AnyDecraseSize> *other,
								I32 numberOfItemsToCopy = -1 ) {
				numberOfItemsToCopy = numberOfItemsToCopy < 0 ? other->getSize() : numberOfItemsToCopy;
				insert(position, position + numberOfItemsToCopy - 1, other->getCArray() );
			}
			
			/**
			 * Pop the last element of the array, removing it from the 
			 * array. This may also incur memory reallocation and memory
			 * copy costs, if you u se a different resize operation than
			 * the default one.
			 * @return The last element of the array. Now no longer in 
			 * the array.
			 */
			Item		 popBack() {
				// Make sure that there is something to pop.
				ROOT_ASSERT(!isEmpty())
	
				// Get the new number of items in the Dynamic Array.
				U32 newSize = getSize()-1;
				
				// Check if we need to resize.
				DecreaseSize dS;
				reallocate(dS(getAllocatedSpace(),newSize));
				
				// Decrease size.
				setSize(newSize);
				
				//Return the last item.
				return getCArray()[newSize];
			}
			
			/**
			 * Deletes the element at the specified position from the 
			 * array. Please note that when removing an item which is
			 * not at the end of the array, there is an extra memory copy
			 * cost when closing the gap created, alongside any possible
			 * memory reallocation and copy costs from resizing the 
			 * array, in case of a custom resize operation.
			 * @param position The position at which to delete the 
			 * element. 
			 */
			void		 erase(U32 position) {
				// Make sure that position exists.
				ROOT_ASSERT(getSize() > position)
	
				// Get the new number of items in the Dynamic Array.
				U32 newSize = getSize()-1;
				
				// Check if we need to resize.
				DecreaseSize dS;
				reallocate(dS(getAllocatedSpace(),newSize));
				
				// Decrease size.
				setSize(newSize);
				
				// Displace the items to cover the whole, this time forwards.
				memcpy(&getCArray()[position], &getCArray()[position+1], (getSize()-position)*sizeof(Item));
			}

			/**
			 * Deletes the elements between the ones in the positions
			 * specified, including them. 
			 * 
			 * Please note that when removing items which are
			 * not at the end of the array, there is an extra memory copy
			 * cost when closing the gap created, alongside any possible
			 * memory reallocation and copy costs from resizing the 
			 * array, in case of a custom resize operation.
			 * 
			 * @param start The first element to delete.
			 * @param end The last element to delete. Any element 
			 * between this and start will also be deleted.
			 */
			void		 erase(U32 start, U32 end){
				/* Make sure that the elements from start to end are in the array
				 * and that end > start */
				ROOT_ASSERT(end < getSize() && end > start)
				
				// Work out how many items we will delete.
				U32 itemsToDelete = end - start;
	
				// Get the new number of items in the Dynamic Array.
				U32 newSize = getSize()-itemsToDelete;
				
				// Check if we need to resize.
				DecreaseSize dS;
				reallocate(dS(getAllocatedSpace(),newSize));
				
				// Decrease size.
				setSize(newSize);
				
				// Displace the items to cover the whole, this time forwards.
				memcpy(&getCArray()[start], &getCArray()[start+itemsToDelete], (getSize()-(start+itemsToDelete))*sizeof(Item));
			}
			
			/**
			 * Erase the whole array, possibly having to reallocate.
			 */
			void 		 clear() {
				erase(0,getSize()-1);
			}
			
			/**
			 * Swap the elements between the indices given (including both)
			 * by the items in the given array. This will incur memory copy costs
			 * and possibly memory allocation costs. If the items to copy is the same
			 * as the given gap, only 1 memory copy will be used
			 * @param start First element to replace.
			 * @param end Last element to replace.
			 * @param array The array of elements to swap.
			 * @param arraySize The size of the given array. Alternatively, give the 
			 * amount of items to copy.
			 */
			void		 swap(U32 start, U32 end, const Item* array, U32 arraySize) {
				if(((end - start) +1) != arraySize){
					erase(start, end);
					insert(start, array, arraySize);
				} else {
					memcpy(&getCArray()[start],array,arraySize);
				}
			}
			
			/**
			 * Swap the elements between the indices given (including both)
			 * by the items in the given DynamicArray. This will incur memory copy costs
			 * and possibly memory allocation costs. If the items to copy is the same
			 * as the given gap, only 1 memory copy will be used
			 * @param start First element to replace.
			 * @param end Last element to replace.
			 * @param other The DynamicArray with the elements to swap.
			 * @param itemsToSwap The amount of items to swap. Default is -1. If 
			 * a value less than 0 is used, the whole given DynamicArray will be copied.
			 */
			template<class AnyIncreaseSize, class AnyDecraseSize>
			void 		 swap(U32 start,
							  U32 end,
							  const DynamicArray< Item, AnyIncreaseSize, AnyDecraseSize > *other,
							  I32 itemsToSwap = -1 ) {
				swap(start,end,other->getCArray(),itemsToSwap < 0?other->getSize():itemsToSwap);
			}
			
			/* 
			 * Array accessors.
			 */
			
			/**
			 * Get the element at the specified index.
			 * Returns a reference so it can be used for assignments.
			 * @param index The array index to access.
			 * @return Reference to the item at the specified index.
			 */
			inline Item&  get(I32 index) const {
				// Check that index is in range.
				ROOT_ASSERT(index>0 && index < getSize());
				return m_pData[index];
			}
			
			/**
			 * Get the element at the specified index.
			 * Returns a reference so it can be used for assignments.
			 * @param index The array index to access.
			 * @return Reference to the item at the specified index.
			 */
			inline Item& operator[](I32 index) const {
				return get(index);
			}
			
			/**
			 * @class iterator
			 * 
			 * A simple iterator class for a DynamicArray. Eliminating 
			 * or adding elements to the array does not break an 
			 * already existing iterator but it may change what item
			 * it's pointing at, invalidating it.
			 */
			class iterator {
				public:
					/**
					 * Linearly search the array from the point the iterator
					 * is currently pointing at to the end of the array.
					 * If the item is not found, the iterator will point to
					 * an out-of bounds index (specifically the 
					 * DynamicArray's size).
					 * 
					 * @param item The item so search for.
					 * @return True iff item is found, false otherwise.
					 */
					bool	 			 find(const Item &item) {
						// Iterate over the array to search for the item.
						while(m_index < m_pDynamicArray->getSize()){
							// If the item is found. We are now pointing to it so we return true.
							if(item==element())
								return true;
							++m_index;
						}
						// If the index becomes m_pDynamicArray.getSize() we 
						// didn't find the item.
						return false;
					}
					
					bool	 			 reverseFind(const Item &item) {
						// Iterate over the array to search for the item.
						while(m_index >= 0){
							// If the item is found. We are now pointing to it so we return true.
							if(item==element())
								return true;
							--m_index;
						}
						// If the index becomes m_pDynamicArray.getSize() we 
						// didn't find the item.
						return false;
					}
					
					/**
					 * Linearly search for the first occurrence of a sequence of
					 * items.
					 * The iterator will point to the first element in the sequence
					 * if it's found and to an out-of-bounds index if not.
					 * 
					 * @param items A pointer to the sequence of items to find.
					 * @param numItems The number of items in the sequence.
					 * @return True iff the sequence is found. False otherwise.
					 */
					bool	 			 find(const Item *items, const U32 numItems) {
						// We haven't started searching, so we found nothing yet.
						U32 itemsFound = 0;
						while(m_index < m_pDynamicArray->getSize()){
							// If the item is the next one in the sequence,
							// we increment how many items we found.
							if(items[itemsFound]==element()) {	
								++itemsFound;
								// If itemsFound == numItems we have found the sequence.
								// We point to the first element and return true.
								if(itemsFound == numItems){
									m_index-=(numItems-1);
									return true;
								}
							} else {
								// That wasn't the sequence, we start from the begining.
								itemsFound = 0;
							}
							// Continue.
							++m_index;
						}
						// We didn't find the sequence, we return false.
						return false;
					}
					
					bool	 			 reverseFind(const Item *items, const U32 numItems) {
						// We haven't started searching, so we found nothing yet.
						U32 itemsFound = numItems - 1;
						while(m_index >= 0){
							// If the item is the next one in the sequence,
							// we increment how many items we found.
							if(items[itemsFound]==element()) {	
								--itemsFound;
								// If itemsFound == numItems we have found the sequence.
								// We point to the first element and return true.
								if(itemsFound == 0){
									return true;
								}
							} else {
								// That wasn't the sequence, we start from the begining.
								itemsFound = numItems - 1;
							}
							// Continue.
							--m_index;
						}
						// We didn't find the sequence, we return false.
						return false;
					}
					
					/**
					 * A function to access the element the iterator is pointing at.
					 * 
					 * @return The element the iterator is currently pointing at.
					 */
					inline Item&		 element() const {
						return m_pDynamicArray->get(m_index);
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
							this->m_pDynamicArray = rightHandSide->m_pDynamicArray;
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
								this->m_pDynamicArray != rightHandSide->m_pDynamicArray )
									return false;
						}
						return true;
					}
					
					/**
					 * Conversion operator.
					 * Convert into an integer, the integer being
					 * the index.
					 */
					inline 			 operator I32() const {
						return m_index;
					}
				
				protected:
					/**
					 * The protected constructor.
					 * Creates an iterator with the given size and for the given
					 * DynamicArray.
					 * @param index The initial index.
					 * @param pDynamicArray A pointer to the DynamicArray this iterator
					 * iterates over.
					 */
					explicit			 iterator(I32 index, 
												  const DynamicArray<Item,IncreaseSize,DecreaseSize>* pDynamicArray )
					:	m_index(index),
						m_pDynamicArray(pDynamicArray) {
					}
							 
					/**
					 * The current index.
					 */
					I32		 			 m_index;
					/**
					 * The DynamicArray this iterator iterates over.
					 */
					const DynamicArray<Item,IncreaseSize,DecreaseSize> 
										*m_pDynamicArray;
					
				friend class DynamicArray<Item,IncreaseSize,DecreaseSize>;
			};
			
			/**
			 * A quick function to obtain an iterator pointing to element
			 * 0 of the array.
			 * @return An iterator pointing to the begining of the array.
			 */
			iterator		 start() const {
				return iterator(0,this);
			}
			
			/**
			 * A quick function to obtain an iterator pointing to the
			 * last element of the array.
			 * @return An iterator pointing to the end of the array.
			 */
			iterator		 end() const {
				return iterator(getSize()-1,this);
			}
			
			/**
			 * A function to find the first instance of an element. Since
			 * the DynamicArray is not guarranteed to be sorted, this 
			 * function uses a linear search.
			 * @param item The item to find.
			 * @return An iterator pointing to the specified element.
			 */
			iterator		 find(const Item &item) const {
				iterator it = start();
				it.find(item);
				return it;
			}
			
			iterator		 reverseFind(const Item &item) const {
				iterator it = end();
				it.reverseFind(item);
				return it;
			}
			
			/**
			 * A function to find the first instance of a sequence of elements.
			 * Since the DynamicArray is not guarranteed to be sorted, this 
			 * function uses a linear search.
			 * @param items A pointer to the sequence of items to find.
			 * @param numItems The lenght of the sequence.
			 * @return An iterator pointing to the specified element.
			 */
			iterator		 find(const Item *items, const U32 numItems) const {
				iterator it = start();
				it.find(items,numItems);
				return it;
			}
			
			iterator		 reverseFind(const Item *items, const U32 numItems) const {
				iterator it = end();
				it.reverseFind(items,numItems);
				return it;
			}
			
			/**
			 * A function to find the first instance of a sequence of elements.
			 * Since the DynamicArray is not guarranteed to be sorted, this 
			 * function uses a linear search.
			 * @param items A pointer to the sequence of items to find.
			 * @param numItems The lenght of the sequence.
			 * @return An iterator pointing to the specified element.
			 */
			template<class AnyIncreaseSize, class AnyDecraseSize>
			iterator		 find(const DynamicArray< Item, IncreaseSize, DecreaseSize > *other) const {
				iterator it = start();
				it.find(other->getCArray(),other->getSize);
				return it;
			}
			
			/**
			 * A function to obtain a pointer to the first element
			 * in the array.
			 * @return A pointer to the array.
			 */
			inline Item		*getCArray() const {
				return m_pData;
			}
			
			/**
			 * Make a copy of this DynamicArray. Warning: Will incur dynamic
			 * allocation costs if no custom memory allocator is used.
			 * Will copy contents of the array over to the new one.
			 * @param allocator Allocator with which to allocate space
			 * for the new DynamicArray. The default is the one provided by
			 * DefaultAllocator.
			 * @param allocatorForDynamicArray Allocator which the new DynamicArray
			 * will use to allocate its array. Default is NULL. If NULL value
			 * is used, the new DynamicArray will use this DynamicArray's
			 * allocator.
			 * @return A pointer to a copy of this DynamicArray.
			 */
			DynamicArray<Item,IncreaseSize,DecreaseSize>
							*getCopy(Allocator* allocator = DefaultAllocator::getStandardAllocator(),
									 Allocator* allocatorForDynamicArray = NULL ) const {
				return new (allocator) DynamicArray<Item,IncreaseSize,DecreaseSize>(this,
																					allocatorForDynamicArray?
																						allocatorForDynamicArray:
																						m_pAllocator);
			}
			
			/**
			 * Copy contents of the given DynamicArray to this one.
			 * May incur memory reallocation costs and will always cost
			 * a memory copy.
			 * @param other Pointer to the DyanmicArray to copy 
			 * contents from. I don't even know if what I'm writing
			 * is gramatically correct. Its very late...
			 */
			template<class AnyIncreaseSize, class AnyDecraseSize>
			void			 copy(const DynamicArray<Item,AnyIncreaseSize,AnyDecraseSize>* other) {
				copy(other->getCArray(),other->getSize());
			}
			
			/**
			 * Copy the contents of the given array to this one.
			 * May incur memory reallocation costs and will always cost
			 * a memory copy.
			 * @param data A pointer to the array to copy.
			 * @param size The size of the array or the amount of
			 * elements to be copied across.
			 */
			void			 copy(const Item* data, const U32 size) {
				// Check if we need to resize.
				if(size > getSize()) {
					IncreaseSize iS;
					reallocate(iS(getAllocatedSpace(),size));
				} else {
					DecreaseSize dS;
					reallocate(dS(getAllocatedSpace(),size));
				}
				// Set own size.
				setSize(size);
				// Copy the data.
				memcpy(getCArray(), data, size*sizeof(Item));
			}
			
			/**
			 * Asignment operator. Will copy accross array and may
			 * incur memory reallocation costs, use with care.
			 * @param other The DynamicArray to be asigned.
			 */
			template<class AnyIncreaseSize, class AnyDecraseSize>
			inline DynamicArray<Item,IncreaseSize,DecreaseSize>&
							 operator=(const DynamicArray<Item,AnyIncreaseSize,AnyDecraseSize>& other) {
				if(this!=&other){
					copy(other);
				}
				return *this;
			}
			
			/**
			 * Operator new.
			 * Overloading of new operator to make it possible
			 * to dynamically allocate memory for this class using
			 * a custom Allocator. Example usage:
			 * @code
			 * // Make a StackAllocator 50Kb in size.
			 * StackAllocator* stackAllocator = new StackAllocator(50 * 1024);
			 * // Allocate a new DynamicArray.
			 * DynamicArray<U32>* dynArray = new (stackAllocator) DynamicArray;
			 * @endcode
			 * @param size The size of the class given automatically.
			 * @param allocator The allocator to use. Please note that the allocator
			 * will only allocate space for this class and its members. It will
			 * not be in charge of allocating space for the array. That is given
			 * in the constructor.
			 * @return A pointer to the DynamicArray.
			 */
			void			*operator new(size_t size, 
										  Allocator* allocator = DefaultAllocator::getStandardAllocator() ) {
				return allocator->allocate(size);
			}
			
		protected:
			/**
			 * Set the value of the size member variable. Does not resize
			 * the array or check allocated space. Only to be used as a way
			 * to change the member variable from within class functions
			 * and prevent having to change code if the name (or 
			 * representation) ever changes.
			 * @param newSize The value to be set.
			 */
			inline void	 	 setSize(const U32 newSize) {
				m_size = newSize;
			}
			
			/**
			 * Similar to setSize. Only changes the member variable. If actual
			 * reallocation is needed use the method reallocate.
			 * @param newAllocatedSpace The value to be set.
			 */
			inline void	 	 setAllocatedSpace(const U32 newAllocatedSpace) {
				m_allocatedSpace = newAllocatedSpace;
			}
		
			/**
			 * Pointer to the array containing the data of the DynamicArray.
			 */
			Item			*m_pData;
		
			/**
			 * The amount of elements in the array.
			 */
			U32			 	 m_size;
			/**
			 * The amount of space allocated for the array.
			 */
			U32			  	 m_allocatedSpace;
			/**
			 * The allocator in charge of allocating, reallocating
			 * and freeing the array of items.
			 */
			Allocator		*m_pAllocator;
	};
	
} //namespace root

#endif //_ROOT_CONTAINERS_DYNAMIC_ARRAY_H
