/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pair.hpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/12 15:59:47 by mjiam         #+#    #+#                 */
/*   Updated: 2022/02/15 22:29:40 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
#define PAIR_HPP

// Struct holding two objects of arbitrary type.
namespace ft {
template <class T1, class T2>
struct pair {
	public:
		typedef	T1	first_type;
		typedef T2	second_type;

		T1	first;	// copy of the first object
		T2	second;	// copy of the second object

		// CONSTRUCTORS & DESTRUCTORS
		// default constructor
		pair(void) : first(), second() {}
		// initialise with two objects
		pair(T1 const& x, T2 const& y) : first(x), second(y) {}
		// templated copy constructor for pair class itself
		template <class U1, class U2>
		pair(pair<U1,U2> const& p) : first(p.first), second(p.second) {}
		// assignment operator
		pair& operator=(pair const& other) {
			if (this != &other) {
				first = other.first;
				second = other.second;
			}
			return *this;
		}
};

// NON-MEMBER FUNCTIONS
// Convenience wrapper for creating a pair from two objects.
// Returns newly-constructed pair<> object containing given values.
template <class T1, class T2>
pair<T1,T2> make_pair(T1 x, T2 y) {
	return pair<T1,T2>(x, y);
}

// Comparison operators
template< class T1, class T2 >
bool	operator==(ft::pair<T1,T2> const& lhs, ft::pair<T1,T2> const& rhs) {
	return (lhs.first == rhs.first && lhs.second == rhs.second);
}

template< class T1, class T2 >
bool	operator!=(ft::pair<T1,T2> const& lhs, ft::pair<T1,T2> const& rhs) {
	return !(lhs == rhs);
}

template< class T1, class T2 >
bool	operator<(ft::pair<T1,T2> const& lhs, ft::pair<T1,T2> const& rhs) {
	return (lhs.first < rhs.first
		|| (!(rhs.first < lhs.first) && lhs.second < rhs.second));
}

template< class T1, class T2 >
bool	operator<=(ft::pair<T1,T2> const& lhs, ft::pair<T1,T2> const& rhs) {
	return !(rhs < lhs);
}

template< class T1, class T2 >
bool	operator>(ft::pair<T1,T2> const& lhs, ft::pair<T1,T2> const& rhs) {
	return rhs < lhs;
}

template< class T1, class T2 >
bool	operator>=(ft::pair<T1,T2> const& lhs, ft::pair<T1,T2> const& rhs) {
	return !(lhs < rhs);
}

} // namespace ft

#endif
