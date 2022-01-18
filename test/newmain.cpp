/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   newmain.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/30 18:13:43 by mjiam         #+#    #+#                 */
/*   Updated: 2022/01/18 21:41:39 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"
#include "vector.hpp"
#include "../utils/pair.hpp"
#include "../utils/lexicographical_compare.hpp"

#define lex_comp lexicographical_compare

template <class T>
int    printVector(ft::vector<T> &ft_vec, std::vector<T> &std_vec,
			int &test_count, std::string const &test_name = std::string())
{
	int error = 0;

	if (!test_name.empty())
		printTest(test_name, test_count);
	std::cout << "- STL vector -\n";
	std::cout << "capacity: " << std_vec.capacity() << std::endl;
	std::cout << "size:     " << std_vec.size() << std::endl;
	std::cout << "contents: [";
	for (unsigned i = 0; i < std_vec.size(); i++)
		std::cout << ' ' << std_vec[i];
	std::cout << " ]\n";
	std::cout << "\n- FT vector -\n";
	std::cout << "capacity: " << ft_vec.capacity() << std::endl;
	std::cout << "size:     " << ft_vec.size() << std::endl;
	std::cout << "contents: [";
	for (unsigned i = 0; i < ft_vec.size(); i++) {
		std::cout << ' ' << ft_vec[i];
		error += isNotEqual(ft_vec[i], std_vec[i]);
	}
	std::cout << " ]\n";
	return printResult(std_vec.size() == ft_vec.size()
		&& std_vec.capacity() == ft_vec.capacity()
		&& error == 0);
}

int main() {
	int					test_count = 0;
	int					pass_count = 0;

	ft::vector<int>		ft_vec;
	std::vector<int>	std_vec;

	// push_back test
	for (int i = 1; i <= 10; i++){
		ft_vec.push_back(i);
		std_vec.push_back(i);
	}
	pass_count += printVector(ft_vec, std_vec, test_count, "push_back");

	// empty test
	printTest("empty", test_count);
	std::cout << std::boolalpha << "is ft_vec empty: " << ft_vec.empty() << std::endl;
	std::cout << std::boolalpha << "is std_vec empty: " << std_vec.empty() << std::endl;
	pass_count += printResult(ft_vec.empty() == std_vec.empty());

	// pop_back test
	ft_vec.pop_back();
	std_vec.pop_back();
	pass_count += printVector(ft_vec, std_vec, test_count, "pop_back");

	// fill constructor test
	ft::vector<int>     ft_fill_vec(4, 42);
	std::vector<int>    std_fill_vec(4, 42);
	pass_count += printVector(ft_fill_vec, std_fill_vec, test_count, "fill constructor");

	// copy constructor test
	ft::vector<int>		ft_copy_vec(ft_vec);
	std::vector<int>		std_copy_vec(std_vec);
	pass_count += printVector(ft_copy_vec, std_copy_vec, test_count, "copy constructor");

	// clear test
	ft_copy_vec.clear();
	std_copy_vec.clear();
	pass_count += printVector(ft_copy_vec, std_copy_vec, test_count, "clear");
	
	// reserve test
	size_t   ft_oldcap = ft_fill_vec.capacity(), std_oldcap = std_fill_vec.capacity();
	ft_fill_vec.reserve(10);
	std_fill_vec.reserve(10);
	pass_count += printVector(ft_fill_vec, std_fill_vec, test_count, "reserve");
	std::cout << "ft fill vec capacity was " << ft_oldcap << ", is now " << ft_fill_vec.capacity() << ".\n";
	std::cout << "std fill vec capacity was " << std_oldcap << ", is now "  << std_fill_vec.capacity() << ".\n";

	// insert test
	ft::vector<int>::iterator ft_it;
	std::vector<int>::iterator std_it;
	ft_it = ft_fill_vec.end();
	std_it = std_fill_vec.end();
	ft_fill_vec.insert(ft_it - 1, 2, 13);
	std_fill_vec.insert(std_it - 1, 2, 13);
	pass_count += printVector(ft_fill_vec, std_fill_vec, test_count, "insert");
	ft_it = ft_fill_vec.begin();
	std_it = std_fill_vec.begin();
	ft_fill_vec.insert(ft_it + 2, 2, 0);
	std_fill_vec.insert(std_it + 2, 2, 0);
	pass_count += printVector(ft_fill_vec, std_fill_vec, test_count, "insert");

	// resize test
	ft_fill_vec.resize(8, 7);
	std_fill_vec.resize(8, 7);
	pass_count += printVector(ft_fill_vec, std_fill_vec, test_count, "resize");

	// erase test
	ft_fill_vec.erase(ft_fill_vec.end() - 2);
	std_fill_vec.erase(std_fill_vec.end() - 2);
	pass_count += printVector(ft_fill_vec, std_fill_vec, test_count, "erase");
	ft_fill_vec.erase(ft_fill_vec.end() - 3, ft_fill_vec.end() - 1);
	std_fill_vec.erase(std_fill_vec.end() - 3, std_fill_vec.end() - 1);
	ft_fill_vec.erase(ft_fill_vec.begin() + 2, ft_fill_vec.begin() + 4);
	std_fill_vec.erase(std_fill_vec.begin() + 2, std_fill_vec.begin() + 4);
	pass_count += printVector(ft_fill_vec, std_fill_vec, test_count, "erase range");

	// swap test
	ft_fill_vec.swap(ft_vec);
	std_fill_vec.swap(std_vec);
	printTest("swap", test_count);
	std::cout << "fill_vectors now look like:\n";
	pass_count += printVector(ft_fill_vec, std_fill_vec, test_count);
	std::cout << "\nbase vectors now look like:\n";
	printVector(ft_vec, std_vec, test_count);

	// pair/make_pair test
	ft::pair<int,int>	p1 = ft::make_pair(ft_fill_vec[1], ft_vec[0]);
	std::pair<int,int>	p2 = std::make_pair(ft_fill_vec[1], ft_vec[0]);
	printTest("pair", test_count);
	std::cout << "Making pair with values: " << ft_fill_vec[1] << ", "
		<< ft_vec[0] << std::endl;
	std::cout << "Value of (ft)p1 is (" << p1.first << ", " << p1.second << ")\n";
	std::cout << "Value of (std)p2 is (" << p2.first << ", " << p2.second << ")\n";
	pass_count += printResult(p1.first == p2.first && p1.second == p2.second);

	// lexicographical_compare test
	std::string	s1 = "Apple";
	std::string s2 = "apple";
	printTest("lexicographical_compare", test_count);
	std::cout << "Comparing strings: " << s1 << " & " << s2 << std::endl << std::boolalpha;
	ft::pair<bool,bool> comp1(
			std::lex_comp(s1.begin(), s1.end(), s2.begin(), s2.end()),
			ft::lex_comp(s1.begin(), s1.end(), s2.begin(), s2.end()));
	ft::pair<bool,bool> comp2(
			std::lex_comp(s1.begin(), s1.end(), s2.begin(), s2.end(), mycomp),
			ft::lex_comp(s1.begin(), s1.end(), s2.begin(), s2.end(), mycomp));
	std::cout << "Default comparison returns: " << comp1.first << " (std), "
		<< comp1.second << " (ft)\n";
	std::cout << "Case-insensitive custom comparison returns: " << comp2.first << " (std), "
		<< comp2.second << " (ft)\n";
	pass_count += printResult(comp1.first == comp1.second && comp2.first == comp2.second);
	printPassing(pass_count, test_count);
	
	// ft::vector<int>     ft_range_vec(ft_fill_vec.begin(), ft_fill_vec.end());
	// std::vector<int>    std_range_vec(std_fill_vec.begin(), std_fill_vec.end());
	// printVector(ft_range_vec, std_range_vec);

	return 0;
}