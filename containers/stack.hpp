/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stack.hpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 14:30:57 by mjiam         #+#    #+#                 */
/*   Updated: 2022/02/02 14:39:31 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft {
template < class T, class Container = ft::vector<T> >
class stack {
	public:
		typedef T			value_type;
		typedef Container	container_type;
		typedef std::size_t	size_type;
	
	// CONSTRUCTORS & ASSIGNMENT OPERATORS
	// default & copy constructor
	// Copy-constructs the underlying container with contents of `cont`,
	// if any, otherwise it is an empty container.
	explicit stack(Container const& cont = Container());
	

	// DESTRUCTOR
	~stack(void);
};

} // namespace ft

#endif
