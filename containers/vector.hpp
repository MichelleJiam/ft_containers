/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 17:42:12 by mjiam         #+#    #+#                 */
/*   Updated: 2021/10/20 16:21:57 by mjiam         ########   odam.nl         */
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
		vector(vector const& other);
		// assignment operator
		vector&	operator=(vector const& other);

		// DESTRUCTOR
		~vector(void);

		// ITERATORS
		iterator				begin(void);
		const_iterator			begin(void) const;
		iterator				end(void);
		const_iterator			end(void) const;
		reverse_iterator		rbegin(void);
		const_reverse_iterator	rbegin(void) const;
		reverse_iterator		rend(void);
		const_reverse_iterator	rend(void) const;

		// CAPACITY FUNCTIONS
		// Returns current number of elements.
		size_type	size(void) const;

		// Returns max number of elements that the vector can hold.
		size_type	max_size(void) const;

		// Resizes container to contain n elements. If container size > `n`,
		// container is reduced to `n`. If `n` > size, container is 
		// expanded to size `n`. If `val` is specified, new elements 
		// are initialized as copies of `val`.
		void		resize (size_type n, value_type val = value_type());

		// Returns number of elements container can have before reallocation
		// is necessary (done automatically by container).
		// This is not necessarily equal to container size.
		size_type	capacity(void) const;

		// Returns whether vector is empty (= size is 0).
		bool		empty(void) const;

		// Requests enough space for at least `n` elements,
		// only reallocating if capacity is less than `n`.
		void		reserve (size_type n);

		// ELEMENT ACCESS FUNCTIONS
		reference		operator[] (size_type n);
		const_reference	operator[] (size_type n) const;
		reference		at (size_type n);
		const_reference	at (size_type n) const;
		reference		front(void);
		const_reference	front(void) const;
		reference		back(void);
		const_reference	back(void) const;

		// MODIFIERS
		// Replaces current contents with elements constructed from
		// elements in range [first,last] in the same order.
		template <class InputIterator>
  		void		assign (InputIterator first, InputIterator last);
		  
		// Replaces current contents with `n` elements, each initialized
		// to a copy of `val`.
		void		assign (size_type n, const value_type& val);

		// Adds new element to end of vector, copying/moving content of val
		// to it. Increases size by 1. Automatic reallocation is only triggered
		// if new size surpasses current capacity.
		void		push_back (const value_type& val);

		// Removes (and destroys) last element, reducing size by 1.
		void		pop_back(void);

		// Insert single element at specified `position`, increasing size by 1.
		iterator	insert (iterator position, const value_type& val);

		// Inserts `n` elements iniitalized to a copy of `val`.
		void		insert (iterator position, size_type n, const value_type& val);

		// Inserts elements in range [first,last] at `position` in same order.
		template <class InputIterator>
		void		insert (iterator position, InputIterator first, InputIterator last);

		// Erases (destroys) single element at `position`, reducing size by 1.
		iterator	erase (iterator position);

		// Erases a range of elements [first,last].
		iterator	erase (iterator first, iterator last);

		// Swaps content of container by content of `x` (same type).
		// Sizes may differ. All iterators, references, pointers remain valid.
		void		swap (vector& x);

		// Removes (destroys) all elements from vector, leaving size of 0.
		// Reallocation is not guaranteed and capacity is not guaranteed
		// to change.
		// Typical alternative that forces reallocation:
		//		vector<T>().swap(x);
		void		clear(void);

		// ALLOCATOR
		// Returns a copy of the allocator object associated with vector.
		allocator_type get_allocator() const;

	private:
		allocator_type	_alloc;
		size_type		_size;
		size_type		_capacity;
		pointer			_array;
};

// NON-MEMBER FUNCTION OVERLOADS
template <class T, class Alloc>
bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
template <class T, class Alloc>
bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
template <class T, class Alloc>
bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
template <class T, class Alloc>
bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
template <class T, class Alloc>
bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
template <class T, class Alloc>
bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

// Overload of member function `swap` hat improves its performance by
// mutually transferring ownership over their assets to the other container
// (i.e., the containers exchange references to their data, without actually
// performing any element copy or movement).
template <class T, class Alloc>
void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);

} // ft namespace

#include "vector.ipp"

#endif