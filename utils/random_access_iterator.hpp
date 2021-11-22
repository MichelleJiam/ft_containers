/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   random_access_iterator.hpp                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/19 17:11:17 by mjiam         #+#    #+#                 */
/*   Updated: 2021/11/22 16:56:31 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "./iterator_utils.hpp"

namespace   ft {
template <class T>
class RandomAccessIterator
	: public ft::iterator<ft::random_access_iterator_tag, T> {
	public:
		// CONSTRUCTORS & DESTRUCTORS
		// default constructor
		RandomAccessIterator(void) : _pointer(NULL) {}
		// constructor from a pointer
		RandomAccessIterator(pointer ptr) : _pointer(ptr) {}
		// copy constructor
		RandomAccessIterator(RandomAccessIterator const& other)
			: _pointer(other._pointer) {}
		// assignment operator
		RandomAccessIterator&	operator=(RandomAccessIterator const& other);
		// destructor
		~RandomAccessIterator(void);

		RandomAccessIterator&	operator+=(difference_type n);

	protected:
		pointer	_pointer;

} // namespace ft

#endif
