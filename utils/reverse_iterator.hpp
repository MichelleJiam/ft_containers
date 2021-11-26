/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reverse_iterator.hpp                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/26 21:11:29 by mjiam         #+#    #+#                 */
/*   Updated: 2021/11/26 21:29:15 by mjiam         ########   odam.nl         */
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
		typedef	ft::iterator_traits<Iterator>		_traits_type;
	
	public:
		typedef typename _traits_type::value_type			value_type;
		typedef typename _traits_type::difference_type		difference_type;
		typedef typename _traits_type::pointer				pointer;
		typedef typename _traits_type::reference			reference;
		typedef typename _traits_type::iterator_category	iterator_category;
		typedef	Iterator									iterator_type;

		// CONSTRUCTORS & DESTRUCTORS
		// default constructor
		reverse_iterator(void) : _current(NULL) {}
		// initialise constructor with a pointer
		explicit reverse_iterator(iterator_type it) : _current(it) {}
		// copy constructor
		reverse_iterator(reverse_iterator const& other)
			: _current(other._current) {}
		// assignment operator
		reverse_iterator&	operator=(reverse_iterator const& other) {
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

	protected:
		iterator_type    _current;
};
} // namespace ft

#endif