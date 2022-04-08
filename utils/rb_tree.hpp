/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rb_tree.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 16:47:52 by mjiam         #+#    #+#                 */
/*   Updated: 2022/04/08 17:49:04 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <cstddef> // ptrdiff_t, size_t
#include <memory> // allocator
#include <utility> // swap
#include "rb_node.hpp"
#include "rb_iterator.hpp"
#include "equal.hpp"
#include "lexicographical_compare.hpp"
#include "reverse_iterator.hpp"
#include "pair.hpp"

namespace ft {
template <class Key, class Val, class Compare,
			class Alloc = std::allocator<Val> >
class rb_tree {
	public:
		typedef Key						key_type;
		typedef Val						value_type;
		typedef value_type*				pointer;
		typedef const value_type*		const_pointer;
		typedef value_type&				reference;
		typedef const value_type&		const_reference;
		typedef std::size_t				size_type;
		typedef std::ptrdiff_t			difference_type;
		typedef Alloc					allocator_type;
		
		typedef rb_iterator<value_type>					iterator;
		typedef rb_iterator<value_type const>			const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	protected:
		typedef rb_node<Val>*			node_ptr;
		typedef rb_node_base*			base_ptr;
		typedef const rb_node<Val>*		const_node_ptr;
		typedef rb_node_base&			base_ref;
	
	private:
		typedef typename Alloc::template rebind<rb_node_base>::other
				_base_type_alloc;
		typedef typename Alloc::template rebind<rb_node<Val> >::other
				_node_type_alloc;
		
		allocator_type		_alloc;
		_base_type_alloc	_b_alloc;
		_node_type_alloc	_n_alloc;
		base_ptr			_nil; // sentinel representing NULL
		base_ptr			_root; // root node
		size_type			_size;
		Compare				_key_compare;
	
	public:
	// Constructors & Destructor
		rb_tree(Compare const& comp, Alloc const& alloc)
			:	_alloc(alloc),
				_b_alloc(alloc),
				_n_alloc(alloc),
				_size(0),
				_key_compare(comp) {
			_nil = _create_nil();
			_root = _nil;
		}

		rb_tree(rb_tree const& other)
			:	_alloc(other._alloc),
				_b_alloc(other._alloc),
				_n_alloc(other._alloc),
				_key_compare(other._key_compare) {
			_nil = _create_nil();
			_root = _nil;
			*this = other;
		}

		rb_tree&	operator=(rb_tree const& other) {
			if (this != &other) {
				if (!empty())
					clear();
				_key_compare = other._key_compare;
				if (other._root != _nil)
					insert(other.begin(), other.end());
			}
			return *this;
		}

		~rb_tree() {
			if (_size > 0)
				clear();
			_drop_node(_nil);
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
			if (_root != _nil)
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
			else {
				std::cout << "NIL" << " (" << sColour << ") ";
				std::cout << "Parent is ";
				if (root->parent == NULL) std::cout << "NULL";
				else if (root->parent == _nil) std::cout << "NIL";
				else std::cout << _get_val(root->parent).first
						<< ", " << _get_val(root->parent).second;
				std::cout << " | LChild is ";
				if (root->left == NULL) std::cout << "NULL\n";
				else if (root->left == _nil) std::cout << "NIL\n";
				else std::cout << _get_val(root->left).first
						<< ", " << _get_val(root->left).second << "\n";
			}
		}

		void	print_tree() {
			std::cout << "Tree size: " << size() << std::endl;
			print_tree_helper(_root, "", true);
			std::cout << std::endl;
		}

	// Allocator
		allocator_type	get_allocator() const {
			return _alloc;
		}
	
	// Accessors
		Compare key_comp() const {
			return _key_compare;
		}

		iterator	begin() {
			return iterator(_find_min(_root));
		}

		const_iterator	begin() const {
			return const_iterator(_find_min(_root));
		}

		iterator	end() {
			return iterator(_nil);
		}

		const_iterator	end() const {
			return const_iterator(_nil);
		}

		reverse_iterator	rbegin() {
			return reverse_iterator(end());
		}

		const_reverse_iterator	rbegin() const {
			return const_reverse_iterator(end());
		}

		reverse_iterator	rend() {
			return reverse_iterator(begin());
		}

		const_reverse_iterator	rend() const {
			return const_reverse_iterator(begin());
		}

		bool	empty() const {
			return (_size == 0);
		}

		size_type	size() const {
			return _size;
		}

		size_type	max_size() const {
			return _n_alloc.max_size();
		}

	// Modifiers
		void	clear() {
			_erase_from(_root);
			_nullify_root();
		}

		// single
		iterator	insert(value_type const& val) {
			base_ptr search = _search_by_key(val.first);
			if (search == _nil) {
				base_ptr inserted = _insert_at(_nil, val);
				_size += 1;
				return iterator(inserted);
			}
			else
				return iterator(search);
		}

		// with position hint
		iterator	insert(iterator position, value_type const& val) {
			(void)position;
			return insert(val);
		}

		// range
		template <class InputIterator>
		void	insert(InputIterator first, InputIterator last) {
			while (first != last) {
				insert(*first);
				++first;
			}
		}

		// erase element at `position`
		void	erase(iterator position) {
			if (position == end() || position.base() == NULL)
				return ;
			_delete_node(position.base());
		}

		// erase element with given key
		size_type	erase(key_type const& key) {
			return _delete_node(_search_by_key(key));
		}

		// erase range
		void	erase(iterator first, iterator last) {
			if (first == begin() && last == end())
				clear();
			else {
				while (first != last)
					erase(first++);
			}
		}

		void	swap(rb_tree& other) {
			std::swap(_root, other._root);
			std::swap(_nil, other._nil);
			std::swap(_size, other._size);
			std::swap(_key_compare, other._key_compare);
			std::swap(_n_alloc, other._n_alloc);
		}

	// Set ops
		iterator	find(key_type const& key) {
			iterator found(_search_by_key(key));
			return found;
		}

		const_iterator	find(key_type const& key) const {
			const_iterator found(_search_by_key(key));
			return found;
		}

		size_type	count(key_type const& key) const {
			return _search_by_key(key) == _nil ? 0 : 1;
		}

		iterator	lower_bound(key_type const& key) {
			return _lower_bound(key);
		}

		const_iterator	lower_bound(key_type const& key) const {
			return _lower_bound(key);
		}

		iterator	upper_bound(key_type const& key) {
			return _upper_bound(key);
		}

		const_iterator	upper_bound(key_type const& key) const {
			return _upper_bound(key);
		}

		pair<iterator, iterator>	equal_range(key_type const& key) {
			return ft::make_pair<iterator, iterator>(
					lower_bound(key), upper_bound(key));
		}

		pair<const_iterator, const_iterator>	equal_range(key_type const& key) const {
			return ft::make_pair<const_iterator, const_iterator>(
					lower_bound(key), upper_bound(key));
		}

	// Relational ops
		friend bool operator==(rb_tree const& lhs, rb_tree const& rhs) {
			return (lhs.size() == rhs.size()
					&& ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		}

		friend bool operator<(rb_tree const& lhs, rb_tree const& rhs) {
			return ft::lexicographical_compare(lhs.begin(), lhs.end(),
												rhs.begin(), rhs.end());
		}

	private:
		// UTILITIES
		// does not check if node is _nil/NULL before casting.
		// caller's responsibility to check before calling.
		reference	_get_val(base_ptr node) const {
			return static_cast<node_ptr>(node)->val;
		}
		
		// does not check if node is _nil/NULL before casting.
		// caller's responsibility to check before calling.
		key_type const&	_get_key(base_ptr node) const {
			return static_cast<node_ptr>(node)->val.first;
		}

		base_ptr	_find_min(base_ptr start) const {
			while (start != _nil && start->left != _nil)
				start = start->left;
			return start;
		}

		base_ptr	_find_max(base_ptr start) const {
			while (start != _nil && start->right != _nil)
				start = start->right;
			return start;
		}
		
		// used by _delete_node
		base_ptr	_search_by_key(key_type const& key) const {
			base_ptr	tmp = _root;

			while (tmp != _nil) {
				if (_get_key(tmp) == key)
					return tmp;
				if (_key_compare(_get_key(tmp), key) == true)
					tmp = tmp->right;
				else
					tmp = tmp->left;
			}
			return _nil;
		}

		iterator	_lower_bound(key_type const& key) {
			base_ptr	tmp = _root;
			base_ptr	node = _nil;

			while (tmp != _nil) {
				if (_key_compare(_get_key(tmp), key) == false) {
					node = tmp;
					tmp = tmp->left;
				}
				else
					tmp = tmp->right;
			}
			return iterator(node);
		}

		const_iterator	_lower_bound(key_type const& key) const {
			base_ptr	tmp = _root;
			base_ptr	node = _nil;

			while (tmp != _nil) {
				if (_key_compare(_get_key(tmp), key) == false) {
					node = tmp;
					tmp = tmp->left;
				}
				else
					tmp = tmp->right;
			}
			return const_iterator(node);
		}

		iterator	_upper_bound(key_type const& key) {
			base_ptr	tmp = _root;
			base_ptr	node = _nil;

			while (tmp != _nil) {
				if (_key_compare(key, _get_key(tmp)) == true) {
					node = tmp;
					tmp = tmp->left;
				}
				else
					tmp = tmp->right;
			}
			return iterator(node);
		}

		const_iterator	_upper_bound(key_type const& key) const {
			base_ptr	tmp = _root;
			base_ptr	node = _nil;

			while (tmp != _nil) {
				if (_key_compare(key, _get_key(tmp)) == true) {
					node = tmp;
					tmp = tmp->left;
				}
				else
					tmp = tmp->right;
			}
			return const_iterator(node);
		}

		// NODE MANAGEMENT
		base_ptr	_create_nil() {
			base_ptr tmp = _b_alloc.allocate(1);
			_b_alloc.construct(tmp, rb_node_base());
			return tmp;
		}

		base_ptr	_create_node(value_type const& val, base_ptr parent) {
			rb_node<Val>	tmp(val, parent, _nil);
			node_ptr		new_node = _n_alloc.allocate(1);
			_n_alloc.construct(new_node, tmp);
			return new_node;
		}

		// template <class T, class Alloc_T>
		// void	_drop_node(T& node_type, Alloc_T& alloc) { // templated version for passing base/node allocators
		void	_drop_node(base_ptr node) {
			_b_alloc.destroy(node);
			_b_alloc.deallocate(node, 1);
			_size -= 1;
		}

		// called by clear to reset _root and its parent to _nil for empty tree
		void	_nullify_root() {
			_root = _nil;
			_root->parent = _nil;
		}

		// called by clear. erases from `start` onwards without rebalancing
		void	_erase_from(base_ptr start) {
			while (start != _nil && start != NULL) {
				_erase_from(start->right);
				base_ptr next = start->left;
				_drop_node(start);
				start = next;
			}
		}

		// INSERTION & ROTATIONS
		// called by _insert_at
		base_ptr	_find_insert_pos(base_ptr new_node) {
			base_ptr parent = _nil;
			base_ptr tmp = this->_root;

			while (tmp != _nil) {
				parent = tmp;
				if (new_node != _nil &&
					_key_compare(_get_key(new_node), _get_key(tmp)) == true)
					tmp = tmp->left;
				else
					tmp = tmp->right;
			}
			return parent;
		}

		// called by insert
		base_ptr	_insert_at(base_ptr parent, value_type const& val) {
			base_ptr node = _create_node(val, parent);
			base_ptr new_parent = _find_insert_pos(node);
			
			node->parent = new_parent;
			if (new_parent == _nil)
				_root = node;
			else if (node != _nil && new_parent != _nil &&
				_key_compare(_get_key(node), _get_key(new_parent)) == true)
				new_parent->left = node;
			else
				new_parent->right = node;
			_insert_rebalance(node);
			return node;
		}

		// helper called by rotate fns
		void	_relink_parent(base_ptr node, base_ptr new_child) {
			new_child->parent = node->parent;
			if (node->parent == _nil)
				this->_root = new_child;
			else if (node == node->parent->left)
				node->parent->left = new_child;
			else if (node == node->parent->right)
				node->parent->right = new_child;
		}

		void	_left_rotate(base_ptr node) {
			base_ptr node_b = node->right;

			// turn node_b's left subtree into node's right subtree
			node->right = node_b->left;
			if (node_b->left != _nil)
				node_b->left->parent = node;
			_relink_parent(node, node_b);
			node_b->left = node;
			node->parent = node_b;
		}

		void	_right_rotate(base_ptr node) {
			base_ptr node_b = node->left;

			node->left = node_b->right;
			if (node_b->right != _nil)
				node_b->right->parent = node;
			_relink_parent(node, node_b);
			node_b->right = node;
			node->parent = node_b;
		}

		// helper called by _parent_case if uncle node is red
		base_ptr	_ins_red_uncle_case(base_ptr uncl, base_ptr node) {
			uncl->colour = BLACK;
			node->parent->colour = BLACK;
			node->parent->parent->colour = RED;
			return node->parent->parent;
		}

		// helper called by _rebalance_tree for R_ Rotations
		base_ptr	_ins_reb_right_parent_case(base_ptr node) {
			base_ptr uncl = node->parent->parent->left;

			if (uncl->colour == RED)
				node = _ins_red_uncle_case(uncl, node);
			else { // if uncle is black
				if (node == node->parent->left) { // Right Left Case
					node = node->parent;
					_right_rotate(node);
				}
				node->parent->colour = BLACK;
				node->parent->parent->colour = RED;
				_left_rotate(node->parent->parent); // Right Right Case
			}
			return node;
		}

		// helper called by _rebalance_tree for L_ Rotations
		base_ptr	_ins_reb_left_parent_case(base_ptr node) {
			base_ptr uncl = node->parent->parent->right;
			
			if (uncl->colour == RED)
				node = _ins_red_uncle_case(uncl, node);
			else { // if uncle is black
				if (node == node->parent->right) { // Left Right Case
					node = node->parent;
					_left_rotate(node);
				}
				node->parent->colour = BLACK;
				node->parent->parent->colour = RED;
				_right_rotate(node->parent->parent); // Left Left Case
			}
			return node;
		}

		// called by _insert to fix RB properties after insertion
		void	_insert_rebalance(base_ptr node) {
			while (node->parent->colour == RED) {
				if (node->parent == node->parent->parent->right)
					node = _ins_reb_right_parent_case(node);
				else // if node's parent is on left side
					node = _ins_reb_left_parent_case(node);
				if (node == _root)
					break;
			}
			_root->colour = BLACK;
			_nil->parent = _root;
		}

		// DELETION
		// called by _delete_node
		// Allows moving subtrees around RB tree by replacing one subtree
		// with another, i.e. node_a's parent becomes node_b's and vice versa.
		void	_transplant(base_ptr a, base_ptr b) {
			if (a->parent == _nil)
				_root = b;
			else if (a == a->parent->left)
				a->parent->left = b;
			else
				a->parent->right = b;
			b->parent = a->parent;
		}

		// helper called by _delete_rebalance if node is left child
		base_ptr	_del_reb_left_child_case(base_ptr node, base_ptr parent) {
			base_ptr	sib = parent->right;

			// case 1: node's sibling is RED
			if (sib->colour == RED) {
				sib->colour = BLACK;
				parent->colour = RED;
				_left_rotate(parent);
				sib = parent->right;
			}
			// case 2: node's sibling is BLACK and both sib's children are BLACK
			if (sib->left->colour == BLACK && sib->right->colour == BLACK) {
				sib->colour = RED;
				node = parent;
			}
			else {
				// case 3: node's sibling is BLACK, sib's LChild is RED and RChild is BLACK
				if (sib->right->colour == BLACK) {
					sib->left->colour = BLACK;
					sib->colour = RED;
					_right_rotate(sib);
					sib = parent->right;
				}
				// case 4: node's sibling is BLACK and sib's RChild is RED
				sib->colour = parent->colour;
				parent->colour = BLACK;
				sib->right->colour = BLACK;
				_left_rotate(parent);
				node = this->_root;
			}
			return node;
		}

		// helper called by _delete_rebalance if node is left child
		base_ptr	_del_reb_right_child_case(base_ptr node, base_ptr parent) {
			base_ptr	sib = parent->left;

			// case 1: node's sibling is RED
			if (sib->colour == RED) {
				sib->colour = BLACK;
				parent->colour = RED;
				_right_rotate(parent);
				sib = parent->left;
			}
			// case 2: node's sibling is BLACK and both sib's children are BLACK
			if (sib->right->colour == BLACK && sib->left->colour == BLACK) {
				sib->colour = RED;
				node = parent;
			}
			else {
				// case 3: node's sibling is BLACK, sib's LChild is BLACK and RChild is RED
				if (sib->left->colour == BLACK) {
					sib->right->colour = BLACK;
					sib->colour = RED;
					_left_rotate(sib);
					sib = parent->left;
				}
				// case 4: node's sibling is BLACK and sib's LChild is RED
				sib->colour = parent->colour;
				parent->colour = BLACK;
				sib->left->colour = BLACK;
				_right_rotate(parent);
				node = this->_root;
			}
			return node;
		}

		// called by _delete_node to fixup RB properties after deletion
		void	_delete_rebalance(base_ptr node) {
			while (node != _root && node->colour == BLACK) {
				if (node == node->parent->left)
					node = _del_reb_left_child_case(node, node->parent);
				else
					node = _del_reb_right_child_case(node, node->parent);
			}
			node->colour = BLACK;
		}

		// helper called by _delete_node if node_to_delete has 2 children
		base_ptr	_del_two_children(base_ptr x, base_ptr node_to_delete, rb_colour &saved_colour) {
			// assigning minimum of right subtree of node_to_delete to y
			base_ptr	y = _find_min(node_to_delete->right);
			saved_colour = y->colour;
			x = y->right;
			if (y->parent == node_to_delete)
				x->parent = y;
			else {
				_transplant(y, y->right);
				y->right = node_to_delete->right;
				y->right->parent = y;
			}
			_transplant(node_to_delete, y);
			y->left = node_to_delete->left;
			y->left->parent = y;
			y->colour = node_to_delete->colour;
			return x;
		}

		// helper called by _delete_node if node_to_delete has 1 child
		base_ptr	_del_single_child(base_ptr x, base_ptr node_to_delete) {
			if (node_to_delete->left == _nil) {
				x = node_to_delete->right;
				_transplant(node_to_delete, x);
			}
			else if (node_to_delete->right == _nil) {
				x = node_to_delete->left;
				_transplant(node_to_delete, x);
			}
			return x;
		}

		// called by erase
		size_type	_delete_node(base_ptr node_to_delete) {
			if (node_to_delete == _nil) // invalid key/pos given
				return 0;

			base_ptr	x = _nil;
			rb_colour	saved_colour = node_to_delete->colour;

			 // when node_to_delete only has 1 child
			if (node_to_delete->left == _nil || node_to_delete->right == _nil)
				x = _del_single_child(x, node_to_delete);
			else // when node_to_delete has 2 children
				x = _del_two_children(x, node_to_delete, saved_colour);
			_drop_node(node_to_delete);
			if (saved_colour == BLACK) // if y is BLACK, RB properties may have been violated
				_delete_rebalance(x);
			_nil->parent = _root;
			return 1;
		}
};
} // namespace ft

#endif
