/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   random_access_iterator.hpp                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/19 17:11:17 by mjiam         #+#    #+#                 */
/*   Updated: 2022/03/31 18:13:15 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "iterator_utils.hpp"

namespace   ft {
template <class T>
class random_access_iterator
	: public ft::iterator<ft::random_access_iterator_tag, T> {
	private:
		typedef ft::iterator<ft::random_access_iterator_tag, T>	_it_type;
		
	public:
		typedef typename _it_type::difference_type	difference_type;
		typedef typename _it_type::pointer			pointer;
		typedef typename _it_type::reference		reference;

		// CONSTRUCTORS & DESTRUCTORS
		// default constructor
		random_access_iterator(void) : _current(NULL) {}
		// initialise constructor with a pointer
		random_access_iterator(pointer ptr) : _current(ptr) {}
		// copy constructor
		random_access_iterator(random_access_iterator const& other)
			: _current(other._current) {}
		// assignment operator
		random_access_iterator&	operator=(random_access_iterator const& other) {
			if (this != &other)
				this->_current = other._current;
			return *this;
		}
		// destructor
		~random_access_iterator(void) {}

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
		// returns value at _current + `n`
		random_access_iterator&	operator[](difference_type n) const {
			return *(*this + n);
		}
		// user-defined conversion function for const iterator
		operator	random_access_iterator<T const>() const {
			return random_access_iterator<T const>(this->_current);
		}
		// returns an iterator referring to _current + `n`.
		random_access_iterator	operator+(difference_type n) const {
			return random_access_iterator(_current + n);
		}
		// pre-increments underlying iterator and returns *this (e.g. ++a).
		random_access_iterator&	operator++(void) {
			++_current;
			return *this;
		}
		// post-increments underlying iterator and
		// returns iterator with previous value of *this (e.g. a++).
		random_access_iterator	operator++(int) {
			random_access_iterator	tmp = *this;
			++_current;
			return tmp;
		}
		// moves underlying iterator forward `n` steps.
		random_access_iterator&	operator+=(difference_type n) {
			_current += n;
			return *this;
		}
		// returns an iterator referring to _current - `n`.
		random_access_iterator	operator-(difference_type n) const {
			return random_access_iterator(_current - n);
		}
		// pre-decrements underlying iterator and returns *this (e.g. --a).
		random_access_iterator&	operator--(void) {
			--_current;
			return *this;
		}
		// post-decrements underlying iterator and
		// returns iterator with previous value of *this (e.g. a--).
		random_access_iterator	operator--(int) {
			random_access_iterator	tmp = *this;
			--_current;
			return tmp;
		}
		// moves underlying iterator backward `n` steps.
		random_access_iterator&	operator-=(difference_type n) {
			_current -= n;
			return *this;
		}

		protected:
			pointer	_current;
};

// NON-MEMBER FUNCTIONS
// returns distance in address between 2 iterators.
template <class T>
typename random_access_iterator<T>::difference_type operator-(
		random_access_iterator<T> const& lhs,
		random_access_iterator<T> const& rhs) {
	return lhs.base() - rhs.base();
}

template <class T>
typename random_access_iterator<T>::difference_type operator+(
		typename random_access_iterator<T>::difference_type n,
		random_access_iterator<T> const& i) {
	return random_access_iterator<T>(i.base() + n);
}

// boolean comparison operators
template <class T>
bool	operator==(random_access_iterator<T> const& lhs,
					random_access_iterator<T> const& rhs) {
	return lhs.base() == rhs.base();
}

template <class T>
bool	operator!=(random_access_iterator<T> const& lhs,
					random_access_iterator<T> const& rhs) {
	return lhs.base() != rhs.base();
}

template <class T>
bool	operator<(random_access_iterator<T> const& lhs,
					random_access_iterator<T> const& rhs) {
	return lhs.base() < rhs.base();
}

template <class T>
bool	operator>(random_access_iterator<T> const& lhs,
					random_access_iterator<T> const& rhs) {
	return lhs.base() > rhs.base();
}

template <class T>
bool	operator<=(random_access_iterator<T> const& lhs,
					random_access_iterator<T> const& rhs) {
	return lhs.base() <= rhs.base();
}

template <class T>
bool	operator>=(random_access_iterator<T> const& lhs,
					random_access_iterator<T> const& rhs) {
	return lhs.base() >= rhs.base();
}

} // namespace ft

#endif
