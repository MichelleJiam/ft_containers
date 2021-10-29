/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.ipp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/12 19:09:49 by mjiam         #+#    #+#                 */
/*   Updated: 2021/10/29 19:01:15 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_IPP
# define VECTOR_IPP

// #include "vector.hpp"

namespace ft {

// DEFAULT CONSTRUCTOR
template <class T, class Allocator>
vector<T,Allocator>::vector(Allocator const& alloc)
		: _alloc(alloc), _size(0), _capacity(0), _array(NULL) {
}

// FILL CONSTRUCTOR
// Exceptions:
// allocator::allocate may throw bad alloc;
// allocator::construct calls value_type's copy constructor, which
// 	may throw bad_alloc if value_type is class like map/vector/string.
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
	} // TODO: replace with assign
}

// RANGE CONSTRUCTOR
// Exceptions:
// std::distance may throw if arithmetical operations performed on the 
// 	iterators throw;
// allocator::allocate & allocator:construct may throw bad_alloc.
template <class T, class Allocator>
template <class InputIterator>
vector<T,Allocator>::vector(InputIterator first, InputIterator last,
							Allocator const& alloc)
		:	_alloc(alloc),
			_size(distance(first,last)),
			_capacity(_size), // TODO: 
			_array(alloc.allocate(_size)) {
	try {
		for (size_type i = 0; i < _size; i++) {
			_alloc.construct(&_array[i], *(first + i));
		}
	}
	catch (...) {
		_alloc.deallocate(_array, _size);
		throw;
	} // TODO: replace with assign
}

// COPY CONSTRUCTOR
template <class T, class Allocator>
vector<T,Allocator>::vector(vector const& other)
		: _alloc(other._alloc)  {
	// *this = other;
	// copyRange
	_size = other._size;
	_capacity = other._capacity;
	_array = _alloc.allocate(other._capacity);
	try {
		for (size_type i = 0; i < _size; i++)
			_alloc.construct(&_array[i], other._array[i]);
	}
	catch (...) {
		_alloc.deallocate(_array, _size);
		throw;
	} // TODO: replace with assign
}

// ASSIGNMENT OPERATOR
template <class T, class Allocator>
vector<T,Allocator>&	vector<T,Allocator>::operator=(
		vector const& other) {
	if (this != &other) {
		// assign (which both clears and constructs)
	}
	return *this;
}

// DESTRUCTOR
template <class T, class Allocator>
vector<T,Allocator>::~vector(void) {
	// clear
	_alloc.deallocate(_array, _capacity);
}

template <class T, class Allocator>
void	vector<T,Allocator>::assign(size_type count, const T& value) {
	
}

template <class T, class Allocator>
template <class InputIterator>
void	vector<T,Allocator>::assign (InputIterator first,
										InputIterator last) {

}

template <class T, class Allocator>
typename vector<T,Allocator>::allocator_type vector<T,Allocator>::get_allocator() const {

}

// CAPACITY FUNCTIONS
// Exceptions: never throws
template <class T, class Allocator>
typename vector<T,Allocator>::size_type	vector<T,Allocator>::size(void) const {
	return this->_size;
}

template <class T, class Allocator>
typename vector<T,Allocator>::size_type	vector<T,Allocator>::max_size(void) const {
	return _alloc->max_size();
}

// Changes only the number of elements in the container, not its capacity.
// Exceptions: throws length_error if resized above max_size
template <class T, class Allocator>
void		vector<T,Allocator>::resize(size_type n, value_type val) {
	if (n > this.max_size())
		throw std::length_error("vector::resize - n exceeds vector max_size");
	else if (n < this->_size) {
		for (size_type i = _size; i > n; i--)
			_alloc.destroy(_array[i]);
	}
	else {

	}
}

template <class T, class Allocator>
typename vector<T,Allocator>::size_type	vector<T,Allocator>::capacity(void) const {

}

template <class T, class Allocator>
bool		vector<T,Allocator>::empty(void) const {

}

// Because vectors use an array as their underlying storage, erasing elements
// in positions other than the vector end causes the container to relocate 
// all the elements after the segment erased to their new positions.
// No-throw guarantee if removed elements include last element.
// Returns: iterator following last removed element.
// 			If operation erased last element, end() is returned.
template <class T, class Allocator>
typename vector<T,Allocator>::iterator	vector<T,Allocator>::erase (iterator position) {
	return erase(position, position + 1);
}

template <class T, class Allocator>
typename vector<T,Allocator>::iterator	vector<T,Allocator>::erase (iterator first, iterator last) {
	size_type	n_to_erase = std::distance(first, last);
	size_type	start = std::distance(begin(), first);
	size_type	end;
	
	if (n_to_erase == 0)
		return last;
	for (end = start; end < start + n_to_erase; end++)
		_alloc.destroy(&_array[end]);
	for (size_type j = 0; end + j < _size; j++) {
		_alloc.construct(&_array[start + j], _array[end + j]);
		_alloc.destroy(&_array[end + j]);
	}
	this->_size -= n_to_erase;
	if (end >= _size)
		return end();
	else
		return (last - n_to_erase);
}

// Only reallocates storage, increasing capacity to n or greater,
// 	if `n` > current capacity. Has no effect on current size.
// Exceptions:
// If size requested > vector::max_size, throws length_error exception;
// If reallocating, allocator may throw bad_alloc.
template <class T, class Allocator>
void		vector<T,Allocator>::reserve (size_type n) {

}

} // namespace ft

#endif