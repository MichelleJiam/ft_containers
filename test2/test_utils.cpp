/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_utils.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 16:54:54 by mjiam         #+#    #+#                 */
/*   Updated: 2022/01/21 19:03:20 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"
#include "vector.hpp"
#include "../utils/pair.hpp"
#include "../utils/lexicographical_compare.hpp"

#define lex_comp lexicographical_compare

// void test_utils(IMPL::pair<int,int> &passed_tests) { //, std::ofstream &outfile) {
// 	printHeader("utils");
	
// 	// pair/make_pair test
//     int a[3] = {7, 42, 30};
// 	IMPL::pair<int,int>	p = IMPL::make_pair(12, a[1]);
// 	printTest("pair", passed_tests.second);
// 	std::cout << "Making pair with values: " << 12 << "," << a[1] << std::endl;
// 	std::cout << "Value of p is (" << p.first << "," << p.second << ")\n";
// 	// passed_tests.first += printResult(p1.first == p2.first
//     //                                     && p1.second == p2.second);

// 	// lexicographical_compare test
// 	std::string	s1 = "Apple";
// 	std::string s2 = "apple";
// 	printTest("lexicographical_compare", passed_tests.second);
// 	std::cout << "Comparing strings: " << s1 << " & " << s2 << std::endl << std::boolalpha;
// 	bool comp1 = IMPL::lex_comp(s1.begin(), s1.end(), s2.begin(), s2.end());
// 	bool comp2 = IMPL::lex_comp(s1.begin(), s1.end(), s2.begin(), s2.end(), mycomp);
// 	std::cout << "Default comparison returns: " << comp1 << std::endl;
// 	std::cout << "Case-insensitive custom comparison returns: " << comp2 << std::endl;
// 	// passed_tests.first += printResult(comp1.first == comp1.second
//     //                             && comp2.first == comp2.second);
	
// 	// is_integral test
// 	printTest("is_integral", passed_tests.second);
// 	bool comp_char = IMPL::is_integral<char>::value;
// 	bool comp_int = IMPL::is_integral<int>::value;
// 	bool comp_float = IMPL::is_integral<float>::value;
// 	bool comp_it = IMPL::is_integral<IMPL::vector<int>::iterator>::value;
// 	std::cout << "char: " << comp_char << std::endl;
// 	std::cout << "int: " << comp_int << std::endl;
// 	std::cout << "float: " << comp_float << std::endl;
// 	std::cout << "vector iter: " << comp_it << std::endl;
// 	// passed_tests.first += printResult(comp_char.first == comp_char.second
// 	// 							&& comp_int.first == comp_int.second
// 	// 							&& comp_float.first == comp_float.second
// 	// 							&& comp_it.first == comp_it.second);
// }
