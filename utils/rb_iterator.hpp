/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rb_iterator.hpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 15:56:42 by mjiam         #+#    #+#                 */
/*   Updated: 2022/04/07 19:08:36 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_ITERATOR_HPP
#define RB_ITERATOR_HPP

#include "rb_node.hpp"
#include "iterator_utils.hpp" // iterator_tag

namespace ft {
template <class T>
class	rb_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T>{
	public:
		typedef	T	value_type;
		typedef T&	reference;
		typedef T*	pointer;

		typedef ft::bidirectional_iterator_tag	iterator_category;
		typedef std::ptrdiff_t					difference_type;

		typedef rb_iterator<T>			self;
		typedef rb_node_base::base_ptr	base_ptr;
		typedef rb_node<T>*				node_ptr;
	
	private:
		base_ptr	_node;

		// Sentinel is the only node with both children being NULL.
		bool	_is_nil(base_ptr x) {
			return x->right == NULL && x->left == NULL;
		}

		base_ptr	_rb_increment(base_ptr x) {
			if (_is_nil(x)) // if x is sentinel
				x = x->parent; // sentinel's parent is root
			else if (!_is_nil(x->right)) { // if x is not end node
				x = x->right;
				while (!_is_nil(x->left)) // move downwards
					x = x->left;
			}			
			else { // if x is end node
				base_ptr	y = x->parent;
				while (!_is_nil(y) && x == y->right) {
					x = y;
					y = y->parent;
				}
				// if (x->right != y) // moving upwards
					x = y;
			}
			return x;
		}

		base_ptr	_rb_decrement(base_ptr x) {
			if (_is_nil(x)) { // if x is sentinel
				x = x->parent; // sentinel's parent is root
				while (!_is_nil(x->right)) // getting max
					x = x->right;
			}
			else if (!_is_nil(x->left)) { // if x is not end node
				base_ptr	y = x->left;
				while (!_is_nil(y->right)) // moving downwards
					y = y->right;
				x = y;
			}
			else { // if x is end node
				base_ptr	y = x->parent;
				while (x == y->left) { // moving upwards
					x = y;
					y = y->parent;
				}
				x = y;
			}
			return x;
		}

	public:
		// constructors
		rb_iterator() : _node() {}
		
		explicit rb_iterator(base_ptr x) : _node(x) {}

		base_ptr	base() const {
			return _node;
		}

		reference	operator*() const {
			return static_cast<node_ptr>(_node)->val;
		}

		pointer	operator->() const {
			return &static_cast<node_ptr>(_node)->val;
		}

		// ++it
		self&	operator++() {
			_node = _rb_increment(_node);
			return *this;
		}

		// it++
		self	operator++(int) {
			self	tmp = *this;
			_node = _rb_increment(_node);
			return tmp;
		}

		// --it
		self&	operator--() {
			_node = _rb_decrement(_node);
			return *this;
		}

		// it++
		self	operator--(int) {
			self	tmp = *this;
			_node = _rb_decrement(_node);
			return tmp;
		}

		// user-defined conversion function for const iterator
		operator	rb_iterator<T const>() const {
			return rb_iterator<T const>(this->_node);
		}
};

template <class T>
bool	operator==(rb_iterator<T> const& x, rb_iterator<T> const& y) {
	return x.base() == y.base();
}

template <class T>
bool	operator!=(rb_iterator<T> const& x, rb_iterator<T> const& y) {
	return x.base() != y.base();
}

} // namespace ft

#endif
