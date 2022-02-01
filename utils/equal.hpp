/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   equal.hpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 20:57:00 by mjiam         #+#    #+#                 */
/*   Updated: 2022/02/01 21:13:03 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EQUAL_HPP
#define EQUAL_HPP

// #include "../utils/iterator_utils.hpp"
// #include "../utils/random_access_iterator.hpp"
// #include "../utils/reverse_iterator.hpp"
#include "../utils/type_traits.hpp"

namespace ft {
template <class InputIterator1, class InputIterator2>
bool equal(InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2,
			typename ft::enable_if<!ft::is_integral<InputIterator1>::value>::type* = NULL,
			typename ft::enable_if<!ft::is_integral<InputIterator2>::value>::type* = NULL) {
	while (first1 != last1) {
		if (*first1 != *first2)
			return false;
		++first1;
		++first2;
	}
	return true;
}

template  <class InputIterator1, class InputIterator2, class BinaryPredicate>
bool equal(InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, BinaryPredicate pred,
			typename ft::enable_if<!ft::is_integral<InputIterator1>::value>::type* = NULL,
			typename ft::enable_if<!ft::is_integral<InputIterator2>::value>::type* = NULL) {
	while (first1 != last1) {
		if (!pred(*first1, *first2))
			return false;
		++first1;
		++first2;
	}
	return true;
}

} // namespace ft

#endif