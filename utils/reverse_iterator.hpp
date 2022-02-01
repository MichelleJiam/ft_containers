/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reverse_iterator.hpp                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/26 21:11:29 by mjiam         #+#    #+#                 */
/*   Updated: 2022/02/01 21:51:53 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "./iterator_utils.hpp"

namespace   ft {
template <class Iterator>
class reverse_iterator
	:	public iterator<typename ft::iterator_traits<Iterator>::iterator_category,
						typename ft::iterator_traits<Iterator>::value_type,
						typename ft::iterator_traits<Iterator>::difference_type,
						typename ft::iterator_traits<Iterator>::pointer,
						typename ft::iterator_traits<Iterator>::reference> {
	private:
		typedef	ft::iterator_traits<Iterator>			_traits_type;

	public:
		typedef	Iterator								iterator_type;
		typedef typename _traits_type::difference_type	difference_type;
		typedef typename _traits_type::pointer			pointer;
		typedef typename _traits_type::reference		reference;

		// CONSTRUCTORS & DESTRUCTORS
		// default constructor
		reverse_iterator(void) : _current(NULL) {}
		// initialise constructor with a pointer
		explicit reverse_iterator(iterator_type x) : _current(x) {}
		// copy constructor
		template <class Iter>
		reverse_iterator(reverse_iterator<Iter> const& other)
			: _current(other.base()) {}
		// assignment operator
		template <class Iter>
		reverse_iterator&	operator=(reverse_iterator<Iter> const& other) {
			if (this != &other)
				this->_current = other._current;
			return *this;
		}
		// destructor
		~reverse_iterator(void) {}

		// returns _current, the iterator used for underlying work.
		iterator_type	base(void) const {
			return _current;
		}
		// returns a reference to the value at _current (if dereferenceable).
		// internally, function decreases a copy of base iterator and
		// returns result of dereferencing this.
		reference	operator*(void) const {
			Iterator	tmp = _current;
			return *--tmp;
		}
		// returns a pointer to the value at _current (if dereferenceable).
		pointer		operator->(void) const {
			Iterator	tmp = _current;
			--tmp;
			return tmp;
		}
		// returns value at _current + `n`
		reference	operator[](difference_type n) const {
			return *(*this + n);
		}
		// returns an iterator referring to _current - `n`.
		reverse_iterator	operator+(difference_type n) const {
			return reverse_iterator(_current - n);
		}
		// pre-decrements underlying iterator and returns *this (e.g. ++a).
		reverse_iterator&	operator++(void) {
			--_current;
			return *this;
		}
		// post-decrements underlying iterator and
		// returns iterator with previous value of *this (e.g. a++).
		reverse_iterator	operator++(int) {
			reverse_iterator	tmp = *this;
			--_current;
			return tmp;
		}
		// moves underlying iterator backward `n` steps.
		reverse_iterator&	operator+=(difference_type n) {
			_current -= n;
			return *this;
		}
		// returns an iterator referring to _current + `n`.
		reverse_iterator	operator-(difference_type n) const {
			return reverse_iterator(_current + n);
		}
		// pre-increments underlying iterator and returns *this (e.g. --a).
		reverse_iterator&	operator--(void) {
			++_current;
			return *this;
		}
		// post-increments underlying iterator and
		// returns iterator with previous value of *this (e.g. a--).
		reverse_iterator	operator--(int) {
			reverse_iterator	tmp = *this;
			++_current;
			return tmp;
		}
		// moves underlying iterator forward `n` steps.
		reverse_iterator&	operator-=(difference_type n) {
			_current += n;
			return *this;
		}

	protected:
		Iterator								_current;
};
} // namespace ft

#endif