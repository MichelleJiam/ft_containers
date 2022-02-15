/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rb_tree.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 16:47:52 by mjiam         #+#    #+#                 */
/*   Updated: 2022/02/15 17:23:12 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <cstddef> // ptrdiff_t, size_t

// #define NIL rb_tree->_nil

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

	// constructor with parent and children (for passing nil)
	rb_node_base(node_ptr parent, node_ptr child)
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
	
	static node_ptr	minimum(node_ptr nil, node_ptr start) {
		while (start->left != nil)
			start = start->left;
		return start;
	}

	static const_node_ptr	minimum(const_node_ptr nil, const_node_ptr start) {
		while (start->left != nil)
			start = start->left;
		return start;
	}

	static node_ptr	mastartimum(node_ptr nil, node_ptr start) {
		while (start->right != nil)
			start = start->right;
		return start;
	}

	static const_node_ptr	mastartimum(const_node_ptr nil, const_node_ptr start) {
		while (start->right != nil)
			start = start->right;
		return start;
	}
};

// derived class that knows Val
template <class Val>
struct	rb_node : rb_node_base {
	Val	val; // Val is a pair<Key,T> object

	// default constructor
	rb_node() : rb_node_base() {}
	
	// constructor with val
	rb_node(Val const& val)
		: rb_node_base(), val(val) {}

	// constructor with val & parent & children (nil)
	rb_node(Val const& val, rb_node_base* parent, rb_node_base* child)
		: rb_node_base(parent, child), val(val) {}
		
	// rb_node(rb_node_base const& base) : rb_node_base(base) {}

	// copy constructor
	rb_node(rb_node const& other) : rb_node_base(other), val(other.val) {}

	~rb_node() {}
};

// iterators
#include <functional> // TODO: remove
template <class Key, class Val, class Compare = std::less<Key>, // TODO: remove
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
		typedef Alloc				allocator_type;

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
		allocator_type		_alloc;
		base_ptr			_nil; // sentinel representing NULL
		base_ptr			_root; // root node
		size_type			_size;
		Compare				_key_compare;
	
	public:
	// Constructors & Destructor
		rb_tree(Compare const& comp = Compare(), Alloc const& alloc = Alloc()) // TODO: remove default args
			: _alloc(alloc), _size(0), _key_compare(comp) {
			_nil = _create_nil();
			_root = _nil;
		}

		rb_tree(rb_tree const& other) {
			_nil = _create_nil();
			*this = other;
		}

		~rb_tree() {
			_erase(_root);
		}

	// DEBUGGING - REMOVE
		void	debug_empty() {
			std::cout << "nil colour is: " << (_nil->colour == RED ? "red" : "black") << std::endl;
			std::cout << "size is: " << size() << std::endl;
			std::cout << "empty? " << std::boolalpha << empty() << std::endl;
		}

		void	debug_single() {
			std::cout << "size is: " << size() << std::endl;
			std::cout << "empty? " << std::boolalpha << empty() << std::endl;
			std::cout << "root colour is: " << (_root->colour == RED ? "red" : "black") << std::endl;
			std::cout << "root value: " << _get_val(_root).first << ", " << _get_val(_root).second << std::endl;
			std::cout << "root parent colour is " << (_root->parent->colour ? "black" : "red") << std::endl;
			std::cout << "root leftC colour is " << (_root->left->colour ? "black" : "red") << std::endl;
			std::cout << "root rightC colour is " << (_root->right->colour ? "black" : "red") << std::endl;
		}

		void	print_tree_helper(base_ptr root, std::string indent, bool last) {
			
			std::cout << indent;
			if (last) {
				std::cout << "R----";
				indent += "   ";
			}
			else {
				std::cout << "L----";
				indent += "|  ";
			}
			std::string sColour = root->colour ? "BLACK" : "RED";
			if (root != _nil) {
				std::cout << "[" << _get_val(root).first << ", "
					<< _get_val(root).second << "] " << "(" << sColour << ")";
				if (root->parent != _nil)
					std::cout << " | Parent is [" << _get_val(root->parent).first
						<< ", " << _get_val(root->parent).second << "]\n";
				else
					std::cout << " | Parent is NIL\n";
				print_tree_helper(root->left, indent, false);
				print_tree_helper(root->right, indent, true);
			}
			else
				std::cout << "NIL" << " (" << sColour << ")" << std::endl;
		}

		void	print_tree() {
			std::cout << "Tree size: " << size() << std::endl;
			// if (_root != _nil)
				print_tree_helper(_root, "", true);
			std::cout << std::endl;
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
			return _alloc.max_size();
		}

	// Modifiers
		void	insert(value_type const& val) {
			if (_root == _nil)
				_root = _create_node(val, _nil);
			else
				_root = _insert_at(_root, _nil, val);
			_size += 1;
		}

	private:
		// convenience functions
		value_type const&	_get_val(base_ptr node) {
			return static_cast<rb_node<Val>*>(node)->val;
		}

		key_type const&	_get_key(base_ptr node) {
			return static_cast<rb_node<Val>*>(node)->val.first;
		}
		
		base_ptr	_create_nil() {
			base_ptr tmp = _b_alloc.allocate(1);
			_b_alloc.construct(tmp, rb_node_base(BLACK));
			return tmp;
		}

		base_ptr	_create_node(value_type const& val, base_ptr parent) {
			node_ptr tmp = _n_alloc.allocate(1);
			_n_alloc.construct(tmp, rb_node<Val>(val)); 
			// std::cout << "_create_node: value key is " << tmp->value.first << std::endl;
			tmp->parent = parent; // TODO: inefficient? see if base constructor can be changed to do this
			tmp->left = _nil;
			tmp->right = _nil;
			return tmp;
		}

		// template <class T, class Alloc_T>
		// void	_drop_node(T& node_type, Alloc_T& alloc) { // templated version for passing base/node allocators
		void	_drop_node(base_ptr node) {
			_b_alloc.destroy(node);
			_b_alloc.deallocate(node, 1);
		}

		// erase without rebalancing
		void	_erase(base_ptr start) {
			while (start != _nil) {
				_erase(start->right);
				base_ptr next = start->left;
				_drop_node(start);
				start = next;
			}
		}

		base_ptr	_insert_at(base_ptr root, base_ptr parent, value_type const& val) {
			if (root == _nil)
				return _create_node(val, parent);
			if (_key_compare(val.first, _get_key(root)) == true) {
				root->left = _insert_at(root->left, root, val);
			}
			else {
				root->right = _insert_at(root->right, root, val);
			}
			return root;
		}


};
}

#endif
