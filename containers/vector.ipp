/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.ipp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/12 19:09:49 by mjiam         #+#    #+#                 */
/*   Updated: 2021/10/20 16:11:35 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// DEFAULT CONSTRUCTOR
template <class T, class Alloc>
ft::vector<T,Alloc>::vector(allocator_type const& alloc)
		: _alloc(alloc), _size(0), _capacity(0), _array(NULL) {
}

// FILL CONSTRUCTOR
// Exceptions:
// allocator::allocate may throw bad alloc;
// allocator::construct calls value_type's copy constructor, which
// 	may throw bad_alloc if value_type is class like map/vector/string.
template <class T, class Alloc>
ft::vector<T,Alloc>::vector(size_type count, value_type const& val,
							allocator_type const& alloc)
		:	_alloc(alloc),
			_size(count),
			_capacity(count),
			_array(alloc.allocate(count)) {
	try {
		for (size_type i = 0; i < count; i++) {
			_alloc.construct(&_array[i], val);
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
template <class T, class Alloc>
template <class InputIterator>
ft::vector<T,Alloc>::vector(InputIterator first, InputIterator last,
							allocator_type const& alloc)
		:	_alloc(alloc),
			_size = std::distance(first, last),
			_capacity = _size, // TODO: 
			_array = alloc.allocate(_size) {
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
template <class T, class Alloc>
ft::vector<T,Alloc>::vector(vector const& other)
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
template <class T, class Alloc>
vector&	ft::vector<T,Alloc>::operator=(vector const& other) {
	if (this != &other) {
		// assign (which both clears and constructs)
	}
	return *this;
}

// DESTRUCTOR
template <class T, class Alloc>
ft::vector<T,Alloc>::~vector(void) {
	// clear
	_alloc.deallocate(_array, _capacity);
}

template <class T, class Alloc>
size_type	ft::vector<T,Alloc>::size(void) const {

}

template <class T, class Alloc>
size_type	ft::vector<T,Alloc>::max_size(void) const {

}

// Changes only the number of elements in the container, not its capacity.
template <class T, class Alloc>
void		ft::vector<T,Alloc>::resize (size_type n, value_type val) {

}

template <class T, class Alloc>
size_type	ft::vector<T,Alloc>::capacity(void) const {

}

template <class T, class Alloc>
bool		ft::vector<T,Alloc>::empty(void) const {

}

// Because vectors use an array as their underlying storage, erasing elements
// in positions other than the vector end causes the container to relocate 
// all the elements after the segment erased to their new positions.
// No-throw guarantee if removed elements include last element.
template <class T, class Alloc>
iterator	ft::vector<T,Alloc>::erase (iterator position) {

}

// Only reallocates storage, increasing capacity to n or greater,
// 	if `n` > current capacity. Has no effect on current size.
// Exceptions:
// If size requested > vector::max_size, throws length_error exception;
// If reallocating, allocator may throw bad_alloc.
template <class T, class Alloc>
void		ft::vector<T,Alloc>::reserve (size_type n) {

}