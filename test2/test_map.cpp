/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_map.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/15 22:22:07 by mjiam         #+#    #+#                 */
/*   Updated: 2022/03/10 16:55:50 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

typedef IMPL::pair<int,std::string>	t_ispair; // TODO: fix, won't compile unless changed to std::
typedef IMPL::map<int, std::string>	t_ismap;
typedef IMPL::map<char, int>		t_cimap;

void	test_map_erase(void) {
	printTest("erase");

	t_ismap	map;
	map.insert(std::pair<int,std::string>(1, "one"));
	map.insert(std::pair<int,std::string>(2, "two"));
	std::cout << "map size: " << map.size() << std::endl;
	try {
		map.erase(42);
	} catch (...) {
		std::cerr << "erase failed\n";
	}
	std::cout << "map size: " << map.size() << std::endl;
	map.erase(2);
	std::cout << "map size: " << map.size() << std::endl;
		
	t_cimap map2;
	map2.insert(t_cipair('a', 10));
	map2.insert(t_cipair('b', 20));
	map2.insert(t_cipair('c', 30));
	map2.insert(t_cipair('d', 40));
	map2.insert(t_cipair('e', 50));
	map2.insert(t_cipair('f', 60));
	// map2.print_tree();
	typename t_cimap::iterator it = map2.find('b');
	map2.erase (it);                   // erasing by iterator
	// map2.print_tree();
	map2.erase ('c');                  // erasing by key
	// map2.print_tree();
	it = map2.find ('e');
	map2.erase (it, map2.end());
	// map2.print_tree();
}

void test_map() {
#ifndef SIMPLE
	printHeader("testing map");
#endif

	test_map_constructors();
	test_map_erase();
}
