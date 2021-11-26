/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.ipp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/12 19:09:49 by mjiam         #+#    #+#                 */
/*   Updated: 2021/11/26 21:09:54 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_IPP
# define VECTOR_IPP

#define myvector ft::vector<T,Allocator>
#define DEBUG 1

//	#include "vector.hpp"
// DEBUG
// #define InputIterator typename vector<T,A>::iterator

// namespace ft {

//	DEFAULT CONSTRUCTOR
template <class T, class Allocator>
myvector::vector(Allocator const& alloc)
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
myvector::vector(size_type count, T const& value, Allocator const& alloc)
		:	_alloc(alloc),
			_size(count),
			_capacity(count),
			_array(_alloc.allocate(count)) {
	try {
		_fill_insert(this->begin(), count, value);
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
template <typename InputIterator>
myvector::vector(InputIterator first, InputIterator last,
				Allocator const& alloc,
				typename std::iterator_traits<InputIterator>::type*) // TODO: change to ft::
		:	_alloc(alloc),
			_size(std::distance(first, last)),
			_capacity(_size), //	TODO: use reserve?
			_array(alloc.allocate(_size)) {
	try {
		_range_copy(this->begin(), first, last);
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
myvector::vector(vector const& other)
		:	_alloc(other._alloc),
			_size(other._size),
			_capacity(_size),
			_array(_alloc.allocate(_size)) {
	try {
		_range_copy(this->begin(), other.begin(), other.end());
	}
	catch (...) {
		_alloc.deallocate(_array, _size);
	}
			//	_alloc.construct(&_array[i], other._array[i]);
	// TODO: check if resize has to be called before range_copy
}

//	ASSIGNMENT OPERATOR
template <class T, class Allocator>
ft::vector<T,Allocator>&	myvector::operator=(vector const& other) {
	if (this != &other) {
		this->assign(other.begin(), other.end());
	}
	return *this;
}

//	DESTRUCTOR
template <class T, class Allocator>
myvector::~vector(void) {
	this->clear();
	_alloc.deallocate(_array, _capacity);
}

// ITERATORS
template <class T, class Allocator>
typename myvector::iterator	myvector::begin(void) {
	return iterator(_array);
}

template <class T, class Allocator>
typename myvector::const_iterator	myvector::begin(void) const {
	return const_iterator(_array);
}

template <class T, class Allocator>
typename myvector::iterator	myvector::end(void) {
	return iterator(_array + _size);
}

template <class T, class Allocator>
typename myvector::const_iterator	myvector::end(void) const {
	return const_iterator(_array + _size);
}


//	Destroys current elements and replaces with newly constructed ones.
//	Automatically reallcoates if new size > current capacity.
template <class T, class Allocator>
void	myvector::assign(size_type count, const T& value) {
	this->clear();
	if (count == 0)
		return ;
	this->reserve(count);
	this->insert(begin(), count, value);
}

template <class T, class Allocator>
template <typename InputIterator>
void	myvector::assign (InputIterator first, InputIterator last,
							typename std::iterator_traits<InputIterator>::type*) { // TODO: change to ft
	size_type	count = std::distance(first, last);
	
	this->clear();
	if (count == 0)
		return ;
	this->reserve(count);
	this->insert(begin(), first, last);
}

template <class T, class Allocator>
typename myvector::allocator_type myvector::get_allocator(void) const {
	return this->_alloc;
}

//	ELEMENT ACCESS FUNCTIONS
template <class T, class Allocator>
typename myvector::reference myvector::operator[](size_type pos) {
	return (this->_array[pos]);
}


//	CAPACITY FUNCTIONS
template <class T, class Allocator>
bool		myvector::empty(void) const {
	if (this->_size == 0)
		return true;
	return false;
}

//	No-throw guarantee
template <class T, class Allocator>
typename myvector::size_type	myvector::size(void) const {
	return this->_size;
}

template <class T, class Allocator>
typename myvector::size_type	myvector::max_size(void) const {
	return _alloc.max_size();
}

//	Only reallocates storage, increasing capacity to n or greater,
//	if `new_cap` > current capacity. Has no effect on current size.
//	Exceptions:
//	If size requested > vector::max_size, throws length_error exception;
//	If reallocating, allocator may throw bad_alloc.
template <class T, class Allocator>
void		myvector::reserve (size_type new_cap) {
	if (new_cap > this->max_size())
		throw std::length_error(
			"vector::reserve - new_cap exceeds vector max_size");
	if (new_cap > this->capacity()) {
		if (DEBUG) std::cout << "reserve: reallocating more memory\n";
		// note: problem with push_back was reserve was not reallocating more mem
		size_type	old_size = this->size();
		pointer		tmp = NULL;
		try {
			 tmp = _alloc.allocate(new_cap);
			 if (this->size() > 0) {
				_range_copy(tmp, this->begin(), this->end() - 1);
				_destroy_until(this->begin(), this->end());
			 }
			_alloc.deallocate(&*this->begin(), this->_capacity);
			this->_array = tmp;
			this->_size = old_size;
			this->_capacity = new_cap;
		}
		catch (...) {
			if (tmp)
				_alloc.deallocate(tmp, new_cap);
			throw;
		}
		if (DEBUG) std::cout << "capacity is now " << this->capacity() << std::endl;
	}
}

template <class T, class Allocator>
typename myvector::size_type	myvector::capacity(void) const {
	return this->_capacity;
}

//	After this call, size() returns 0. Leaves capacity unchanged.
//	Invalidates all refs, ptrs, and iterators referring to contained elements.
//	No-throw guarantee
template <class T, class Allocator>
void	myvector::clear(void) {
	for (size_type i = 0; i < this->_size; i++) {
		_alloc.destroy(&_array[i]);
	}
	this->_size = 0;
}

// 
template <class T, class Allocator>
typename myvector::iterator	myvector::insert(iterator pos, T const& value) {
	this->insert(pos, 1, value);
	return (pos);
}

//	Because vectors use an array as their underlying storage, inserting elements
//	in positions other than the vector end causes the container to relocate 
//	all the elements after `pos` to their new positions.
//	Exceptions: strong guarantee if exception occurs.
template <class T, class Allocator>
void	myvector::insert(iterator pos, size_type count, T const& value) {
	size_type	old_cap = this->capacity();
	// size_type   elems_after = vec.end() - pos;
	size_type   offset = pos - this->begin();

	try {
		// if (DEBUG) std::cout << "insert (fill): calling expand_and_move, begin was " << *begin() << std::endl;
		_expand_and_move(pos, count, offset);
		if (DEBUG) std::cout << "insert (fill): begin now " << *begin() << ", calling _fill_insert with begin + " << offset << std::endl;
		_fill_insert(this->begin() + offset, count, value);
		if (DEBUG) std::cout << "inserting " << value << " at position " << offset << std::endl;
		this->_size += count; // TODO: check if resizing needs to be done before range_copy
			// if this doesn't work, have to add old_size var for resizing on failure
	}
	catch (...) {
		if (old_cap < this->capacity())
			_alloc.deallocate(&*(this->begin() + offset), this->capacity() - old_cap);
		throw;
	}
}

template <class T, class Allocator>
template <typename InputIterator>
void	myvector::insert(iterator pos, InputIterator first, InputIterator last,
						typename std::iterator_traits<InputIterator>::type*) { // TODO: enable_if/is_integral, change std:: to ft::
	size_type	old_cap = this->capacity();
	// size_type   elems_after = vec.end() - pos;
	size_type   offset = pos - this->begin();
	size_type	count = last - first;

	try {
		// if (this->size() + count > this->capacity())
		// 	this->reserve(this->size() + count);
		// if (elems_after >= count)
		// 	_range_copy(pos + count, pos, this->end());
		_expand_and_move(pos, count, offset);
		_range_copy(this->begin() + offset, first, last);
		this->size += count; // TODO: check if resizing needs to be done before range_copy
			// if this doesn't work, have to add old_size var for resizing on failure
	}
	catch (...) {
		if (old_cap < this->capacity())
			_alloc.deallocate(&*(this->begin() + offset), this->capacity() - old_cap);
		throw;
	}
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
typename myvector::iterator	myvector::erase(iterator pos) {
	return erase(pos, pos + 1);
}

//	The iterator first does not need to be dereferenceable if first==last:
//	erasing an empty range is a no-op.
//	Invalid range causes undefined behaviour. Input is user's responsibility.
//	Returns: `first` if empty range or first==end().
template <class T, class Allocator>
typename myvector::iterator	myvector::erase(
		iterator first, iterator last) {
	size_type	n_to_erase = last - first;
	size_type	start = first - this->begin();
	size_type	end;
	size_type	i = 0;
	
	if (n_to_erase < 1 || first == this->end())
		return first;
	for (end = start; end < start + n_to_erase; end++)
		_alloc.destroy(&_array[end]);
	try {
		for (; end + i < _size; i++) {
			_alloc.construct(&_array[start + i], _array[end + i]);
			_alloc.destroy(&_array[end + i]);
		}
	}
	catch (...) {
		for (size_type j = 0; j < i; j++)
			_alloc.destroy(&_array[start + j]);
		throw;
	}
	this->_size -= n_to_erase;
	if (end >= _size)
		return this->end();
	else
		return (last - n_to_erase);
}

//	Exceptions: strong guarantee, fn has no effect.
//				May throw length_error if reallocation exceeds max_size.
template <class T, class Allocator>
void	myvector::push_back(T const& value) {
	insert(_array + _size, value);
}

template <class T, class Allocator>
void	myvector::pop_back(void) {
	_alloc.destroy(&_array[_size - 1]);
	this->_size =- 1;
}

//	Changes only the number of elements in the container, not its capacity.
//	Exceptions: throws length_error if resized above max_size.
//				Function has no effect then (strong guarantee).
template <class T, class Allocator>
void		myvector::resize(size_type count, T value) {
	if (count > this->max_size())
		throw std::length_error(
			"vector::resize - count exceeds vector max_size");
	else if (count < this->size())
		_destroy_until(_array[count], _array[_size]);
	else
		this->insert(this->end(), count - this->_size, value);
}

template <class T, class Allocator>
void	myvector::swap(vector& other) {
	(void)other; // DEBUG
}

//	Internal fn called by resize, reserve.
//	Destroys elements from `old_end` to `new_end` and adjusts _size.
//	If `new_end` exceeds current end, doesn't do anything.
template <class T, class Allocator>
void	myvector::_destroy_until(iterator new_end, iterator old_end) {
	// pointer	end_ptr = old_end;

	if (old_end < new_end)
		return ;
	while (old_end != new_end) {
		_alloc.destroy(&*old_end);
		// end_ptr--;
		old_end--;
		this->_size -= 1;
	}
}

//	Internal fn called by copy and range constructors.
//	Inserts elements in range [first,last] at `pos`.
template <class T, class Allocator>
void	myvector::_range_copy(iterator pos, iterator first, iterator last) {
	iterator	ptr = last;
	iterator	cur = pos + (last - first);

	try {
		for (; ptr != first; --ptr, --cur){
			if (DEBUG) std::cout << "range_copy: constructing " << *ptr << "at " << cur - this->begin() << std::endl;
            _alloc.construct(&*cur, *ptr);}
	}
	catch (...) {
		for (; ptr != last; ptr++, cur++)
			_alloc.destroy(&*cur);
		throw;
	}
	// size_type   to_copy = last - first;
	// size_type	copied = to_copy;

	// try {
	// 	for (; copied != 0; copied--)
	// 		std::cout << "range_copy: constructing content of " << 
	// 		first - this->begin() << " + copied (" << copied <<
	// 		") - 1 at " << pos - this->begin() << " + copied - 1\n";
    //         _alloc.construct(&*(pos + copied - 1), *(first + copied - 1));
	// }
	// catch (...) {
	// 	for (size_type i = 0; i < to_copy - copied; i++)
	// 		_alloc.destroy(&*(pos + i));
	// 	throw;
	// }
}

//	Internal fn called by fill constructor and insert (fill version).
//	Inserts `count` elements with value `value` at `pos`.
template <class T, class Allocator>
void	myvector::_fill_insert(iterator pos, size_type count, T const& value) {
	size_type constructed = 0;
	
	try {
		for (; constructed < count; constructed++) {
			_alloc.construct(&*(pos + constructed), value);
		}
	}
	catch (...) {
		for (size_type i = 0; i < constructed; i++)
			_alloc.destroy(&*(pos + i));
		throw;
	}
}

template <class T, class Allocator>
void	myvector::_expand_and_move(iterator pos, size_type count,
									size_type offset) {
	size_type   elems_after = this->end() - pos;

	if (DEBUG) std::cout << "expand_and_move: ";
	if (this->size() + count > this->capacity()){
		if (DEBUG) std::cout << "calling reserve with " << this->size() + count << std::endl;
		this->reserve(this->size() + count);}
	if (elems_after >= count){
		if (DEBUG) std::cout << "copying right elements\n";
		_range_copy(this->begin() + offset + count, pos, this->end());}
}

// } //	namespace ft

#endif