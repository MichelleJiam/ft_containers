/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 16:45:04 by mjiam         #+#    #+#                 */
/*   Updated: 2022/03/29 20:26:26 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

#include "../utils/rb_tree.hpp" // TODO: remove
#include <map>
typedef ft::pair<int,std::string>	t_ispair;
typedef IMPL::pair<char,int>		t_cipair;
typedef std::pair<int,std::string>	t_ispair2;
typedef	ft::map<int, std::string>	t_ismap;

namespace std {
	inline std::string get_name() { return "std"; }
} // TODO: remove

namespace ft {
	inline std::string get_name() { return "ft"; }
} // TODO: remove

template <typename Iterator>
void	print_keyval_or_null(Iterator it, Iterator end, bool newline = true, int which = 1) {
	if (it == end)
		std::cout << "NULL";
	else {
		if (which == 1)
			std::cout << it->first;
		else
			std::cout << it->second;
	}
	if (newline)
			std::cout << std::endl;
}

// template <typename It>
// void	printMap_helper(It root, std::string indent, bool last, It nil = NULL) {
// 	std::cout << indent;
// 	if (last) {
// 		std::cout << "R----";
// 		indent += "   ";
// 	}
// 	else {
// 		std::cout << "L----";
// 		indent += "|  ";
// 	}
// 	// std::string sColour = root->colour ? "BLACK" : "RED";
// 	if (root != nil) {
// 		std::cout << "[" << print_keyval_or_null(root, nil, false) << ", "
// 			<< print_keyval_or_null(root, nil, false, 2) << "] "; //<< "(" << sColour << ")";
// 		print_tree_helper(root->_M_left, indent, false, nil);
// 		print_tree_helper(root->_M_right, indent, true, nil);
// 	}
// 	else {
// 		std::cout << "NIL" << " (" << sColour << ") ";
// 		std::cout << " | LChild is ";
// 		if (root->left == nil) std::cout << "NIL\n";
// 		else std::cout << print_keyval_or_null((root.base())->_M_left, nil, false)
// 				<< ", " << print_keyval_or_null((root.base())->_M_left, nil, true, 2);
// 	}
// }

template <typename T>
void    printMap(T& base_map, std::string const cntr_name,
					std::string const test_case) {
	if (!test_case.empty())
		printTestCase(test_case);
	if (!cntr_name.empty())
		std::cout << "[ " << cntr_name << " ]\n";
	std::cout << "size: " << base_map.size() << std::endl;
	std::cout << "contents:\n";
	// printMap_helper<std::map<int, std::string>::iterator>(base_map.begin(), "", true, base_map.end());
	for (typename T::const_iterator it = base_map.begin(); it != base_map.end(); ++it)
		std::cout << "\t" << it->first << " " << it->second << std::endl;
	std::cout << std::endl;
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
	std::map<int, std::string>	map0;
	RB3.insert(t_ispair(40, "one"));
	RB3.insert(t_ispair(60, "two"));
	RB3.insert(t_ispair(55, "three"));
	RB3.insert(t_ispair(65, "four"));
	RB3.insert(t_ispair(75, "five"));
	RB3.insert(t_ispair(57, "six"));
	RB3.print_tree();
	map0.insert(std::pair<int,std::string>(40, "one"));
	map0.insert(std::pair<int,std::string>(60, "two"));
	map0.insert(std::pair<int,std::string>(55, "three"));
	map0.insert(std::pair<int,std::string>(65, "four"));
	map0.insert(std::pair<int,std::string>(75, "five"));
	map0.insert(std::pair<int,std::string>(57, "six"));
	printMap<std::map<int, std::string> >(map0, "STD map", "insert 40, 60, 55, 65, 75, 57");
	std::cout << "Delete 40\n"; // delete with key
	std::cout << "Result:\n";
	RB3.erase(40);
	RB3.print_tree();
	map0.erase(40);
	printMap<std::map<int, std::string> >(map0, "STD map", "delete 40");
	std::cout << "Delete 75 with pos\n"; // delete with pos
	std::cout << "Result:\n";
	RB3.erase(RB3.find(75));
	RB3.print_tree();
	map0.erase(map0.find(75));
	printMap<std::map<int, std::string> >(map0, "STD map", "delete 75 with pos");
	std::cout << "Delete 57 to end\n"; // delete with range
	std::cout << "Result:\n";
	ft::rb_tree<int, t_ispair>::iterator it0 = RB3.find(57);
	RB3.erase(it0, RB3.end());
	RB3.print_tree();
	map0.erase(map0.find(57), map0.end());
	printMap<std::map<int, std::string> >(map0, "STD map", "delete 57 to end");

	std::cout << "char/int map erase test\n";
	ft::rb_tree<char, t_cipair> map2;
	map2.insert(t_cipair('a', 10));
	map2.insert(t_cipair('b', 20));
	map2.insert(t_cipair('c', 30));
	map2.insert(t_cipair('d', 40));
	map2.insert(t_cipair('e', 50));
	map2.insert(t_cipair('f', 60));
	map2.print_tree();
	ft::rb_tree<char, t_cipair>::iterator itmap2 = map2.find('b');
	map2.erase (itmap2);	// erasing by iterator
	map2.erase ('c');	// erasing by key
	std::cout << "Erase b & c\n"; 
	map2.print_tree();
	std::cout << "Erase range a to end\n"; 
	itmap2 = map2.find ('a');
	map2.erase (itmap2, map2.end());
	map2.print_tree();
	std::map<char,int> mymap;
	mymap['a']=10;
	mymap['b']=20;
	mymap['c']=30;
	mymap['d']=40;
	mymap['e']=50;
	mymap['f']=60;
	std::map<char,int>::iterator it = mymap.find('b');
	mymap.erase (it);                   // erasing by iterator
	mymap.erase ('c');                  // erasing by key
	it=mymap.find ('a');
	mymap.erase ( it, mymap.end() );    // erasing by range
	printMap<std::map<char,int> >(mymap, "STD map", "erase range a to end");

	std::cout << "=== Testing clear on RB ===\n\n";
	std::cout << "Before clear:\n";
	RB.print_tree();
	RB.clear();
	std::cout << "After clear:\n";
	RB.print_tree();

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
		std::cout << "Found 42 with value " << search1->second << std::endl;
	else
		std::cout << "42 not found in map\n";
	std::cout << "FT output:\t";
	ft::rb_tree<int, t_ispair>::iterator search2 = RB2.find(42);
	if (search2 != RB2.end())
		std::cout << "Found 42 with value " << search2->second << std::endl;
	else
		std::cout << "42 not found in map\n";
	
	search1 = map.find(15);
	std::cout << std::endl;
	std::cout << "find(15)\nSTD output:\t";
	if (search1 != map.end())
		std::cout << "Found 15 with value " << search1->second << std::endl;
	else
		std::cout << "15 not found in map\n";
	search2 = RB2.find(15);
	std::cout << "FT output:\t";
	if (search2 != RB2.end())
		std::cout << "Found 15 with value " << search2->second << std::endl;
	else
		std::cout << "15 not found in map\n";

	std::cout << "\n=== Testing count ===\n\n";	
	std::cout << "count(15)\nSTD output:\t" << map.count(15) << std::endl;
	std::cout << "FT output:\t" << RB2.count(15) << std::endl;

	std::cout << "\n=== Testing lower/upper_bound ===\n\n";
	std::cout << "lower_bound(15)\nSTD output:\t";
		print_keyval_or_null(map.lower_bound(15), map.end());
	std::cout << "FT output:\t";
		print_keyval_or_null(RB2.lower_bound(15), RB2.end());
	std::cout << "lower_bound(32)\nSTD output:\t";
		print_keyval_or_null(map.lower_bound(32), map.end());
	std::cout << "FT output:\t";
		print_keyval_or_null(RB2.lower_bound(32), RB2.end());
	std::cout << "\nupper_bound(15)\nSTD output:\t";
		print_keyval_or_null(map.upper_bound(15), map.end());
	std::cout << "FT output:\t";
		print_keyval_or_null(RB2.upper_bound(15), RB2.end());
	std::cout << "upper_bound(32)\nSTD output:\t";
		print_keyval_or_null(map.upper_bound(32), map.end());
	std::cout << "FT output:\t";
		print_keyval_or_null(RB2.upper_bound(32), RB2.end());

	std::cout << "\n=== Testing equal_range ===\n\n";
	std::cout << "equal_range(15)\nSTD output:\t" << "lower: ";
		print_keyval_or_null(map.equal_range(15).first, map.end(), false);
		std::cout << " upper: " << map.equal_range(15).second->first << std::endl;
	std::cout << "FT output:\t" << "lower: ";
		print_keyval_or_null(RB2.equal_range(15).first, RB2.end(), false);
		std::cout << " upper: "; print_keyval_or_null(RB2.equal_range(15).second, RB2.end());

	std::cout << "equal_range(3)\nSTD output:\t" << "lower: ";
		print_keyval_or_null(map.equal_range(3).first, map.end(), false);
		std::cout << " upper: "; print_keyval_or_null(map.equal_range(3).second, map.end());
	std::cout << "FT output:\t" << "lower: ";
		print_keyval_or_null(RB2.equal_range(3).first, RB2.end(), false);
		std::cout << " upper: "; print_keyval_or_null(RB2.equal_range(3).second, RB2.end());
		
	std::cout << "equal_range(32)\nSTD output:\t" << "lower: ";
		print_keyval_or_null(map.equal_range(32).first, map.end(), false);
		std::cout << " upper: "; print_keyval_or_null(map.equal_range(32).second, map.end());
	std::cout << "FT output:\t" << "lower: ";
		print_keyval_or_null(RB2.equal_range(32).first, RB2.end(), false);
		std::cout << " upper: "; print_keyval_or_null(RB2.equal_range(32).second, RB2.end());

	std::cout << "equal_range(210)\nSTD output:\t" << "lower: ";
		print_keyval_or_null(map.equal_range(210).first, map.end(), false);
		std::cout << " upper: "; print_keyval_or_null(map.equal_range(210).second, map.end());
	std::cout << "FT output:\t" << "lower: ";
		print_keyval_or_null(RB2.equal_range(210).first, RB2.end(), false);
		std::cout << " upper: "; print_keyval_or_null(RB2.equal_range(210).second, RB2.end());

	std::cout << "\n=== Testing ft::map ===\n\n";
	t_ismap	ft_map0;
	std::cout << "is ft::map empty: " << ft_map0.empty() << std::endl;
	ft::pair<t_ismap::iterator, bool> insert_ret2 = ft_map0.insert(t_ispair(21, "twenty-one"));
	std::cout << "new element inserted: " << insert_ret2.second << " | value: "
		<< insert_ret2.first->first << std::endl;
	std::cout << "size: " << ft_map0.size() << std::endl;

	insert_ret2 = ft_map0.insert(t_ispair(21, "three"));
	std::cout << "new element inserted: " << insert_ret2.second << " | value: "
		<< insert_ret2.first->first << std::endl;
	std::cout << "size: " << ft_map0.size() << std::endl;

	std::cout << "ft_map0['21'] is " << ft_map0[21] << std::endl;
	std::cout << "ft_map0['42'] is " << ft_map0[42] << std::endl;
	std::cout << "size: " << ft_map0.size() << std::endl;
	ft_map0[42] = "forty-two";

	t_ismap	ft_map1;
	ft_map1[13] = "thirteen";
	std::cout << "before swap:\nmap0 size: " << ft_map0.size() << " | map1 size: " << ft_map1.size()
		<< "\nmap0.begin(): " << ft_map0.begin()->first << ", " << ft_map0.begin()->second
		<< " | map1.begin(): " << ft_map1.begin()->first << ", " << ft_map1.begin()->second
		<< std::endl;
	ft_map0.swap(ft_map1);
	std::cout << "after swap:\nmap0 size: " << ft_map0.size() << " | map1 size: " << ft_map1.size()
		<< "\nmap0.begin(): " << ft_map0.begin()->first << ", " << ft_map0.begin()->second
		<< " | map1.begin(): " << ft_map1.begin()->first << ", " << ft_map1.begin()->second
		<< std::endl << std::endl;

	std::cout << "map1.erase(42) returns: " << ft_map1.erase(42) << std::endl;
	std::cout << "size: " << ft_map1.size() << std::endl;
	ft_map0.clear();
	std::cout << "size of map0 after clear: " << ft_map0.size() << std::endl;
	std::cout << std::endl;

	// TODO:
	// - test map/tree op= for correct copying (of different types?) + memory leaks (from sentinel)
}

int main() {

	// std::cout << "version: " << IMPL::get_name() << std::endl;

	// test_utils();
	// test_vector();
	// test_stack();
	test_rb();
	
	system("leaks ft_bin");
	return 0;
}
