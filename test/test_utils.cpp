/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_utils.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 16:54:54 by mjiam         #+#    #+#                 */
/*   Updated: 2022/01/20 21:11:27 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"
#include "vector.hpp"
#include "../utils/pair.hpp"
#include "../utils/lexicographical_compare.hpp"

#define lex_comp lexicographical_compare

void test_utils(ft::pair<int,int> &passed_tests) {
	printHeader("utils");
	
	// pair/make_pair test
    int a[3] = {7, 42, 30};
	ft::pair<int,int>	p1 = ft::make_pair(12, a[1]);
	std::pair<int,int>	p2 = std::make_pair(12, a[1]);
	printTest("pair", passed_tests.second);
	std::cout << "Making pair with values: " << 12 << "," << a[1] << std::endl;
	std::cout << "Value of (ft)p1 is (" << p1.first << "," << p1.second << ")\n";
	std::cout << "Value of (std)p2 is (" << p2.first << "," << p2.second << ")\n";
	passed_tests.first += printResult(p1.first == p2.first
                                        && p1.second == p2.second);

	// lexicographical_compare test
	std::string	s1 = "Apple";
	std::string s2 = "apple";
	printTest("lexicographical_compare", passed_tests.second);
	std::cout << "Comparing strings: " << s1 << " & " << s2 << std::endl << std::boolalpha;
	ft::pair<bool,bool> comp1(
			std::lex_comp(s1.begin(), s1.end(), s2.begin(), s2.end()),
			ft::lex_comp(s1.begin(), s1.end(), s2.begin(), s2.end()));
	ft::pair<bool,bool> comp2(
			std::lex_comp(s1.begin(), s1.end(), s2.begin(), s2.end(), mycomp),
			ft::lex_comp(s1.begin(), s1.end(), s2.begin(), s2.end(), mycomp));
	std::cout << "Default comparison returns: "
        << comp1.first << " (std), " << comp1.second << " (ft)\n";
	std::cout << "Case-insensitive custom comparison returns: "
        << comp2.first << " (std), " << comp2.second << " (ft)\n";
	passed_tests.first += printResult(comp1.first == comp1.second
                                && comp2.first == comp2.second);
	
	// is_integral test
	printTest("is_integral", passed_tests.second);
	ft::pair<bool,bool> comp_char(std::is_integral<char>::value,
                                    ft::is_integral<char>::value);
	ft::pair<bool,bool> comp_int(std::is_integral<int>::value,
                                    ft::is_integral<int>::value);
	ft::pair<bool,bool> comp_float(std::is_integral<float>::value,
                                    ft::is_integral<float>::value);
	ft::pair<bool,bool> comp_it(std::is_integral<std::vector<int>::iterator>::value,
								ft::is_integral<ft::vector<int>::iterator>::value);
	std::cout << "char:\t\t" << comp_char.first << " (std), " << comp_char.second << " (ft)\n";
	std::cout << "int:\t\t" << comp_int.first << " (std), " << comp_int.second << " (ft)\n";
	std::cout << "float:\t\t" << comp_float.first << " (std), " << comp_float.second << " (ft)\n";
	std::cout << "vector iter:\t" << comp_it.first << " (std), " << comp_it.second << " (ft)\n";
	passed_tests.first += printResult(comp_char.first == comp_char.second
								&& comp_int.first == comp_int.second
								&& comp_float.first == comp_float.second
								&& comp_it.first == comp_it.second);
}
