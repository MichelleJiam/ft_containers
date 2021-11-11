/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.ipp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/12 19:09:49 by mjiam         #+#    #+#                 */
/*   Updated: 2021/11/11 17:41:11 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_IPP
# define VECTOR_IPP

//	#include "vector.hpp"

namespace ft {

//	DEFAULT CONSTRUCTOR
template <class T, class Allocator>
vector<T,Allocator>::vector(Allocator const& alloc)
		: _alloc(alloc), _size(0), _capacity(0), _array(NULL) {
}

//	FILL CONSTRUCTOR
//	Exceptions:
//	allocator::allocate may throw bad alloc;
//	allocator::construct calls value_type's copy constructor, which
//		may throw bad_alloc if value_type is class like map/vector/string.
//	Note: if constructors throw, destructor is not called, so clean up
//			is done on this level before throw.
template <class T, class Allocator>
vector<T,Allocator>::vector(size_type count, T const& value,
							Allocator const& alloc)
		:	_alloc(alloc),
			_size(count),
			_capacity(count),
			_array(alloc.allocate(count)) {
	try {
		for (size_type i = 0; i < count; i++) {
			_alloc.construct(&_array[i], value);
		}
	}
	catch (...) {
		_alloc.deallocate(_array, count);
		throw;
	}
}

//	RANGE CONSTRUCTOR
//	Exceptions:
//	std::distance may throw if arithmetical operations performed on the 
//	iterators throw;
//	allocator::allocate & allocator:construct may throw bad_alloc.
template <class T, class Allocator>
template <class InputIterator>
vector<T,Allocator>::vector(InputIterator first, InputIterator last,
							Allocator const& alloc)
		:	_alloc(alloc),
			_size(std::distance(first, last)),
			_capacity(_size), //	TODO: use reserve?
			_array(alloc.allocate(_size)) {
	try {
		_range_copy(this->begin(), first, last, alloc);
	}
	catch (...) {
		_alloc.deallocate(_array, _size);
	}
			//	_alloc.construct(&_array[i], *(first + i));
}

//	COPY CONSTRUCTOR
//	All elements in `other` are copied but any unused capacity is not.
//	i.e. capacity == size in the new vector.
template <class T, class Allocator>
vector<T,Allocator>::vector(vector const& other)
		:	_alloc(other._alloc),
			_size(other._size),
			_capacity(_size),
			_array(_alloc.allocate(_size)) {
	try {
		_range_copy(this->begin(), other.begin(), other.end(), _alloc);
	}
	catch (...) {
		_alloc.deallocate(_array, _size);
	}
			//	_alloc.construct(&_array[i], other._array[i]);
}

//	ASSIGNMENT OPERATOR
template <class T, class Allocator>
vector<T,Allocator>&	vector<T,Allocator>::operator=(
		vector const& other) {
	if (this != &other) {
		//	assign (which both clears and constructs)
	}
	return *this;
}

//	DESTRUCTOR
template <class T, class Allocator>
vector<T,Allocator>::~vector(void) {
	this->clear();
	_alloc.deallocate(_array, _capacity);
}

//	Destroys current elements and replaces with newly constructed ones.
//	Automatically reallcoates if new size > current capacity.
template <class T, class Allocator>
void	vector<T,Allocator>::assign(size_type count, const T& value) {
	this->clear();
	if (count == 0)
		return ;
	this->reserve(count);
	this->insert(begin(), count, value);
}

template <class T, class Allocator>
template <class InputIterator>
void	vector<T,Allocator>::assign (InputIterator first,
										InputIterator last) {
	size_type	count = std::distance(first, last);
	
	this->clear();
	if (count == 0)
		return ;
	this->reserve(count);
	this->insert(begin(), first, last);
}

template <class T, class Allocator>
typename vector<T,Allocator>::allocator_type vector<T,Allocator>::get_allocator(void) const {

}

//	ELEMENT ACCESS FUNCTIONS

//	CAPACITY FUNCTIONS
template <class T, class Allocator>
bool		vector<T,Allocator>::empty(void) const {
	if (this->_size == 0)
		return true;
	return false;
}

//	No-throw guarantee
template <class T, class Allocator>
typename vector<T,Allocator>::size_type	vector<T,Allocator>::size(void) const {
	return this->_size;
}

template <class T, class Allocator>
typename vector<T,Allocator>::size_type	vector<T,Allocator>::max_size(void) const {
	return _alloc.max_size();
}

//	Only reallocates storage, increasing capacity to n or greater,
//	if `n` > current capacity. Has no effect on current size.
//	Exceptions:
//	If size requested > vector::max_size, throws length_error exception;
//	If reallocating, allocator may throw bad_alloc.
template <class T, class Allocator>
void		vector<T,Allocator>::reserve (size_type new_cap) {

}

template <class T, class Allocator>
typename vector<T,Allocator>::size_type	vector<T,Allocator>::capacity(void) const {
	return this->_capacity;
}

//	After this call, size() returns 0. Leaves capacity unchanged.
//	Invalidates all refs, ptrs, and iterators referring to contained elements.
//	No-throw guarantee
template <class T, class Allocator>
void	vector<T,Allocator>::clear(void) {
	for (size_type i = 0; i < this->_size; i++) {
		_alloc.destroy(_array[i]);
	}
	this->_size = 0;
}

// 
template <class T, class Allocator>
typename vector<T,Allocator>::iterator	vector<T,Allocator>::insert(
		iterator pos, T const& value) {
	this->insert(pos, 1, value);
	return (pos);
}

//	Because vectors use an array as their underlying storage, inserting elements
//	in positions other than the vector end causes the container to relocate 
//	all the elements after `pos` to their new positions.
//	Exceptions: strong guarantee if exception occurs.
template <class T, class Allocator>
void	vector<T,Allocator>::insert(iterator pos, size_type count,
									T const& value) {
	size_type	old_cap = this->capacity();
	size_type	inserted = 0;

	// if (this->capacity - this->size() >= count) {

	// }
	// else {
		try {
			this->reserve(this->size + count);
			if (pos < this->end())
				_range_copy(this->end() - 1, pos, this->end(), _alloc);
			for (; inserted < count; inserted++) {
				
				_alloc.construct(pos - 1 + inserted, value);
			}
		}
		catch (...) {
			for (size_type i = 0; i < inserted; i++)
				_alloc.destroy(&*(pos - 1 + i));
			if (old_cap < this->capacity())
				_alloc.deallocate(&*(pos - 1), this->capacity() - old_cap);
			throw;
		}
	// }
}

template <class T, class Allocator>
template <class InputIterator>
void	vector<T,Allocator>::insert(iterator pos, InputIterator first,
									InputIterator last) {
	
}

//	Because vectors use an array as their underlying storage, erasing elements
//	in positions other than the vector end causes the container to relocate 
//	all the elements after the segment erased to their new positions.
//	`pos` must be dereferencable. User has responsibility to pass valid input.
//	`end()` is not valid and causes undefined behaviour.
//	Exceptions: does not throw unless exception is thrown by the assignment
//				operator of T.
//	Returns: iterator following last removed element.
//				If operation erased last element, end() is returned.
template <class T, class Allocator>
typename vector<T,Allocator>::iterator	vector<T,Allocator>::erase(iterator pos) {
	return erase(pos, pos + 1);
}

//	The iterator first does not need to be dereferenceable if first==last:
//	erasing an empty range is a no-op.
//	Invalid range causes undefined behaviour. Input is user's responsibility.
//	Returns: `first` if empty range or first==end().
template <class T, class Allocator>
typename vector<T,Allocator>::iterator	vector<T,Allocator>::erase(
		iterator first, iterator last) {
	size_type	n_to_erase = std::distance(first, last);
	size_type	start = first - this->begin();
	size_type	end;
	
	if (n_to_erase == 0 || first == this->end())
		return first;
	for (end = start; end < start + n_to_erase; end++)
		_alloc.destroy(&_array[end]);
	try {
		for (size_type j = 0; end + j < _size; j++) {
			_alloc.construct(&_array[start + j], _array[end + j]);
			_alloc.destroy(&_array[end + j]);
		}
	}
	this->_size -= n_to_erase;
	if (end >= _size)
		return this->end();
	else
		return (last - n_to_erase);
}

template <class T, class Allocator>
void	vector<T,Allocator>::push_back(T const& value) {
	
}

template <class T, class Allocator>
void	vector<T,Allocator>::pop_back(void) {
	_alloc.destroy(_array[_size - 1]);
	this->_size =- 1;
}

//	Changes only the number of elements in the container, not its capacity.
//	Exceptions: throws length_error if resized above max_size.
//				Function has no effect then (strong guarantee).
template <class T, class Allocator>
void		vector<T,Allocator>::resize(size_type count, T value) {
	if (count > this->max_size())
		throw std::length_error("vector::resize - n exceeds vector max_size");
	else if (count < this->_size)
		_destroy_until_end(_array[count]);
	else
		this->insert(this->end(), count - this->_size, value);
}

template <class T, class Allocator>
void	vector<T,Allocator>::swap(vector& other) {
	
}

//	Internal fn called by resize.
//	Destroys elements past `new_end` and adjusts _size.
//	If `new_end` exceeds current end, doesn't do anything.
template <class T, class Allocator>
void	vector<T,Allocator>::_destroy_until_end(pointer new_end) {
	pointer	end_ptr = _array[_size];

	if (end_ptr < new_end)
		return ;
	while(end_ptr != new_end) {
		_alloc.destroy(_array[end_ptr]);
		end_ptr--;
		this->_size -= 1;
	}
}

//	Internal fn called by copy and range constructors.
//	Inserts elements in range [first,last] at `start` using `alloc`.
template <class T, class Allocator>
void	vector<T,Allocator>::_range_copy(iterator start, iterator first,
										iterator last, Allocator const& alloc) {
	iterator	cur = start;

	try {
		for (; first != last; first++, cur++)
			alloc.construct(&*cur, *first);
	}
	catch (...) {
		for (size_type i = 0; i < (cur - start); i++)
			alloc.destroy(start + i);
		throw;
	}
}

} //	namespace ft

#endif