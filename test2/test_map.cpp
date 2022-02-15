/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_map.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/15 22:22:07 by mjiam         #+#    #+#                 */
/*   Updated: 2022/02/15 22:34:07 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

typedef IMPL::pair<int,std::string>	t_ispair; // TODO: fix, won't compile unless changed to std::
typedef IMPL::map<int, std::string>	t_ismap;

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
}

void test_map() {
#ifndef SIMPLE
	printHeader("testing map");
#endif

	test_map_constructors();
	test_map_erase();
}
