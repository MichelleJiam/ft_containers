/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   iterator_traits.hpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/14 18:01:43 by mjiam         #+#    #+#                 */
/*   Updated: 2021/10/14 20:44:23 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

namespace   ft {
// Traits class defining properties of iterators.
// Generic definition
template <class Iterator>
class iterator_traits {
	public:
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
};

// T* specialization
template <class T>
class iterator_traits<T*> {
	public:
		typedef std::ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::random_access_iterator_tag	iterator_category;
};

// const T* specialization
template <class T>
class iterator_traits<T const*> {
	public:
		typedef std::ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef T const*						pointer;
		typedef T const&						reference;
		typedef std::random_access_iterator_tag	iterator_category;
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
}

#endif