/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rb_tree.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 16:47:52 by mjiam         #+#    #+#                 */
/*   Updated: 2022/02/10 21:47:33 by mjiam         ########   odam.nl         */
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

	// default constructor
	rb_node_base() : colour(RED), parent(NULL), left(NULL), right(NULL) {}
	
	// constructor with colour given
	rb_node_base(rb_colour col)
		: colour(col), parent(NULL), left(NULL), right(NULL) {}

	// copy constructor
	rb_node_base(rb_node_base& other)
		:	colour(other.colour),
			parent(other.parent),
			left(other.left),
			right(other.right) {}

	~rb_node_base() {}
	
	static node_ptr	minimum(node_ptr nil, node_ptr x) {
		while (x->left != nil)
			x = x->left;
		return x;
	}

	static const_node_ptr	minimum(const_node_ptr nil, const_node_ptr x) {
		while (x->left != nil)
			x = x->left;
		return x;
	}

	static node_ptr	maximum(node_ptr nil, node_ptr x) {
		while (x->right != nil)
			x = x->right;
		return x;
	}

	static const_node_ptr	maximum(const_node_ptr nil, const_node_ptr x) {
		while (x->right != nil)
			x = x->right;
		return x;
	}
};

// derived class that knows Val
template <class Val>
struct	rb_node : rb_node_base {
	Val	value_type; // Val is a pair<Key,T> object

	// default constructor
	rb_node() : rb_node_base() {}
	
	// constructor with val
	rb_node(Val val)
		: rb_node_base(RED), value_type(val) {}

	// copy constructor
	rb_node(rb_node& other) : rb_node_base(other), value_type(other.val) {}

	~rb_node() {}
};

// iterators

// uses a single sentinel to represent NULL to simplify boundary conditions
#include <functional> // TODO: remove
template <class Key, class Val, class Compare  = std::less<Key>, // TODO: remove default for compare
			class Alloc = std::allocator<Val> >
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

	protected:
		typedef rb_node<Val>*			node_ptr;
		typedef rb_node_base*			base_ptr;
		typedef const rb_node<Val>*		const_node_ptr;
	
	private:
		typedef typename Alloc::template rebind<rb_node_base>::other
				_base_type_alloc;
		typedef typename Alloc::template rebind<rb_node<Val> >::other
				_node_type_alloc;
		
		_base_type_alloc	_b_alloc;
		_node_type_alloc	_n_alloc;
	
	public:
	// Constructors & Destructor
		rb_tree() : _root(NULL), _size(0), _key_compare() {
			_nil = _create_base();
			// _root = _create_node(NULL);
		}

		rb_tree(Compare const& comp)
			: _root(NULL), _size(0), _key_compare(comp) {
			_nil = _create_base();
		}

		rb_tree(rb_tree const& other) {
			_nil = _create_base();
			*this = other;
		}

		~rb_tree() {
			_erase(_nil, _b_alloc);
		}

	// Accessors
		Compare key_comp() const {
			return _key_compare;
		}

		bool	empty() const {
			return _size == 0;
		}

		size_type	size() const {
			return _size;
		}

		size_type	max_size() const {
			return _n_alloc.max_size();
		}

		// TODO: remove
		void	debug_empty() {
			std::cout << "nil colour is: " << (_nil->colour == RED ? "red" : "black") << std::endl;
			std::cout << "size is: " << size() << std::endl;
			std::cout << "empty? " << std::boolalpha << empty() << std::endl;
		}

	private:
		base_ptr	_nil; // sentinel representing NULL
		node_ptr	_root; // root node
		size_type	_size;
		Compare		_key_compare;
		
		base_ptr	_create_base() {
			base_ptr tmp = _b_alloc.allocate(1);
			_b_alloc.construct(tmp, BLACK);
			return tmp;
		}

		node_ptr	_create_node(value_type const& val) {
			node_ptr tmp = _n_alloc.allocate(1);
			_n_alloc.construct(tmp, rb_node<Val>(val));
			// tmp->parent = _nil; // TODO: inefficient? see if base constructor can be changed to do this
			// _set_ends_to_nil(tmp);
			return tmp;
		}

		template <class T, class R_Alloc>
		void	_erase(T& node_type, R_Alloc& alloc) {
			alloc.destroy(node_type);
			alloc.deallocate(node_type, 1);
		}

		void	_set_ends_to_nil(node_ptr node) {
			node->left = _nil;
			node->right = _nil;
		}
};
}

#endif
