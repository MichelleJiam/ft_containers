/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   newmain.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/30 18:13:43 by mjiam         #+#    #+#                 */
/*   Updated: 2022/01/18 18:18:50 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"
#include "vector.hpp"
#include "../utils/pair.hpp"
#include "../utils/lexicographical_compare.hpp"

#define lex_comp lexicographical_compare

template <class T>
int    printVector(std::string const test_name, int &test_count,
			ft::vector<T> &ftvec, std::vector<T> &stdvec)
{
	int error = 0;

	printTest(test_name, test_count);
	std::cout << "- STL vector -\n";
	std::cout << "capacity: " << stdvec.capacity() << std::endl;
	std::cout << "size:     " << stdvec.size() << std::endl;
	std::cout << "contents: [";
	for (unsigned i = 0; i < stdvec.size(); i++)
		std::cout << ' ' << stdvec[i];
	std::cout << " ]\n";
	std::cout << "\n- FT vector -\n";
	std::cout << "capacity: " << ftvec.capacity() << std::endl;
	std::cout << "size:     " << ftvec.size() << std::endl;
	std::cout << "contents: [";
	for (unsigned i = 0; i < ftvec.size(); i++) {
		std::cout << ' ' << ftvec[i];
		error += isNotEqual(ftvec[i], stdvec[i]);
	}
	std::cout << " ]\n";
	return printResult(stdvec.size() == ftvec.size()
		&& stdvec.capacity() == ftvec.capacity()
		&& error == 0);
}

int main() {
	int					test_count = 0;
	int					pass_count = 0;

	ft::vector<int>		ftvec;
	std::vector<int>	stdvec;

	// push_back test
	for (int i = 1; i <= 10; i++){
		ftvec.push_back(i);
		stdvec.push_back(i);
	}
	pass_count += printVector("push_back", test_count, ftvec, stdvec);

	// empty test
	printTest("empty", test_count);
	std::cout << std::boolalpha << "is ftvec empty: " << ftvec.empty() << std::endl;
	std::cout << std::boolalpha << "is stdvec empty: " << stdvec.empty() << std::endl;
	pass_count += printResult(ftvec.empty() == stdvec.empty());

	// pop_back test
	ftvec.pop_back();
	stdvec.pop_back();
	pass_count += printVector("pop_back", test_count, ftvec, stdvec);

	// fill constructor test
	ft::vector<int>     ft_fill_vec(4, 42);
	std::vector<int>    std_fill_vec(4, 42);
	pass_count += printVector("fill constructor", test_count, ft_fill_vec, std_fill_vec);

	// copy constructor test
	ft::vector<int>		ft_copy_vec(ftvec);
	std::vector<int>		std_copy_vec(stdvec);
	pass_count += printVector("copy constructor", test_count, ft_copy_vec, std_copy_vec);

	// clear test
	ft_copy_vec.clear();
	std_copy_vec.clear();
	pass_count += printVector("clear", test_count, ft_copy_vec, std_copy_vec);
	
	// reserve test
	size_t   ft_oldcap = ft_fill_vec.capacity(), std_oldcap = std_fill_vec.capacity();
	ft_fill_vec.reserve(10);
	std_fill_vec.reserve(10);
	pass_count += printVector("reserve", test_count, ft_fill_vec, std_fill_vec);
	std::cout << "ft fill vec capacity was " << ft_oldcap << ", is now " << ft_fill_vec.capacity() << ".\n";
	std::cout << "std fill vec capacity was " << std_oldcap << ", is now "  << std_fill_vec.capacity() << ".\n";

	// insert test
	ft::vector<int>::iterator ft_it;
	std::vector<int>::iterator std_it;
	ft_it = ft_fill_vec.end();
	std_it = std_fill_vec.end();
	ft_fill_vec.insert(ft_it - 1, 2, 13);
	std_fill_vec.insert(std_it - 1, 2, 13);
	pass_count += printVector("insert", test_count, ft_fill_vec, std_fill_vec);
	ft_it = ft_fill_vec.begin();
	std_it = std_fill_vec.begin();
	ft_fill_vec.insert(ft_it + 2, 2, 0);
	std_fill_vec.insert(std_it + 2, 2, 0);
	pass_count += printVector("insert", test_count, ft_fill_vec, std_fill_vec);

	// resize test
	ft_fill_vec.resize(8, 7);
	std_fill_vec.resize(8, 7);
	pass_count += printVector("resize", test_count, ft_fill_vec, std_fill_vec);

	// erase test
	ft_fill_vec.erase(ft_fill_vec.end() - 2);
	std_fill_vec.erase(std_fill_vec.end() - 2);
	pass_count += printVector("erase", test_count, ft_fill_vec, std_fill_vec);
	ft_fill_vec.erase(ft_fill_vec.end() - 3, ft_fill_vec.end() - 1);
	std_fill_vec.erase(std_fill_vec.end() - 3, std_fill_vec.end() - 1);
	ft_fill_vec.erase(ft_fill_vec.begin() + 2, ft_fill_vec.begin() + 4);
	std_fill_vec.erase(std_fill_vec.begin() + 2, std_fill_vec.begin() + 4);
	pass_count += printVector("erase range", test_count, ft_fill_vec, std_fill_vec);

	// pair/make_pair test
	ft::pair<int,int>	p1 = ft::make_pair(ft_fill_vec[1], ftvec[0]);
	std::pair<int,int>	p2 = std::make_pair(ft_fill_vec[1], ftvec[0]);
	printTest("pair", test_count);
	std::cout << "Making pair with values: " << ft_fill_vec[1] << ", "
		<< ftvec[0] << std::endl;
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