/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rb_tree.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 16:47:52 by mjiam         #+#    #+#                 */
/*   Updated: 2022/02/09 18:41:11 by mjiam         ########   odam.nl         */
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

template <class Val>
struct	rb_tree_node {
	typedef rb_tree_node*		node_ptr;
	typedef const rb_tree_node*	const_node_ptr;
	typedef rb_tree_node		node_type;

	rb_colour	colour;
	node_ptr	parent;
	node_ptr	left;
	node_ptr	right;
	
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

// Helper type to manage default initialization of node count and header.
// struct	rb_tree_header {
// 	rb_tree_node	header;
// 	size_t			node_count;

// 	rb_tree_header() {
// 		header.colour = RED;
// 		_reset();
// 	}

// 	void	_move_data(rb_tree_header& from) {
// 		header.colour = from.header.colour;
// 		header.parent = from.header.parent;
// 		header.left = from.header.left;
// 		header.right = from.header.right;
// 		header.parent->parent = &header;
// 		node_count = from.node_count;

// 		from._reset();
// 	}

// 	void	_reset() {
// 		header.parent = NULL;
// 		header.left = &header;
// 		header.right = &header;
// 		node_count = 0;
// 	}
// };

// iterators

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
		typedef rb_tree_node<Val>		node_type;
		typedef const rb_tree_node<Val>	const_node_type;
		typedef node_type*				node_ptr;
		typedef const node_type*		const_node_ptr;

	private:
		typedef typename Alloc::template rebind<node_type>::other	_node_alloc;

	

};
}

#endif
