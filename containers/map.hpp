/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.hpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 16:27:08 by mjiam         #+#    #+#                 */
/*   Updated: 2022/03/29 20:15:17 by mjiam         ########   odam.nl         */
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
		// Returns a read/write iterator pointing to first pair in the map.
		// Iteration is done in ascending order according to the keys.
		iterator	begin() {
			return _tree.begin();
		}

		// Returns a read-only iterator pointing to first pair in the map.
		// Iteration is done in ascending order according to the keys.
		const_iterator	begin() const {
			return _tree.begin();
		}

		// Returns a read/write iterator pointing to one past the last pair
		// in the map. Iteration is done in ascending order according to the keys.
		iterator	end() {
			return _tree.end();
		}

		// Returns a read-only iterator pointing to one past the last pair
		// in the map. Iteration is done in ascending order according to the keys.
		const_iterator	end() const {
			return _tree.cend();
		}

		// Returns a read/write reverse iterator pointing to the last pair
		// in the map. Iteration is done in descending order according to the keys.
		reverse_iterator	rbegin() {
			return _tree.rbegin();
		}

		// Returns a read-only reverse iterator pointing to the last pair
		// in the map. Iteration is done in descending order according to the keys.
		const_reverse_iterator	rbegin() const {
			return _tree.rbegin();
		}

		// Returns a read/write reverse iterator pointing to one before the
		// first pair in the map. Iteration is done in descending order
		// according to the keys.
		reverse_iterator	rend() {
			return _tree.rend();
		}

		// Returns a read-only reverse iterator pointing to one before the
		// first pair in the map. Iteration is done in descending order
		// according to the keys.
		const_reverse_iterator	rend() const {
			return _tree.rend();
		}

		
	// CAPACITY FUNCTIONS
		// Returns true if the map is empty.
		bool	empty() const {
			return _tree.empty();
		}

		// Returns size of map.
		size_type	size() const {
			return _tree.size();
		}

		// Returns maximum size of map.
		size_type	max_size() const {
			return _tree.max_size();
		}

	// ELEMENT ACCESS FUNCTIONS
		// Allows subscript access to map data.
		// Returns a reference to value associated with key `k` or
		// default value of a newly-created key if `k` doesn't yet exist.
		mapped_type&	operator[](key_type const& key) {
			iterator	it = lower_bound(key);
			if (it == end() || key_comp()(key, (*it).first) == true)
				it = insert(it, value_type(key, mapped_type()));
			return (*it).second;
		}

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

		// Erases an element pointed to by given iterator.
		// If element itself is a pointer, pointed-to data is not touched.
		void	erase(iterator position) {
			_tree.erase(position);
		}

		// Erases all elements with given key. Returns number of elements erased.
		size_type	erase(key_type const& key) {
			return _tree.erase(key);
		}

		// Erases elements between first and last.
		void	erase(iterator first, iterator last) {
			_tree.erase(first, last);
		}

		// Swaps elements between two maps.
		// Whether allocators are swapped depends on the allocator traits.
		void	swap(map& other) {
			_tree.swap(other._tree);
		}

		// Erases all elements in a map.
		void	clear() {
			_tree.clear();
		}

	// OBSERVERS
		// Returns key comparison object out of which map was constructed.
		key_compare	key_comp() const {
			return _tree.key_comp();
		}

		// Returns value comparison object built from key comparison object.
		// Can be used to compare 2 elements to see if the first key goes
		// before the second.
		value_compare	value_comp() const {
			return value_compare(_tree.key_comp());
		}

	// OPERATIONS
		// Tries to locate an element in map.
		// Returns iterator to found element or end() if not found.
		iterator	find(key_type const& key) {
			return _tree.find(key);
		}

		const_iterator	find(key_type const& key) const {
			return _tree.find(key);
		}

		// Returns number of elements with given key.
		// Only makes sense for multimaps as maps do not allow duplicate
		// keys and will always return either 0 (absent) or 1 (present).
		size_type	count(key_type const& key) const {
			return _tree.count(key);
		}

		// Returns iterator to first element of a subsequence matching `key`.
		// If none, returns first element with a greater value than `key`,
		// or end() if no such element exists.
		iterator	lower_bound(key_type const& key) {
			return _tree.lower_bound(key);
		}

		const_iterator	lower_bound(key_type const& key) const {
			return _tree.lower_bound(key);
		}

		// Returns iterator to first element greater than `key`,
		// or end() if no such element exists.
		iterator	upper_bound(key_type const& key) {
			return _tree.upper_bound(key);
		}

		const_iterator	upper_bound(key_type const& key) const {
			return _tree.upper_bound(key);
		}

		// Returns a pair of iterators pointing to subsequence matching
		// given key.
		// Doesn't make much sense for map as unique keys => range of 1 element.
		// If no matches are found, returns 2 iterators pointing to the
		// first element whose key goes after `key` according to internal
		// comparison object (key_comp).
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
