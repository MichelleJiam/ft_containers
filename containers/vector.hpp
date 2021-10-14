/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 17:42:12 by mjiam         #+#    #+#                 */
/*   Updated: 2021/10/14 20:59:27 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory> // allocator
// #include "../utils/iterator_traits.hpp"

namespace   ft {
template < class T, class Alloc = std::allocator<T> >
class vector {
	public:
		typedef T					value_type;
		typedef Alloc				allocator_type;
		typedef	std::ptrdiff_t		difference_type;
		typedef	std::size_t			size_type;
		typedef value_type&			reference;
		typedef value_type const&	const_reference;
		typedef value_type*			pointer;
		typedef value_type const*	const_pointer;
		typedef random_access_iterator<value_type>			iterator;
		typedef random_access_iterator<value_type const>	const_iterator;
		typedef reverse_iterator<iterator>					reverse_iterator;
		typedef reverse_iterator<const_iterator>			const_reverse_iterator;

		// CONSTRUCTORS & ASSIGNMENT OPERATORS
		// default: empty container
		explicit vector(allocator_type const& alloc = allocator_type());
		// fill: container with n elements, each a copy of val
		explicit vector(size_type n, value_type const& val = value_type(),
						allocator_type const& alloc = allocator_type());
		// range: container with first-last elements
		template <class InputIterator>
		vector(InputIterator first, InputIterator last,
				allocator_type const& alloc = allocator_type());
		// copy: container with copies of each element in x
		vector(vector const& x);
		// assignment operator
		vector&	operator=(vector const& x);

		// DESTRUCTOR
		~vector(void);

		// ITERATORS

		// CAPACITY FUNCTIONS

		// ELEMENT ACCESS FUNCTIONS

		// MODIFIERS

		// ALLOCATOR

	private:
		allocator_type	_alloc;
		pointer			_array;
		size_type		_size;
		size_type		_capacity;
};

// NON-MEMBER FUNCTION OVERLOADS


}

#include "vector.ipp"

#endif