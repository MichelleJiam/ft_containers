/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.hpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 16:27:08 by mjiam         #+#    #+#                 */
/*   Updated: 2022/03/22 22:47:02 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <cstddef> // ptrdiff_t, size_t
#include <functional> // less, binary_function
#include <memory> // allocator
#include "../utils/pair.hpp"
#include "../utils/reverse_iterator.hpp"
#include "../utils/rb_tree.hpp"

namespace ft {
template < class Key, class T, class Compare = std::less<Key>,
			class Allocator = std::allocator< ft::pair<const Key, T> > >
class map {
	public:
		typedef Key						key_type;
		typedef T						mapped_type;
		typedef ft::pair<const Key, T>	value_type;
		typedef std::size_t				size_type;
		typedef std::ptrdiff_t			difference_type;
		typedef Compare					key_compare;
		typedef Allocator				allocator_type;

		// nested class for comparing elements of type value_type
		class	value_compare
				: public std::binary_function<value_type, value_type, bool> {
			// `friend` allows class to access private & protected members of map
			friend class map<Key, T, Compare, Allocator>;
			protected:
				Compare	comp;

				value_compare(Compare c) : comp(c) {}

			public:
				bool	operator()(value_type const& x, value_type const& y) const {
					return comp(x.first, y.first);
				}
		};

	private:
		typedef rb_tree<key_type, value_type, key_compare, allocator_type>
					_tree_type;

		_tree_type	_tree;

	public:
		typedef typename Allocator::reference			reference;
		typedef typename Allocator::const_reference		const_reference;
		typedef typename Allocator::pointer				pointer;
		typedef typename Allocator::const_pointer		const_pointer;
		typedef typename _tree_type::iterator			iterator;
		typedef typename _tree_type::const_iterator		const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	// CONSTRUCTORS & ASSIGNMENT OPERATORS
		// default: empty container
		explicit map(key_compare const& comp = key_compare(),
						allocator_type const& alloc = allocator_type())
				: _tree(comp, alloc) {	}

		// range
		template <class InputIterator>
		map(InputIterator first, InputIterator last,
			key_compare const& comp = key_compare(),
			allocator_type const& alloc = allocator_type())
				: _tree(comp, alloc) {
			insert(first, last);
		}

		// copy
		map(map const& other) : _tree(other._tree) {}

		// assignment operator
		map&	operator=(map const& other) {
			_tree = other._tree;
			return *this;
		}

	// DESTRUCTOR
		~map()  {}

	// ITERATORS

		
	// CAPACITY FUNCTIONS
		bool	empty() const {
			return _tree.empty();
		}

		size_type	size() const {
			return _tree.size();
		}

		size_type	max_size() const {
			return _tree.max_size();
		}

	// ELEMENT ACCESS FUNCTIONS


	// MODIFIERS
		// single
		ft::pair<iterator, bool>	insert(value_type const& val) {
			size_type	old_size = size();
			iterator	inserted = _tree.insert(val);
			return ft::make_pair(inserted, old_size != size());
		}

		// with hint
		iterator	insert(iterator position, value_type const& val) {
			return _tree.insert(position, val);
		}

		// range
		template <class InputIterator>
		void	insert(InputIterator first, InputIterator last) {
			_tree.insert(first, last);
		}

	// OBSERVERS
		

	// OPERATIONS
		iterator	find(key_type const& key) {
			return _tree.find(key);
		}

		const_iterator	find(key_type const& key) const {
			return _tree.find(key);
		}

		size_type	count(key_type const& key) const {
			return _tree.count(key);
		}

		iterator	lower_bound(key_type const& key) {
			return _tree.lower_bound(key);
		}

		const_iterator	lower_bound(key_type const& key) const {
			return _tree.lower_bound(key);
		}

		iterator	upper_bound(key_type const& key) {
			return _tree.upper_bound(key);
		}

		const_iterator	upper_bound(key_type const& key) const {
			return _tree.upper_bound(key);
		}

		pair<iterator, iterator>	equal_range(key_type const& key) {
			return _tree.equal_range(key);
		}

		pair<const_iterator, const_iterator>	equal_range(key_type const& key) const {
			return _tree.equal_range(key);
		}

	// ALLOCATOR
		allocator_type	get_allocator() const {
			return _tree.get_allocator();
		}
};
} // namespace ft

#endif
