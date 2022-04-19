/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set.hpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 15:00:58 by mjiam         #+#    #+#                 */
/*   Updated: 2022/04/19 18:42:12 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
#define SET_HPP

#include <functional> // less, binary_function
#include "../utils/function.hpp" // Identity
#include "../utils/rb_tree.hpp"

namespace ft {
template < class Key, class Compare = std::less<Key>,
			class Alloc = std::allocator<Key> >
class set {
	public:
		typedef Key						key_type;
		typedef Key						value_type;
		typedef Compare					key_compare;
		typedef Compare					value_compare;
		typedef Alloc					allocator_type;
		typedef std::size_t				size_type;
		typedef std::ptrdiff_t			difference_type;

	private:
		typedef rb_tree<key_type, value_type, Identity<value_type>,
						key_compare, allocator_type>
					_tree_type;

		_tree_type	_tree;

	public:
		typedef typename Alloc::reference				reference;
		typedef typename Alloc::const_reference			const_reference;
		typedef typename Alloc::pointer					pointer;
		typedef typename Alloc::const_pointer			const_pointer;
		typedef typename _tree_type::const_iterator		iterator;
		typedef typename _tree_type::const_iterator		const_iterator;
		typedef typename _tree_type::const_reverse_iterator	reverse_iterator;
		typedef typename _tree_type::const_reverse_iterator	const_reverse_iterator;

	// CONSTRUCTORS & ASSIGNMENT OPERATORS
		// default: empty container
		explicit set(key_compare const& comp = key_compare(),
						allocator_type const& alloc = allocator_type())
				: _tree(comp, alloc) {	}

		// range
		template <class InputIterator>
		set(InputIterator first, InputIterator last,
			key_compare const& comp = key_compare(),
			allocator_type const& alloc = allocator_type())
				: _tree(comp, alloc) {
			insert(first, last);
		}

		// copy
		set(set const& other) : _tree(other._tree) {}

		// assignment operator
		set&	operator=(set const& other) {
			_tree = other._tree;
			return *this;
		}

	// DESTRUCTOR
		~set()  {}

	// OBSERVERS
		// Returns key comparison object out of which set was constructed.
		key_compare	key_comp() const {
			return _tree.key_comp();
		}

		// Returns value comparison object built from key comparison object.
		// Can be used to compare 2 elements to see if the first key goes
		// before the second.
		value_compare	value_comp() const {
			return value_compare(_tree.key_comp());
		}

	// ALLOCATOR
		allocator_type	get_allocator() const {
			return _tree.get_allocator();
		}

	// ITERATORS
		// Returns a read/write iterator pointing to first pair in the set.
		// Iteration is done in ascending order according to the keys.
		iterator	begin() {
			return _tree.begin();
		}

		// Returns a read-only iterator pointing to first pair in the set.
		// Iteration is done in ascending order according to the keys.
		const_iterator	begin() const {
			return _tree.begin();
		}

		// Returns a read/write iterator pointing to one past the last pair
		// in the set. Iteration is done in ascending order according to the keys.
		iterator	end() {
			return _tree.end();
		}

		// Returns a read-only iterator pointing to one past the last pair
		// in the set. Iteration is done in ascending order according to the keys.
		const_iterator	end() const {
			return _tree.end();
		}

		// Returns a read/write reverse iterator pointing to the last pair
		// in the set. Iteration is done in descending order according to the keys.
		reverse_iterator	rbegin() {
			return _tree.rbegin();
		}

		// Returns a read-only reverse iterator pointing to the last pair
		// in the set. Iteration is done in descending order according to the keys.
		const_reverse_iterator	rbegin() const {
			return _tree.rbegin();
		}

		// Returns a read/write reverse iterator pointing to one before the
		// first pair in the set. Iteration is done in descending order
		// according to the keys.
		reverse_iterator	rend() {
			return _tree.rend();
		}

		// Returns a read-only reverse iterator pointing to one before the
		// first pair in the set. Iteration is done in descending order
		// according to the keys.
		const_reverse_iterator	rend() const {
			return _tree.rend();
		}

	// CAPACITY FUNCTIONS
		// Returns true if the set is empty.
		bool	empty() const {
			return _tree.empty();
		}

		// Returns size of set.
		size_type	size() const {
			return _tree.size();
		}

		// Returns maximum size of set.
		size_type	max_size() const {
			return _tree.max_size();
		}
// MODIFIERS
		// single element
		ft::pair<iterator, bool>	insert(value_type const& val) {
			return _tree.insert(val);
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

		// Erases all elements with given value. Returns number of elements erased.
		size_type	erase(value_type const& val) {
			return _tree.erase(val);
		}

		// Erases elements between first and last.
		void	erase(iterator first, iterator last) {
			_tree.erase(first, last);
		}

		// Swaps elements between two sets.
		// Whether allocators are swapped depends on the allocator traits.
		void	swap(set& other) {
			_tree.swap(other._tree);
		}

		// Erases all elements in a set.
		void	clear() {
			_tree.clear();
		}

	// OPERATIONS
		// Tries to locate an element in set.
		// Returns iterator to found element or end() if not found.
		iterator	find(key_type const& key) {
			return _tree.find(key);
		}

		const_iterator	find(key_type const& key) const {
			return _tree.find(key);
		}

		// Returns number of elements with given key.
		// Only makes sense for multisets as sets do not allow duplicate
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
		// Doesn't make much sense for set as unique keys => range of 1 element.
		// If no matches are found, returns 2 iterators pointing to the
		// first element whose key goes after `key` according to internal
		// comparison object (key_comp).
		pair<iterator, iterator>	equal_range(key_type const& key) {
			return _tree.equal_range(key);
		}

		pair<const_iterator, const_iterator>	equal_range(key_type const& key) const {
			return _tree.equal_range(key);
		}

		// Friend declarations for accessing private tree structure
		template <class Key1, class Compare1, class Alloc1>
		friend bool operator==(set<Key1,Compare1,Alloc1> const& lhs,
								set<Key1,Compare1,Alloc1> const& rhs);

		template <class Key1, class Compare1, class Alloc1>
		friend bool operator<(set<Key1,Compare1,Alloc1> const& lhs,
								set<Key1,Compare1,Alloc1> const& rhs);
};

// NON-MEMBER FUNCTION OVERLOADS
// Improves performance by exchanging references to the data without actually
// performing any element copy or movement.
template <class Key, class Compare, class Alloc>
void swap(set<Key,Compare,Alloc>& lhs, set<Key,Compare,Alloc>& rhs) {
	lhs.swap(rhs);
}

// RELATIONAL OPERATORS
template <class Key, class Compare, class Alloc>
bool operator==(set<Key,Compare,Alloc> const& lhs,
				set<Key,Compare,Alloc> const& rhs) {
	return lhs._tree == rhs._tree;
}

template <class Key, class Compare, class Alloc>
bool operator!=(set<Key,Compare,Alloc> const& lhs,
				set<Key,Compare,Alloc> const& rhs) {
	return !(lhs == rhs);
}

template <class Key, class Compare, class Alloc>
bool operator<(set<Key,Compare,Alloc> const& lhs,
				set<Key,Compare,Alloc> const& rhs) {
	return lhs._tree < rhs._tree;
}

template <class Key, class Compare, class Alloc>
bool operator<=(set<Key,Compare,Alloc> const& lhs,
				set<Key,Compare,Alloc> const& rhs) {
	return !(rhs < lhs);
}

template <class Key, class Compare, class Alloc>
bool operator>(set<Key,Compare,Alloc> const& lhs,
				set<Key,Compare,Alloc> const& rhs) {
	return rhs < lhs;
}

template <class Key, class Compare, class Alloc>
bool operator>=(set<Key,Compare,Alloc> const& lhs,
				set<Key,Compare,Alloc> const& rhs) {
	return !(lhs < rhs);
}

} // namespace ft

#endif /* SET_HPP */
