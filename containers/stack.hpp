/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stack.hpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 14:30:57 by mjiam         #+#    #+#                 */
/*   Updated: 2022/04/06 17:31:00 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft {
template < class T, class Container = ft::vector<T> >
class stack {
	public:
		typedef T									value_type;
		typedef Container							container_type;
		typedef std::size_t							size_type;
		typedef typename Container::reference		reference;
		typedef typename Container::const_reference	const_reference;
	
	// CONSTRUCTORS & ASSIGNMENT OPERATORS
		// default & copy constructor
		// Copy-constructs with contents of `cont`, if given,
		// otherwise constructs an empty container.
		explicit stack(Container const& cont = Container())
			: c(cont) {}
		
		// copy constructor taking another stack object
		// Copy-constructs with contents of other.c.
		stack(stack const& other) : c(other.c) {}

		// assignment operator
		stack& operator=(stack const& other) {
			if (this != &other)
				c = other.c;
			return *this;
		}
	
	// DESTRUCTOR
		~stack() {}

	// ELEMENT ACCESS FUNCTIONS
		// Returns top most element in container.
		reference		top(void) {
			return c.back();
		}

		const_reference	top(void) const {
			return c.back();
		}

	// CAPACITY FUNCTIONS
		// Checks if container has no elements.
		bool	empty(void) const {
			return c.empty();
		}

		// Returns number of elements in container.
		size_type	size(void) const {
			return c.size();
		}

	// MODIFIERS
		// Adds given element to top of the stack.
		void	push(value_type const& value) {
			c.push_back(value);
		}

		// Removes top element.
		void	pop(void) {
			c.pop_back();
		}

	// Friend declarations for accessing protected `c` container attribute.
	template <class T1, class Container1>
	friend bool operator==(stack<T1,Container1> const& lhs,
							stack<T1,Container1> const& rhs);

	template <class T1, class Container1>
	friend bool operator<(stack<T1,Container1> const& lhs,
							stack<T1,Container1> const& rhs);

	protected:
		Container			c;
};

// NON-MEMBER FUNCTION OVERLOADS
// Equality comparison
template <class T, class Container>
bool operator==(stack<T,Container> const& lhs, stack<T,Container> const& rhs) {
	return (lhs.c == rhs.c);
}

template <class T, class Container>
bool operator!=(stack<T,Container> const& lhs, stack<T,Container> const& rhs) {
	return !(lhs == rhs);
}

template <class T, class Container>
bool operator<(stack<T,Container> const& lhs, stack<T,Container> const& rhs) {
	return (lhs.c < rhs.c);
}

template <class T, class Container>
bool operator<=(stack<T,Container> const& lhs, stack<T,Container> const& rhs) {
	return !(rhs < lhs);
}

template <class T, class Container>
bool operator>(stack<T,Container> const& lhs, stack<T,Container> const& rhs) {
	return rhs < lhs;
}

template <class T, class Container>
bool operator>=(stack<T,Container> const& lhs, stack<T,Container> const& rhs) {
	return !(lhs < rhs);
}

} // namespace ft

#endif
