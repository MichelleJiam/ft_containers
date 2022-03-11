/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.hpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 16:27:08 by mjiam         #+#    #+#                 */
/*   Updated: 2022/03/08 22:28:53 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <cstddef> // ptrdiff_t, size_t
#include <functional> // less
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
};
} // namespace ft

#endif
