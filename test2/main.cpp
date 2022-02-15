/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 16:45:04 by mjiam         #+#    #+#                 */
/*   Updated: 2022/02/15 16:47:41 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

#include "../utils/rb_tree.hpp" // TODO: remove

namespace std {
	inline std::string get_name() { return "std"; }
} // TODO: remove

namespace ft {
	inline std::string get_name() { return "ft"; }
} // TODO: remove

int main() {

	// std::cout << "version: " << IMPL::get_name() << std::endl;

	// test_utils();
	// test_vector();
	// test_stack();
	
	ft::rb_tree<int, ft::pair<int, std::string> > RB;
	// RB.debug_empty();
	RB.print_tree();

	ft::pair<int, std::string> key1(42, "one");
	RB.insert(key1);
	RB.print_tree();
	
	ft::pair<int, std::string> key2(13, "two");
	RB.insert(key2);
	RB.print_tree();

	ft::pair<int, std::string> key3(60, "three");
	RB.insert(key3);
	RB.print_tree();
	
	// system("leaks ft_bin");
	return 0;
}
