/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 17:42:12 by mjiam         #+#    #+#                 */
/*   Updated: 2022/01/20 16:11:10 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory> // allocator
#include <cstddef> // ptrdiff_t, size_t
// #include <algorithm> // fill
#include "../utils/iterator_utils.hpp"
#include "../utils/random_access_iterator.hpp"
#include "../utils/type_traits.hpp"

// TODO: remove
#include <iterator>
#include <vector>
//

namespace   ft {
template < class T, class Allocator = std::allocator<T> >
class vector : public std::vector<T, Allocator> {
	public:
		typedef T									value_type;
		typedef Allocator							allocator_type;
		typedef	std::ptrdiff_t						difference_type;
		typedef	std::size_t							size_type;
		typedef typename Allocator::reference		reference;
		typedef typename Allocator::const_reference	const_reference;
		typedef typename Allocator::pointer			pointer;
		typedef typename Allocator::const_pointer	const_pointer;
		typedef ft::random_access_iterator<value_type>		iterator;
		typedef ft::random_access_iterator<value_type const>	const_iterator;
		typedef std::reverse_iterator<iterator>	reverse_iterator; // TODO: change to ft
		typedef std::reverse_iterator<const_iterator>	const_reverse_iterator; // TODO: change to ft

		// CONSTRUCTORS & ASSIGNMENT OPERATORS
		// default: empty container
		explicit vector(Allocator const& alloc = Allocator());
		// fill: container with `count` elements, each a copy of `value`
		explicit vector(size_type count, T const& value = T(),
						Allocator const& alloc = Allocator());
		// range: container with first-last elements
		template <class InputIterator> //, typename std::iterator_traits<InputIterator>::value_type> // TODO: uncomment
		vector(InputIterator first, InputIterator last,
				Allocator const& alloc = Allocator());
				// typename ft::iterator_traits<InputIterator>::type* = NULL);
				// typename std::iterator_traits<InputIterator>::type* = NULL); // TODO: change to ft::
		// copy: container with copies of each element in `other`
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
		reverse_iterator		rbegin(void){return std::vector<T,Allocator>::rbegin();}
		const_reverse_iterator	rbegin(void) const{return std::vector<T,Allocator>::rbegin();}
		reverse_iterator		rend(void){return std::vector<T,Allocator>::rend();}
		const_reverse_iterator	rend(void) const{return std::vector<T,Allocator>::rend();}

		// Replaces current contents with `count` elements, each initialized
		// to a copy of `value`.
		void	assign(size_type count, T const& value);

		// Replaces current contents with elements constructed from
		// elements in range [first,last] in the same order.
		template <class InputIterator>
  		void	assign(InputIterator first, InputIterator last,
		  				typename std::iterator_traits<InputIterator>::type* = NULL); // TODO: change to ft::

		// Returns a copy of the allocator object associated with vector.
		allocator_type	get_allocator(void) const;

		// ELEMENT ACCESS FUNCTIONS
		reference		operator[](size_type pos);
		// const_reference	operator[](size_type pos) const;
		// reference		at(size_type pos);
		// const_reference	at(size_type pos) const;
		// reference		front(void);
		// const_reference	front(void) const;
		// reference		back(void);
		// const_reference	back(void) const;

		// CAPACITY FUNCTIONS
		// Returns whether vector is empty (= size is 0).
		bool	empty(void) const;

		// Returns current number of elements.
		size_type	size(void) const;

		// Returns max number of elements that the vector can hold.
		size_type	max_size(void) const;

		// Requests enough space for at least `new_cap` elements,
		// only reallocating if capacity is less than `new_cap`.
		void	reserve(size_type new_cap);

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
		void	clear(void);

		// Insert single element at specified `pos`, increasing size by 1.
		iterator	insert(iterator pos, T const& value);

		// Inserts `count` elements initialized to a copy of `value`.
		void	insert(iterator pos, size_type count, T const& value);

		// Inserts elements in range [first,last] at `pos` in same order.
		// template <class InputIterator>
		// void	insert(iterator pos, InputIterator first, InputIterator last);
		// 				// typename std::iterator_traits<InputIterator>::type* = NULL); // TODO: change to ft::

		// Erases (destroys) single element at `pos`, reducing size by 1.
		iterator	erase(iterator pos);

		// Erases a range of elements [first,last].
		iterator	erase(iterator first, iterator last);

		// Adds new element to end of vector, copying/moving content of val
		// to it. Increases size by 1. Automatic reallocation is only triggered
		// if new size surpasses current capacity.
		void	push_back(T const& value);

		// Removes (and destroys) last element, reducing size by 1.
		void	pop_back(void);

		// Resizes container to contain n elements. 
		// If container size > `count`, container is reduced to `count`.
		// If `count` > size, container is expanded to size `count`.
		// If `value` is specified, new elements are initialized
		// as copies of `value`.
		void	resize(size_type count, T value = T());

		// Swaps content of container by content of `other` (same type).
		// Sizes may differ. All iterators, references, pointers remain valid.
		void	swap(vector& other);

	private:
		allocator_type	_alloc;
		size_type		_size;
		size_type		_capacity;
		pointer			_array;

		template <class Integer>
		void	_range_construct(Integer n, Integer value, std::true_type);
		template <class InputIterator>
		void	_range_construct(InputIterator first, InputIterator last, std::false_type);
		void	_destroy_until(iterator new_end, iterator old_end);
		template <class InputIterator>
		void	_range_copy(iterator start, InputIterator first, InputIterator last);
		void	_fill_insert(iterator pos, size_type count, T const& value);
		// void	_expand_and_move(iterator pos, size_type count, size_type offset);
		void	_reallocate(size_type new_size);
};


// NON-MEMBER FUNCTION OVERLOADS
// template <class T, class Allocator>
// bool operator==(vector<T,Allocator> const& lhs,vector<T,Allocator> const& rhs);
// template <class T, class Allocator>
// bool operator!=(vector<T,Allocator> const& lhs, vector<T,Allocator> const& rhs);
// template <class T, class Allocator>
// bool operator<(vector<T,Allocator> const& lhs, vector<T,Allocator> const& rhs);
// template <class T, class Allocator>
// bool operator<=(vector<T,Allocator> const& lhs, vector<T,Allocator> const& rhs);
// template <class T, class Allocator>
// bool operator>(vector<T,Allocator> const& lhs, vector<T,Allocator> const& rhs);
// template <class T, class Allocator>
// bool operator>=(vector<T,Allocator> const& lhs, vector<T,Allocator> const& rhs);

// // Overload of member function `swap` that improves its performance by
// // mutually transferring ownership over their assets to the other container
// // (i.e., the containers exchange references to their data, without actually
// // performing any element copy or movement).
// template <class T, class Allocator>
// void swap(vector<T,Allocator>& x, vector<T,Allocator>& y);

} // namespace ft

#include "vector.ipp"
#endif