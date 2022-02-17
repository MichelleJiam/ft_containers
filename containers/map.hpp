/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.hpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 16:27:08 by mjiam         #+#    #+#                 */
/*   Updated: 2022/02/17 21:43:14 by mjiam         ########   odam.nl         */
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

	public:
		typedef typename Allocator::reference			reference;
		typedef typename Allocator::const_reference		const_reference;
		typedef typename Allocator::pointer				pointer;
		typedef typename Allocator::const_pointer		const_pointer;
		typedef typename _tree_type::iterator			iterator;
		typedef typename _tree_type::const_iterator		const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;


};
} // namespace ft

#endif
