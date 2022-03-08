/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 16:45:04 by mjiam         #+#    #+#                 */
/*   Updated: 2022/03/08 21:44:40 by mjiam         ########   odam.nl         */
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

template <typename Iterator>
void	print_key_or_null(Iterator it, Iterator end) {
	if (it == end)
		std::cout << "NULL" << std::endl;
	else
		std::cout << it->first << std::endl;
}

void	test_rb() {
std::cout << "=== Testing insert on RB ===\n\n";
	std::cout << "Insert 11, 2, 14, 1, 7, 15, 5, 8, 4\n";
	std::cout << "Result:\n";
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

	std::cout << "=== Testing insert on RB2 ===\n\n";
	std::cout << "Insert 3, 21, 32, 15\n";
	std::cout << "Result:\n";
	ft::rb_tree<int, t_ispair> RB2;
	RB2.insert(t_ispair(3, "one"));
	RB2.print_tree();
	RB2.insert(t_ispair(21, "two"));
	RB2.print_tree();
	RB2.insert(t_ispair(32, "three"));
	RB2.print_tree();
	ft::rb_tree<int, t_ispair>::iterator insert_ret = RB2.insert(t_ispair(15, "four"));
	RB2.print_tree();
	std::cout << "insert(15, four) returns: " << insert_ret->first << " " << insert_ret->second << std::endl;
	
	std::cout << "Inserting duplicate 21 key with value \'forty-two\'\n";
	insert_ret = RB2.insert(t_ispair(21, "forty-two"));
	std::cout << "insert(21, forty-two) returns: " << insert_ret->first << " " << insert_ret->second << std::endl;

	std::cout << "\n=== Testing erase on RB3 ===\n\n";
	std::cout << "Insert 40, 60, 55, 65, 75, 57\n";
	std::cout << "Result:\n";
	ft::rb_tree<int, t_ispair> RB3;
	RB3.insert(t_ispair(40, "one"));
	RB3.insert(t_ispair(60, "two"));
	RB3.insert(t_ispair(55, "three"));
	RB3.insert(t_ispair(65, "four"));
	RB3.insert(t_ispair(75, "five"));
	RB3.insert(t_ispair(57, "six"));
	RB3.print_tree();
	std::cout << "Delete 40\n";
	std::cout << "Result:\n";
	RB3.erase(t_ispair(40, "one"));
	RB3.print_tree();

	std::cout << "=== Testing accessors on RB2 ===\n\n";
	RB2.print_tree();
	std::map<int, std::string>	map;
	map.insert(std::pair<int,std::string>(21, "two"));
	map.insert(std::pair<int,std::string>(3, "one"));
	map.insert(std::pair<int,std::string>(32, "three"));
	map.insert(std::pair<int,std::string>(15, "four"));

	std::cout << "std begin returns key:\t" << map.begin()->first << std::endl; // returns 3
	std::cout << "ft begin returns key:\t" << RB2.begin()->first << std::endl;
	
	std::cout << "std iterating forwards until end:\t";
	for (std::map<int, std::string>::iterator it = map.begin(); it != map.end(); ++it)
		std::cout << it->first << " ";
	std::cout << std::endl;
	std::cout << "ft iterating forwards until end:\t";
	for (ft::rb_tree<int, t_ispair>::iterator it = RB2.begin(); it != RB2.end(); ++it)
		std::cout << it->first << " ";
	std::cout << std::endl;

	std::cout << "std iterating backwards from end:\t";
	std::map<int, std::string>::iterator it1 = map.end();
	for (--it1; it1 != map.begin(); --it1)
		std::cout << it1->first << " ";
	std::cout << (*it1).first << std::endl;
	std::cout << "ft iterating backwards from end:\t";
	ft::rb_tree<int, t_ispair>::iterator it2 = RB2.end();
	for (--it2; it2 != RB2.begin(); --it2)
		std::cout << it2->first << " ";
	std::cout << (*it2).first << std::endl;

	std::map<int, std::string>::reverse_iterator rit1 = map.rend();
	std::cout << "std rend-- returns key:\t" << (--rit1)->first << std::endl;
	ft::rb_tree<int, t_ispair>::reverse_iterator rit2 = RB2.rend();
	std::cout << "ft rend-- returns key:\t" << (--rit2)->first << std::endl;

	std::cout << "std iterating backwards using rbegin & rend:\t";
	for (std::map<int, std::string>::reverse_iterator rit3 = map.rbegin();
			rit3 != map.rend(); ++rit3)
		std::cout << rit3->first << " ";
	std::cout << std::endl;
	std::cout << "ft iterating backwards using rbegin & rend:\t";
	for (ft::rb_tree<int, t_ispair>::reverse_iterator rit4 = RB2.rbegin();
			rit4 != RB2.rend(); ++rit4)
		std::cout << rit4->first << " ";
	std::cout << std::endl;

	std::cout << "\n=== Testing find ===\n\n";
	std::cout << "find(42)\nSTD output:\t";
	std::map<int, std::string>::iterator search1 = map.find(42);
	if (search1 != map.end())
		std::cout << "Found 42 at " << search1->second << std::endl;
	else
		std::cout << "42 not found in map\n";
	std::cout << "FT output:\t";
	ft::rb_tree<int, t_ispair>::iterator search2 = RB2.find(42);
	if (search2 != RB2.end())
		std::cout << "Found 42 at " << search2->second << std::endl;
	else
		std::cout << "42 not found in map\n";
	
	search1 = map.find(15);
	std::cout << std::endl;
	std::cout << "find(15)\nSTD output:\t";
	if (search1 != map.end())
		std::cout << "Found 15 at " << search1->second << std::endl;
	else
		std::cout << "15 not found in map\n";
	search2 = RB2.find(15);
	std::cout << "FT output:\t";
	if (search2 != RB2.end())
		std::cout << "Found 15 at " << search2->second << std::endl;
	else
		std::cout << "15 not found in map\n";

	std::cout << "\n=== Testing count ===\n\n";	
	std::cout << "count(15)\nSTD output:\t" << map.count(15) << std::endl;
	std::cout << "FT output:\t" << RB2.count(15) << std::endl;

	std::cout << "\n=== Testing lower/upper_bound ===\n\n";
	std::cout << "lower_bound(15)\nSTD output:\t";
		print_key_or_null(map.lower_bound(15), map.end());
	std::cout << "FT output:\t";
		print_key_or_null(RB2.lower_bound(15), RB2.end());
	std::cout << "lower_bound(32)\nSTD output:\t";
		print_key_or_null(map.lower_bound(32), map.end());
	std::cout << "FT output:\t";
		print_key_or_null(RB2.lower_bound(32), RB2.end());
	std::cout << "\nupper_bound(15)\nSTD output:\t";
		print_key_or_null(map.upper_bound(15), map.end());
	std::cout << "FT output:\t";
		print_key_or_null(RB2.upper_bound(15), RB2.end());
	std::cout << "upper_bound(32)\nSTD output:\t";
		print_key_or_null(map.upper_bound(32), map.end());
	std::cout << "FT output:\t";
		print_key_or_null(RB2.upper_bound(32), RB2.end());
}

int main() {

	// std::cout << "version: " << IMPL::get_name() << std::endl;

	// test_utils();
	// test_vector();
	// test_stack();
	test_rb();
	
	// system("leaks ft_bin");
	return 0;
}
