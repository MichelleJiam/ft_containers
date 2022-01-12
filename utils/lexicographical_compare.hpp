/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexicographical_compare.hpp                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/12 17:15:26 by mjiam         #+#    #+#                 */
/*   Updated: 2022/01/12 18:13:15 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICOGRAPHICAL_COMPARE_HPP
#define  LEXICOGRAPHICAL_COMPARE_HPP

namespace ft {
// default
// Elements are compared using operator<.
// Returns true if the range [first1,last1] is lexicographically less than 
// the range [first2,last2].
// Returns false otherwise, including when all elements are equivalent.
template <class InputIterator1, class InputIterator2>
bool	lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2) {
	for (; first1 != last1; ++first1, ++first2) {
		if (first2 == last2 || *first2 < *first1)
			return false;
		else if (*first1 < *first2)
			return true;
	}
	return first2 != last2;
}

// custom
// Elements are compared using given binary comparison function `comp`.
// `comp` function shall not modify any of its arguments.
// It can be either a function pointer or a function object.
template <class InputIterator1, class InputIterator2, class Compare>
bool	lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2,
								Compare comp) {
	for (; first1 != last1; ++first1, ++first2) {
		if (comp(*first1, *first2))
			return true;
		if (comp(*first2, *first1))
			return false;
	}
	return (first1 == last1 && first2 != last2);
}

} // namespace ft

#endif
