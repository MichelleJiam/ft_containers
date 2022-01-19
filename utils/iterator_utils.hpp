/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   iterator_utils.hpp                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/14 18:01:43 by mjiam         #+#    #+#                 */
/*   Updated: 2022/01/19 18:04:20 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_UTILS_HPP
# define ITERATOR_UTILS_HPP

#include <cstddef> // ptrdiff_t, size_t
#include <iterator> // iterator_tags

namespace   ft {
// Iterator tags
// These are empty types used to distinguish different iterators.
typedef std::input_iterator_tag input_iterator_tag;
typedef	std::output_iterator_tag output_iterator_tag;
typedef std::forward_iterator_tag forward_iterator_tag;
typedef std::bidirectional_iterator_tag bidirectional_iterator_tag;
typedef std::random_access_iterator_tag random_access_iterator_tag;

// Common iterator class defining nested typedefs which iterator classes
// can inherit to save work.
template <class Category, class T, class Distance = std::ptrdiff_t,
			class Pointer = T*, class Reference = T&>
class iterator {
	public:
	// category of the iterator. must be one of the iterator category tags.
	typedef Category	iterator_category;
	// type of the values obtained when dereferencing the iterator.
	typedef T			value_type;
	// type to identify distance between iterators
	typedef Distance	difference_type;
	// type representing a pointer-to-value_type
	typedef Pointer		pointer;
	// type representing a reference-to-value_type
	typedef Reference	reference;
};

// Traits class defining properties of iterators.
// Generic definition
template <class Iter>
struct iterator_traits {
	public:
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;
};

// T* specialization
template <class T>
struct iterator_traits<T*> {
	public:
		typedef std::ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef ft::random_access_iterator_tag	iterator_category;
};

// const T* specialization
template <class T>
struct iterator_traits<T const*> {
	public:
		typedef std::ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef T const*						pointer;
		typedef T const&						reference;
		typedef ft::random_access_iterator_tag	iterator_category;
};

template <class InputIterator>
typename iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last) {
		typename ft::iterator_traits<InputIterator>::difference_type res = 0;
		while (first != last) {
			first++;
			res++;
		}
		return res;
	}
} // namespace ft

#endif
