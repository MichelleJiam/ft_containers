/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rb_node.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 19:46:06 by mjiam         #+#    #+#                 */
/*   Updated: 2022/02/17 19:46:59 by mjiam         ########   odam.nl         */
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

	rb_colour	colour;
	base_ptr	parent;
	base_ptr	left;
	base_ptr	right;

	// default constructor
	rb_node_base() : colour(RED), parent(NULL), left(NULL), right(NULL) {}

	// constructor with parent and children (for passing nil)
	rb_node_base(base_ptr parent, base_ptr child)
		: colour(RED), parent(parent), left(child), right(child) {}
	
	// constructor with colour (for passing BLACK with sentinel)
	rb_node_base(rb_colour col)
		: colour(col), parent(NULL), left(NULL), right(NULL) {}

	// copy constructor
	rb_node_base(rb_node_base const& other)
		:	colour(other.colour),
			parent(other.parent),
			left(other.left),
			right(other.right) {}

	~rb_node_base() {}
};

// derived class that knows Val, used for nodes with <key,t> data
template <class Val>
struct	rb_node : rb_node_base {
	typedef rb_node*	node_ptr;
	typedef Val			value_type;
	
	value_type	val; // Val is a pair<Key,T> object

	// default constructor
	rb_node() : rb_node_base() {}
	
	// constructor with val
	rb_node(Val const& val)
		: rb_node_base(), val(val) {}

	// constructor with val & parent & children (nil)
	rb_node(Val const& val, base_ptr parent, base_ptr child)
		: rb_node_base(parent, child), val(val) {}
		
	// rb_node(rb_node_base const& base) : rb_node_base(base) {}

	// copy constructor
	rb_node(rb_node const& other) : rb_node_base(other), val(other.val) {}

	~rb_node() {}
};
} // namespace ft

#endif
