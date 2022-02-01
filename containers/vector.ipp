/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.ipp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/12 19:09:49 by mjiam         #+#    #+#                 */
/*   Updated: 2022/02/01 21:54:39 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_IPP
# define VECTOR_IPP

#define DEBUG 0 // TODO: remove and all debug messages
#define myvector ft::vector<T,Allocator>

//	DEFAULT CONSTRUCTOR
template <class T, class Allocator>
myvector::vector(Allocator const& alloc)
		: _alloc(alloc), _size(0), _capacity(0), _array(NULL) {}

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
//	Also called if passing 2 integers as first 2 params, instead of fill cons.
//	Exceptions:
//	std::distance may throw if arithmetical operations performed 
//	on the iterators throw;
//	allocator::allocate & allocator:construct may throw bad_alloc.
template <class T, class Allocator>
template <class InputIterator>
myvector::vector(InputIterator first, InputIterator last,
				Allocator const& alloc)
		:	_alloc(alloc) {
	try {
		// checks if integral type received. If so, it's not an iterator.
		typedef typename ft::is_integral<InputIterator>::type	Integral;
		_range_dispatch(first, last, Integral());
	}
	catch (...) {
		_alloc.deallocate(_array, _size);
		throw;
	}
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
		_range_copy_backward(this->begin(), other.begin(), other.end());
	}
	catch (...) {
		_alloc.deallocate(_array, _size);
	}
}

//	ASSIGNMENT OPERATOR
//	Iterator invalidation: all
template <class T, class Allocator>
myvector&	myvector::operator=(vector const& other) {
	if (this != &other) {
		this->assign(other.begin(), other.end());
	}
	return *this;
}

//	DESTRUCTOR
template <class T, class Allocator>
myvector::~vector(void) {
	// this->clear();
	if (_array != NULL)
		_alloc.deallocate(_array, _capacity);
}

//	ITERATORS
//	Returns iterator pointing to first element in vector.
//	Iteration is done in ordinary element order.
template <class T, class Allocator>
typename myvector::iterator	myvector::begin(void) {
	return iterator(_array);
}

template <class T, class Allocator>
typename myvector::const_iterator	myvector::begin(void) const {
	return const_iterator(_array);
}

//	Returns iterator pointing to one past the last element in vector.
//	Iteration is done in ordinary element order.
template <class T, class Allocator>
typename myvector::iterator	myvector::end(void) {
	return iterator(_array + _size);
}

template <class T, class Allocator>
typename myvector::const_iterator	myvector::end(void) const {
	return const_iterator(_array + _size);
}

//	Returns reverse iterator pointing to last element in vector.
//	Iteration is done in reverse element order.
template <class T, class Allocator>
typename myvector::reverse_iterator	myvector::rbegin(void) {
	return reverse_iterator(end());
}

template <class T, class Allocator>
typename myvector::const_reverse_iterator	myvector::rbegin(void) const {
	return const_reverse_iterator(end());
}

//	Returns reverse iterator pointing to one before the first element in vector.
//	Iteration is done in reverse element order.
template <class T, class Allocator>
typename myvector::reverse_iterator	myvector::rend(void) {
	return reverse_iterator(begin());
}

template <class T, class Allocator>
typename myvector::const_reverse_iterator	myvector::rend(void) const {
	return const_reverse_iterator(begin());
}

//	Destroys current elements and replaces with newly constructed ones.
//	Automatically reallocates if new size > current capacity.
//	Iterator invalidation: all
template <class T, class Allocator>
void	myvector::assign(size_type count, const T& value) {
	_assign_fill(count, value);
}

template <class T, class Allocator>
template <class InputIterator>
void	myvector::assign(InputIterator first, InputIterator last,
							typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type*) {
	_assign_range(first, last);
}

template <class T, class Allocator>
typename myvector::allocator_type	myvector::get_allocator(void) const {
	return this->_alloc;
}

//	ELEMENT ACCESS FUNCTIONS
//	Returns element at index `pos`. Does not check for out of bounds.
template <class T, class Allocator>
typename myvector::reference	myvector::operator[](size_type pos) {
	return this->_array[pos];
}

template <class T, class Allocator>
typename myvector::const_reference	myvector::operator[](size_type pos) const {
	return this->_array[pos];
}

//	Provides safer data access than [] by checking parameter before access.
//	Exceptions: throws out_of_range if `pos` is invalid index.
template <class T, class Allocator>
typename myvector::reference	myvector::at(size_type pos) {
	if (pos >= this->_size)
		throw std::out_of_range("vector::at - index given is out of range");
	return this->_array[pos];
}

template <class T, class Allocator>
typename myvector::const_reference	myvector::at(size_type pos) const {
	if (pos >= this->_size)
		throw std::out_of_range("vector::at - index given is out of range");
	return this->_array[pos];
}

//	Returns reference to data at the first element of the vector.
//	Calling `front` on an empty container is undefined.
template <class T, class Allocator>
typename myvector::reference	myvector::front(void) {
	return *begin();
}

template <class T, class Allocator>
typename myvector::const_reference	myvector::front(void) const {
	return *begin();
}

//	Returns reference to data at the last element of the vector.
template <class T, class Allocator>
typename myvector::reference	myvector::back(void) {
	return *(end() - 1);
}

template <class T, class Allocator>
typename myvector::const_reference	myvector::back(void) const {
	return *(end() - 1);
}

//	CAPACITY FUNCTIONS
template <class T, class Allocator>
bool	myvector::empty(void) const {
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

//	Only reallocates storage, increasing capacity to `new_cap`,
//	if `new_cap` > current capacity. Has no effect on current size.
//	Iterator invalidation:	if reallocation happens, all invalidated.
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
		_reallocate(new_cap);
	}
}

template <class T, class Allocator>
typename myvector::size_type	myvector::capacity(void) const {
	return this->_capacity;
}

//	After this call, size() returns 0. Leaves capacity unchanged.
//	Iterator invalidation:	all refs, ptrs, and iterators referring to
//							contained elements.
//	No-throw guarantee
template <class T, class Allocator>
void	myvector::clear(void) {
	_destroy_until(this->begin(), this->end());
}

//	Because vectors use an array as their underlying storage, inserting elements
//	in positions other than the vector end causes the container to relocate 
//	all the elements after `pos` to their new positions.
//	Reallocates exponentially (N * 2) if current capacity is insufficient.
//	Iterator invalidation:	If reallocation happens, all invalidated.
//							If not, only after point of insertion.
//	Exceptions: strong guarantee if exception occurs.
template <class T, class Allocator>
typename myvector::iterator	myvector::insert(iterator pos, T const& value) {
	this->insert(pos, 1, value);
	return pos;
}

template <class T, class Allocator>
void	myvector::insert(iterator pos, size_type count, T const& value) {
	size_type		old_cap = this->capacity();
	iterator		saved_end = this->_array + _size;
	difference_type	offset = ft::distance(this->begin(), pos);

	try {
		// if (DEBUG) std::cout
		// 	// << "insert (fill): begin now " << *begin() << ", "
		// 	<< "calling _fill_insert with begin + " << offset << std::endl;
		if (this->capacity() - this->size() < count)
			_reallocate(this->size() ? this->size() * 2 : 1);
		if (pos != saved_end)
			// _range_copy(pos + count, pos, saved_end);
			_range_copy_backward(this->_array + offset + count, pos, saved_end);
		_fill_insert(this->_array + offset, count, value);
		if (DEBUG) std::cout << "inserting " << value << " at position " << 	
			offset << std::endl;
		this->_size += count;
		// for (size_type i = 0; i < _size; i++)
		// 	std::cout << _array[i] << " ";
		// std::cout << " | end of array\n";
	}
	catch (...) {
		if (old_cap < this->capacity())
			_alloc.deallocate(&*(this->_array + offset), this->capacity() - old_cap);
		throw;
	}
}

template <class T, class Allocator>
template <class InputIterator>
void	myvector::insert(iterator pos, InputIterator first, InputIterator last,
						typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type*) {
	size_type		old_cap = this->capacity();
	iterator		saved_end = this->_array + _size;
	difference_type	offset = ft::distance(this->begin(), pos);
	difference_type	count = ft::distance(first, last);

	try {
		if (this->capacity() - this->size() < (size_t)count)
			_reallocate(this->size() + count);
		if (pos != saved_end)
			_range_copy_backward(this->_array + offset + count, pos, saved_end);
		_range_copy_backward(pos, first, last);
		this->_size += count;
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
//	Iterator invalidation: erased elements and all following including end().
//	Exceptions: does not throw unless exception is thrown by the assignment
//				operator of T.
//	Returns:	iterator following last removed element.
//				If operation erased last element, end() is returned.
template <class T, class Allocator>
typename myvector::iterator	myvector::erase(iterator pos) {
	if (pos + 1 != this->end())
		_range_copy_forward(pos, pos + 1, end());
	this->_size -= 1;
	_alloc.destroy(&_array[_size - 1]);
	return pos;		
}

//	The iterator first does not need to be dereferenceable if first==last:
//	erasing an empty range is a no-op.
//	Invalid range causes undefined behaviour. Input is user's responsibility.
//	Returns: `first` if empty range or first==end().
template <class T, class Allocator>
typename myvector::iterator	myvector::erase(
		iterator first, iterator last) {
	if (first != last) {
		iterator	saved_end = this->_array + _size;
		size_type	elems_after = ft::distance(last, saved_end);
		if (last != saved_end)
			_range_copy_forward(first, last, saved_end);
		_destroy_until((first + elems_after), saved_end);
	}
	return first;
}

//	Iterator invalidation:	If reallocation happens, all invalidated.
//							If not, only end().
//	Exceptions: strong guarantee, fn has no effect.
//				May throw length_error if reallocation exceeds max_size.
template <class T, class Allocator>
void	myvector::push_back(T const& value) {
	if (DEBUG) std::cout << "push_back: calling insert with (" << 0 + _size << ", " << value << ")\n";
	insert(_array + _size, value);
}

//	Iterator invalidation:	element erased and end().
template <class T, class Allocator>
void	myvector::pop_back(void) {
	_alloc.destroy(&_array[_size - 1]);
	this->_size -= 1;
}

//	Changes only the number of elements in the container, not its capacity.
//	Iterator invalidation:	If reallocation happens, all invalidated.
//							If resizing to smaller, at point of destruction
//							including end().
//	Exceptions: throws length_error if resized above max_size.
//				Function has no effect then (strong guarantee).
template <class T, class Allocator>
void	myvector::resize(size_type count, T value) {
	if (count > this->max_size())
		throw std::length_error(
			"vector::resize - count exceeds vector max_size");
	else if (count < this->size())
		_destroy_until(_array + count, _array + _size);
	else
		this->insert(this->end(), count - this->_size, value);
}

//	Iterator invalidation: never
template <class T, class Allocator>
void	myvector::swap(vector& other) {	
	size_type	tmp_size = other._size;
	size_type	tmp_capacity = other._capacity;
	pointer		tmp_array = other._array;

	other._size = this->_size;
	other._capacity = this->_capacity;
	other._array = this->_array;

	this->_size = tmp_size;
	this->_capacity = tmp_capacity;
	this->_array = tmp_array;
}

//	Internal fn called by range constructor.
//	Integer specialization
template <class T, class Allocator>
template <class Integer>
void	myvector::_range_dispatch(Integer n, Integer value, ft::true_type) {
	size_type	count = static_cast<size_type>(n);
	_array = _alloc.allocate(count);
	_size = count;
	_capacity = _size;
	_fill_insert(this->begin(), count, value);
}

//	Iterator specialization
template <class T, class Allocator>
template <class InputIterator>
void	myvector::_range_dispatch(InputIterator first, InputIterator last, ft::false_type) {
	try {
		_size = ft::distance(first, last);
		_capacity = _size;
		_array = _alloc.allocate(_size);
		_range_copy_backward(this->begin(), first, last);
	}
	catch (...) {
		clear();
		throw;
	}
}

//	Intenral fn called by assign (fill).
template <class T, class Allocator>
void	myvector::_assign_fill(size_type count, const T& value) {
	this->clear();
	if (count == 0)
		return ;
	this->reserve(count);
	this->insert(begin(), count, value);
}

//	Internal fn called by assign (range).
template <class T, class Allocator>
template <class InputIterator>
void	myvector::_assign_range(InputIterator first, InputIterator last) {
	size_type	count = ft::distance(first, last);
	
	this->clear();
	if (count == 0)
		return ;
	this->reserve(count);
	this->insert(begin(), first, last);
}

//	Internal fn called by resize, erase.
//	Destroys elements from `old_end` to `new_end` and adjusts _size.
//	If `new_end` exceeds current end, doesn't do anything.
template <class T, class Allocator>
void	myvector::_destroy_until(iterator new_end, iterator old_end) {
	if (old_end - new_end) {
		while (old_end != new_end) {
			_alloc.destroy(&*old_end);
			old_end--;
			this->_size -= 1;
		}
	}
}

//	Internal fn called by erase.
//	Use for size-contracting operations.
//	Inserts elements in range [first,last] at `pos`.
template <class T, class Allocator>
template <class InputIterator>
void	myvector::_range_copy_forward(iterator pos, InputIterator first, InputIterator last) {
	while (first != last) {
		_alloc.construct(&*pos, *first);
		++pos;
		++first;
	}
}

//	Internal fn called by copy and range constructors, insert.
//	Use for size-expanding operations.
//	Inserts elements in range [first,last] at `pos`, starting from the last.
template <class T, class Allocator>
template <class InputIterator>
void	myvector::_range_copy_backward(iterator pos, InputIterator first, InputIterator last) {
	difference_type to_copy = ft::distance(first, last);
	
	for (; to_copy > 0; to_copy--) {
		if (DEBUG) std::cout << "range_copy: constructing " << *(first + to_copy - 1) << " at " << ft::distance(this->begin(), (pos + to_copy - 1)) << std::endl;
		_alloc.construct(&*(pos + to_copy - 1), *(first + to_copy - 1));
	}
}

//	Internal fn called by fill constructor and insert (fill version).
//	Inserts `count` elements with value `value` at `pos`.
template <class T, class Allocator>
void	myvector::_fill_insert(iterator pos, size_type count, T const& value) {
	size_type constructed = 0;
	
	try {
		for (; constructed < count; constructed++) {
			_alloc.construct(&*(pos + constructed), value);
			if (DEBUG) std::cout << "fill_insert: constructed " << *(pos + constructed) << std::endl;
		}
	}
	catch (...) {
		for (size_type i = 0; i < constructed; i++)
			_alloc.destroy(&*(pos + i));
		throw;
	}
}

//	Internal fn called by reserve and insert.
//	Reallocates array to `new_cap` size, copying over any existing elements.
template <class T, class Allocator>
void	myvector::_reallocate(size_type new_cap) {
	pointer		new_start = NULL;
	size_type	new_size = 0;
	
	try {
		new_start = _alloc.allocate(new_cap);
		for (; new_size < this->_size; new_size++)
			_alloc.construct(new_start + new_size, _array[new_size]);
		_alloc.deallocate(_array, _capacity);
		this->_array = new_start;
		this->_size = new_size;
		this->_capacity = new_cap;
	}
	catch (...) {
		if (new_start)
			_alloc.deallocate(new_start, new_cap);
	}
}

#endif
