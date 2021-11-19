/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   random_access_iterator.hpp                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/19 17:11:17 by mjiam         #+#    #+#                 */
/*   Updated: 2021/11/19 20:41:00 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "./iterator_utils.hpp"

namespace   ft {
template <class T>
class RandomAccessIterator
	: public ft::iterator<std::random_access_iterator_tag, T> {
	public:
		typedef 
} // namespace ft

#endif
