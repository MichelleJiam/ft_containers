/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rb_node.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 19:46:06 by mjiam         #+#    #+#                 */
/*   Updated: 2022/04/08 14:45:47 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_NODE_HPP
#define RB_NODE_HPP

namespace   ft {
enum rb_colour {
	RED = false,
	BLACK = true
};

// base class that doesn't know about Val (user data)
// used for sentinal node to prevent unecessary memory usage
struct	rb_node_base {
	typedef rb_node_base*		base_ptr;
	typedef const rb_node_base*	const_base_ptr;

	base_ptr	parent;
	base_ptr	left;
	base_ptr	right;
	rb_colour	colour;

	// default constructor for sentinel
	rb_node_base() : parent(NULL), left(NULL), right(NULL), colour(BLACK) {}

	// constructor with parent and children (for passing nil)
	rb_node_base(base_ptr parent, base_ptr child)
		: parent(parent), left(child), right(child), colour(RED) {}
	
	// copy constructor
	rb_node_base(rb_node_base const& other)
		:	parent(other.parent),
			left(other.left),
			right(other.right),
			colour(other.colour) {}
};

// derived class that knows Val, used for nodes with <key,t> data
template <class Val>
struct	rb_node : rb_node_base {
	Val	val; // Val is a pair<Key,T> object

	// constructor with val & parent & children (nil)
	rb_node(Val const& val, base_ptr parent, base_ptr child)
		: rb_node_base(parent, child), val(val) {}
		
	rb_node(rb_node_base const& base) : rb_node_base(base) {}

	// copy constructor
	rb_node(rb_node const& other) : rb_node_base(other), val(other.val) {}
};
} // namespace ft

#endif
