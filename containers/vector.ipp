/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.ipp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/12 19:09:49 by mjiam         #+#    #+#                 */
/*   Updated: 2021/10/14 21:00:38 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// default constructor
template <class T, class Alloc>
ft::vector<T,Alloc>::vector(allocator_type const& alloc)
		: _alloc(alloc), _array(NULL), _size(0), _capacity(0) {
}

// fill constructor
template <class T, class Alloc>
ft::vector<T,Alloc>::vector(size_type n, value_type const& val,
							allocator_type const& alloc)
		: _alloc(alloc), _array(alloc.allocate(n)), _size(n), _capacity(n) {
	try {
		for (size_type i = 0; i < n; i++) {
			_alloc.construct(&_array[i], val);
		}
	}
	catch (...) {
		_alloc.deallocate(_array, n);
		throw;
	}
}

// range constructor
template <class T, class Alloc>
template <class InputIterator>
ft::vector<T,Alloc>::vector(InputIterator first, InputIterator last,
							allocator_type const& alloc)
		:	_alloc(alloc),
			_size = std::distance(first, last),
			_array = alloc.allocate(_size),
			_capacity = _size {
	try {
		for (size_type i = 0; i < _size; i++) {
			_alloc.construct(&_array[i], *(first + i));
		}
	}
	catch (...) {
		_alloc.deallocate(_array, _size);
		throw;
	}
}
