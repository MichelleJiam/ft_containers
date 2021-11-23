/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   random_access_iterator.hpp                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/19 17:11:17 by mjiam         #+#    #+#                 */
/*   Updated: 2021/11/23 22:14:42 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "./iterator_utils.hpp"

namespace   ft {
template <class T>
class RandomAccessIterator
	: public ft::iterator<ft::random_access_iterator_tag, T> {
	private:
		typedef ft::iterator<ft::random_access_iterator_tag, T>	_it_type;
		
	public:
		typedef typename _it_type::difference_type	difference_type;
		typedef typename _it_type::pointer			pointer;
		typedef typename _it_type::reference		reference;

		// CONSTRUCTORS & DESTRUCTORS
		// default constructor
		RandomAccessIterator(void) : _current(NULL) {}
		// initialise constructor with a pointer
		RandomAccessIterator(pointer ptr) : _current(ptr) {}
		// copy constructor
		RandomAccessIterator(RandomAccessIterator const& other)
			: _current(other._current) {}
		// assignment operator
		RandomAccessIterator&	operator=(RandomAccessIterator const& other) {
			if (this != &other)
				this->_current = other._current;
			return *this;
		}
		// destructor
		~RandomAccessIterator(void) {}

		// returns _current, the iterator used for underlying work.
		pointer		base(void) const {
			return _current;
		}
		// returns a reference to the value at _current (if dereferenceable).
		reference	operator*(void) const {
			return *_current;
		}
		// returns a pointer to the value at _current (if dereferenceable).
		pointer		operator->(void) const {
			return _current;
		}
		// user-defined conversion function for const iterator
		operator	RandomAccessIterator<T const>() const {
			return RandomAccessIterator<T const>(this->_current);
		}
		// pre-increments underlying iterator and returns *this (e.g. ++a).
		RandomAccessIterator&	operator++(void) {
			++_current;
			return *this;
		}
		// post-increments underlying iterator and
		// returns iterator with previous value of *this (e.g. a++).
		RandomAccessIterator	operator++(int) {
			RandomAccessIterator	tmp = *this;
			++_current;
			return tmp;
		}
		// pre-decrements underlying iterator and returns *this (e.g. --a).
		RandomAccessIterator&	operator--(void) {
			--_current;
			return *this;
		}
		// post-decrements underlying iterator and
		// returns iterator with previous value of *this (e.g. a--).
		RandomAccessIterator	operator--(int) {
			RandomAccessIterator	tmp = *this;
			--_current;
			return tmp;
		}
		// returns an iterator referring to _current + `n`.
		RandomAccessIterator	operator+(difference_type n) const {
			return RandomAccessIterator(_current + n);
		}
		// moves underlying iterator forward `n` steps.
		RandomAccessIterator&	operator+=(difference_type n) {
			_current += n;
			return *this;
		}
		// returns an iterator referring to _current - `n`.
		RandomAccessIterator	operator-(difference_type n) const {
			return RandomAccessIterator(_current - n);
		}
		// moves underlying iterator backward `n` steps.
		RandomAccessIterator&	operator-=(difference_type n) {
			_current -= n;
			return *this;
		}
		// returns value at _current + `n`
		RandomAccessIterator&	operator[](difference_type n) const {
			return *(*this + n);
		}

		protected:
			pointer	_current;
	};

// NON-MEMBER FUNCTIONS
// returns distance in address between 2 iterators.
template <class T>
typename RandomAccessIterator<T>::difference_type operator-(
		RandomAccessIterator<T> const& lhs,
		RandomAccessIterator<T> const& rhs) {
	return rhs.base() - lhs.base();
}

// boolean comparison operators
template <class T>
bool	operator==(RandomAccessIterator<T> const& lhs,
					RandomAccessIterator<T> const& rhs) {
	return lhs.base() == rhs.base();
}

template <class T>
bool	operator!=(RandomAccessIterator<T> const& lhs,
					RandomAccessIterator<T> const& rhs) {
	return lhs.base() != rhs.base();
}

template <class T>
bool	operator<(RandomAccessIterator<T> const& lhs,
					RandomAccessIterator<T> const& rhs) {
	return lhs.base() < rhs.base();
}

template <class T>
bool	operator>(RandomAccessIterator<T> const& lhs,
					RandomAccessIterator<T> const& rhs) {
	return lhs.base() > rhs.base();
}

template <class T>
bool	operator<=(RandomAccessIterator<T> const& lhs,
					RandomAccessIterator<T> const& rhs) {
	return lhs.base() <= rhs.base();
}

template <class T>
bool	operator>=(RandomAccessIterator<T> const& lhs,
					RandomAccessIterator<T> const& rhs) {
	return lhs.base() >= rhs.base();
}

} // namespace ft

#endif
