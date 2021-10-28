/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 17:42:12 by mjiam         #+#    #+#                 */
/*   Updated: 2021/10/28 17:47:38 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory> // allocator
// #include "../utils/iterator_traits.hpp"

// TODO: remove
#include <iterator>
//

namespace   ft {

template < class T, class Allocator = std::allocator<T> >
class vector {
	public:
		typedef T									value_type;
		typedef Allocator							allocator_type;
		typedef	std::ptrdiff_t						difference_type;
		typedef	std::size_t							size_type;
		typedef typename Allocator::reference		reference;
		typedef typename Allocator::const_reference	const_reference;
		typedef typename Allocator::pointer			pointer;
		typedef typename Allocator::const_pointer	const_pointer;
		typedef std::random_access_iterator<value_type>	iterator; // TODO: change to ft
		typedef std::random_access_iterator<value_type const>	const_iterator; // TODO: change to ft
		typedef std::reverse_iterator<iterator>	reverse_iterator;
		typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;

		// CONSTRUCTORS & ASSIGNMENT OPERATORS
		// default: empty container
		explicit vector(Allocator const& alloc);
		// fill: container with n elements, each a copy of val
		explicit vector(size_type count, T const& value = T(),
						Allocator const& alloc = Allocator());
		// range: container with first-last elements
		template <class InputIterator>
		vector(InputIterator first, InputIterator last,
				Allocator const& alloc = Allocator());
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

		// Replaces current contents with `n` elements, each initialized
		// to a copy of `val`.
		void		assign (size_type count, const T& value);

		// Replaces current contents with elements constructed from
		// elements in range [first,last] in the same order.
		template <class InputIterator>
  		void		assign (InputIterator first, InputIterator last);

		// Returns a copy of the allocator object associated with vector.
		allocator_type get_allocator() const;

		// ELEMENT ACCESS FUNCTIONS
		reference		operator[] (size_type pos);
		const_reference	operator[] (size_type pos) const;
		reference		at (size_type pos);
		const_reference	at (size_type pos) const;
		reference		front(void);
		const_reference	front(void) const;
		reference		back(void);
		const_reference	back(void) const;

		// CAPACITY FUNCTIONS
		// Returns whether vector is empty (= size is 0).
		bool		empty(void) const;

		// Returns current number of elements.
		size_type	size(void) const;

		// Returns max number of elements that the vector can hold.
		size_type	max_size(void) const;

		// Requests enough space for at least `n` elements,
		// only reallocating if capacity is less than `n`.
		void		reserve (size_type n);

		// Returns number of elements container can have before reallocation
		// is necessary (done automatically by container).
		// This is not necessarily equal to container size.
		size_type	capacity(void) const;

		// MODIFIERS
		// Removes (destroys) all elements from vector, leaving size of 0.
		// Reallocation is not guaranteed and capacity is not guaranteed
		// to change.
		// Typical alternative that forces reallocation:
		//		vector<T>().swap(x);
		void		clear(void);

		// Insert single element at specified `position`, increasing size by 1.
		iterator	insert (iterator position, const T& val);

		// Inserts `n` elements iniitalized to a copy of `val`.
		void		insert (iterator position, size_type n, const T& val);

		// Inserts elements in range [first,last] at `position` in same order.
		template <class InputIterator>
		void		insert (iterator position, InputIterator first, InputIterator last);

		// Erases (destroys) single element at `position`, reducing size by 1.
		iterator	erase (iterator position);

		// Erases a range of elements [first,last].
		iterator	erase (iterator first, iterator last);

		// Adds new element to end of vector, copying/moving content of val
		// to it. Increases size by 1. Automatic reallocation is only triggered
		// if new size surpasses current capacity.
		void		push_back (const T& val);

		// Removes (and destroys) last element, reducing size by 1.
		void		pop_back(void);

		// Resizes container to contain n elements. If container size > `n`,
		// container is reduced to `n`. If `n` > size, container is 
		// expanded to size `n`. If `val` is specified, new elements 
		// are initialized as copies of `val`.
		void		resize (size_type n, T val = T());

		// Swaps content of container by content of `x` (same type).
		// Sizes may differ. All iterators, references, pointers remain valid.
		void		swap (vector& x);

	private:
		allocator_type	_alloc;
		size_type		_size;
		size_type		_capacity;
		pointer			_array;
};

// NON-MEMBER FUNCTION OVERLOADS
template <class T, class Allocator>
bool operator== (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs);
template <class T, class Allocator>
bool operator!= (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs);
template <class T, class Allocator>
bool operator<  (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs);
template <class T, class Allocator>
bool operator<= (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs);
template <class T, class Allocator>
bool operator>  (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs);
template <class T, class Allocator>
bool operator>= (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs);

// Overload of member function `swap` hat improves its performance by
// mutually transferring ownership over their assets to the other container
// (i.e., the containers exchange references to their data, without actually
// performing any element copy or movement).
template <class T, class Allocator>
void swap (vector<T,Allocator>& x, vector<T,Allocator>& y);

} // ft namespace

#include "vector.ipp"

#endif