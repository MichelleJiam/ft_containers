/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 16:45:04 by mjiam         #+#    #+#                 */
/*   Updated: 2022/02/16 17:56:17 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

#include "../utils/rb_tree.hpp" // TODO: remove
#include <map>
typedef IMPL::pair<int,std::string>	t_ispair;
typedef std::pair<int,std::string>	t_ispair2;

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
	
	ft::rb_tree<int, t_ispair> RB;
	RB.debug_empty();
	RB.print_tree();

	RB.insert(t_ispair(11, "one"));
	RB.print_tree();
	
	RB.insert(t_ispair(2, "two"));
	RB.print_tree();

	RB.insert(t_ispair(14, "three"));
	RB.print_tree();

	RB.insert(t_ispair(1, "four"));
	RB.insert(t_ispair(7, "five"));
	RB.insert(t_ispair(15, "six"));
	RB.insert(t_ispair(5, "seven"));
	RB.insert(t_ispair(8, "eight"));
	RB.insert(t_ispair(4, "nine"));
	RB.print_tree();

	ft::rb_tree<int, t_ispair> RB2;
	RB2.insert(t_ispair(3, "one"));
	RB2.print_tree();
	RB2.insert(t_ispair(21, "two"));
	RB2.print_tree();
	RB2.insert(t_ispair(32, "three"));
	RB2.print_tree();
	RB2.insert(t_ispair(15, "four"));
	RB2.print_tree();

	ft::rb_tree<int, t_ispair> RB3;
	RB3.insert(t_ispair(40, "one"));
	RB3.insert(t_ispair(60, "two"));
	RB3.insert(t_ispair(55, "three"));
	RB3.insert(t_ispair(65, "four"));
	RB3.insert(t_ispair(75, "five"));
	RB3.insert(t_ispair(57, "six"));
	RB3.print_tree();

	RB3.erase(t_ispair(40, "one"));
	RB3.print_tree();
	
	system("leaks ft_bin");
	return 0;
}
