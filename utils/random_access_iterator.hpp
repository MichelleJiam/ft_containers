/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   random_access_iterator.hpp                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/19 17:11:17 by mjiam         #+#    #+#                 */
/*   Updated: 2022/04/05 20:41:49 by mjiam         ########   odam.nl         */
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

	// OPERATORS
		// returns a reference to the value at _current (if dereferenceable).
		reference	operator*(void) const {
			return *_current;
		}

		// returns a pointer to the value at _current (if dereferenceable).
		pointer		operator->(void) const {
			return _current;
		}

		// returns value at _current + `n`
		reference	operator[](difference_type n) const {
			return _current[n];
		}

		// user-defined conversion function for conversion to const iterator
		operator	random_access_iterator<T const>() const {
			return random_access_iterator<T const>(_current);
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

// op- must support mixed const/non-const iterator params
template <class TL, class TR>
typename random_access_iterator<TL>::difference_type operator-(
		random_access_iterator<TL> const& lhs,
		random_access_iterator<TR> const& rhs) {
	return lhs.base() - rhs.base();
}

template <class T>
random_access_iterator<T> operator+(
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

// for comparison between different typed iterators, i.e. const == non-const
template <class TL, class TR>
bool	operator==(random_access_iterator<TL> const& lhs,
					random_access_iterator<TR> const& rhs) {
	return lhs.base() == rhs.base();
}

template <class T>
bool	operator!=(random_access_iterator<T> const& lhs,
					random_access_iterator<T> const& rhs) {
	return lhs.base() != rhs.base();
}

// for const iterator != non-const
template <class TL, class TR>
bool	operator!=(random_access_iterator<TL> const& lhs,
					random_access_iterator<TR> const& rhs) {
	return lhs.base() != rhs.base();
}

template <class T>
bool	operator<(random_access_iterator<T> const& lhs,
					random_access_iterator<T> const& rhs) {
	return lhs.base() < rhs.base();
}

// for const iterator < non-const
template <class TL, class TR>
bool	operator<(random_access_iterator<TL> const& lhs,
					random_access_iterator<TR> const& rhs) {
	return lhs.base() < rhs.base();
}

template <class T>
bool	operator>(random_access_iterator<T> const& lhs,
					random_access_iterator<T> const& rhs) {
	return lhs.base() > rhs.base();
}

// for const iterator > non-const
template <class TL, class TR>
bool	operator>(random_access_iterator<TL> const& lhs,
					random_access_iterator<TR> const& rhs) {
	return lhs.base() > rhs.base();
}

template <class T>
bool	operator<=(random_access_iterator<T> const& lhs,
					random_access_iterator<T> const& rhs) {
	return lhs.base() <= rhs.base();
}

// for const iterator <= non-const
template <class TL, class TR>
bool	operator<=(random_access_iterator<TL> const& lhs,
					random_access_iterator<TR> const& rhs) {
	return lhs.base() <= rhs.base();
}

template <class T>
bool	operator>=(random_access_iterator<T> const& lhs,
					random_access_iterator<T> const& rhs) {
	return lhs.base() >= rhs.base();
}

// for const iterator >= non-const
template <class TL, class TR>
bool	operator>=(random_access_iterator<TL> const& lhs,
					random_access_iterator<TR> const& rhs) {
	return lhs.base() >= rhs.base();
}

} // namespace ft

#endif
