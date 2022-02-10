/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rb_tree.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 16:47:52 by mjiam         #+#    #+#                 */
/*   Updated: 2022/02/10 19:11:55 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <cstddef> // ptrdiff_t, size_t

namespace   ft {
enum rb_colour {
	RED = false,
	BLACK = true
};

// base class that doesn't know about Val (user data)
// used for sentinal node to prevent unecessary memory usage
struct	rb_node_base {
	typedef rb_node_base*		node_ptr;
	typedef const rb_node_base*	const_node_ptr;

	rb_colour	colour;
	node_ptr	parent;
	node_ptr	left;
	node_ptr	right;

	rb_node_base();
	
	static node_ptr	min_node(node_ptr x) {
		while (x->left != NULL)
			x = x->left;
		return x;
	}

	static const_node_ptr	min_node(const_node_ptr x) {
		while (x->left != NULL)
			x = x->left;
		return x;
	}

	static node_ptr	max_node(node_ptr x) {
		while (x->right != NULL)
			x = x->right;
		return x;
	}

	static const_node_ptr	max_node(const_node_ptr x) {
		while (x->right != NULL)
			x = x->right;
		return x;
	}
};

// derived class that knows Val
template <class Val>
struct	rb_node : rb_node_base {
	Val	value_type; // Val is a pair<Key,T> object

	rb_node(Val val)
		: colour(RED), parent(NULL), left(NULL), right(NULL), value_type(val) {}

	rb_node(rb_node& other)
		:	colour(other.colour),
			parent(other.parent),
			left(other.left),
			right(other.right),
			value_type(other.val) {}

	~rb_node() {}
}

// iterators

// uses a single sentinel to represent NULL to simplify boundary conditions

template <class Key, class Val, class Compare, class Alloc>
class rb_tree {
	public:
		typedef Key					key_type;
		typedef Val					value_type;
		typedef value_type*			pointer;
		typedef const value_type*	const_pointer;
		typedef value_type&			reference;
		typedef const value_type&	const_reference;
		typedef std::size_t			size_type;
		typedef std::ptrdiff_t		difference_type;
		typedef Alloc				allocator_type;

	protected:
		// typedef rb_node<Val>		node_type;
		// typedef const rb_node<Val>	const_node_type;
		// typedef node_type*				node_ptr;
		// typedef const node_type*		const_node_ptr;
		typedef rb_node*			node_ptr;
		typedef rb_node_base*		base_ptr;
		typedef const rb_node*		const_node_ptr;

		base_ptr	nil; // sentinel representing NULL
		node_ptr	root; // root node
		size_type	size;
	
	private:
		typedef typename Alloc::template rebind<rb_node_base>::other
				_base_type_alloc;
		typedef typename Alloc::template rebind<rb_node>::other
				_node_type_alloc;
		
		_base_type_alloc	sentinel_alloc;
		_node_type_alloc	node_alloc;

		
		
	rb_tree() {

	}
	
};
}

#endif
