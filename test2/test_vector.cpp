/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_vector.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 16:54:47 by mjiam         #+#    #+#                 */
/*   Updated: 2022/01/20 21:37:56 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"
#include "vector.hpp"

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
		error += is_not_equal(ft_vec[i], std_vec[i]);
	}
	std::cout << " ]\n";
	return printResult(std_vec.size() == ft_vec.size()
		&& std_vec.capacity() == ft_vec.capacity()
		&& error == 0);
}

void test_vector(ft::pair<int,int> &passed_tests, std::ofstream &outfile) {
	printHeader("vector");
	outfile << "hello\n";
	ft::vector<int>		ft_vec;
	std::vector<int>	std_vec;

	// push_back test
	for (int i = 1; i <= 10; i++){
		ft_vec.push_back(i);
		std_vec.push_back(i);
	}
	passed_tests.first += printVector(ft_vec, std_vec, passed_tests.second, "push_back");

	// empty test
	printTest("empty", passed_tests.second);
	std::cout << std::boolalpha << "is ft_vec empty: " << ft_vec.empty() << std::endl;
	std::cout << std::boolalpha << "is std_vec empty: " << std_vec.empty() << std::endl;
	passed_tests.first += printResult(ft_vec.empty() == std_vec.empty());

	// pop_back test
	ft_vec.pop_back();
	std_vec.pop_back();
	passed_tests.first += printVector(ft_vec, std_vec, passed_tests.second, "pop_back");

	// fill constructor test
	ft::vector<int>     ft_fill_vec(4, 42);
	std::vector<int>    std_fill_vec(4, 42);
	passed_tests.first += printVector(ft_fill_vec, std_fill_vec, passed_tests.second, "fill constructor");

	// copy constructor test
	ft::vector<int>		ft_copy_vec(ft_vec);
	std::vector<int>		std_copy_vec(std_vec);
	passed_tests.first += printVector(ft_copy_vec, std_copy_vec, passed_tests.second, "copy constructor");

	// range test
	ft::vector<int>     ft_range_vec(ft_fill_vec.begin(), ft_fill_vec.end() - 2);
	std::vector<int>    std_range_vec(std_fill_vec.begin(), std_fill_vec.end() - 2);
	passed_tests.first += printVector(ft_range_vec, std_range_vec, passed_tests.second, "range constructor");

	// clear test
	ft_copy_vec.clear();
	std_copy_vec.clear();
	passed_tests.first += printVector(ft_copy_vec, std_copy_vec, passed_tests.second, "clear");
	
	// reserve test
	size_t   ft_oldcap = ft_fill_vec.capacity(), std_oldcap = std_fill_vec.capacity();
	ft_fill_vec.reserve(10);
	std_fill_vec.reserve(10);
	passed_tests.first += printVector(ft_fill_vec, std_fill_vec, passed_tests.second, "reserve");
	std::cout << "ft fill vec capacity was " << ft_oldcap << ", is now " << ft_fill_vec.capacity() << ".\n";
	std::cout << "std fill vec capacity was " << std_oldcap << ", is now "  << std_fill_vec.capacity() << ".\n";

	// insert test
	ft::vector<int>::iterator ft_it;
	std::vector<int>::iterator std_it;
	ft_it = ft_fill_vec.end();
	std_it = std_fill_vec.end();
	ft_fill_vec.insert(ft_it - 1, 2, 13);
	std_fill_vec.insert(std_it - 1, 2, 13);
	passed_tests.first += printVector(ft_fill_vec, std_fill_vec, passed_tests.second, "insert");
	ft_it = ft_fill_vec.begin();
	std_it = std_fill_vec.begin();
	ft_fill_vec.insert(ft_it + 2, 2, 0);
	std_fill_vec.insert(std_it + 2, 2, 0);
	passed_tests.first += printVector(ft_fill_vec, std_fill_vec, passed_tests.second, "insert");

	// resize test
	ft_fill_vec.resize(8, 7);
	std_fill_vec.resize(8, 7);
	passed_tests.first += printVector(ft_fill_vec, std_fill_vec, passed_tests.second, "resize");

	// erase test
	ft_fill_vec.erase(ft_fill_vec.end() - 2);
	std_fill_vec.erase(std_fill_vec.end() - 2);
	passed_tests.first += printVector(ft_fill_vec, std_fill_vec, passed_tests.second, "erase");
	ft_fill_vec.erase(ft_fill_vec.end() - 3, ft_fill_vec.end() - 1);
	std_fill_vec.erase(std_fill_vec.end() - 3, std_fill_vec.end() - 1);
	ft_fill_vec.erase(ft_fill_vec.begin() + 2, ft_fill_vec.begin() + 4);
	std_fill_vec.erase(std_fill_vec.begin() + 2, std_fill_vec.begin() + 4);
	passed_tests.first += printVector(ft_fill_vec, std_fill_vec, passed_tests.second, "erase range");

	// swap test
	ft_fill_vec.swap(ft_vec);
	std_fill_vec.swap(std_vec);
	printTest("swap", passed_tests.second);
	std::cout << "fill_vectors now look like:\n";
	passed_tests.first += printVector(ft_fill_vec, std_fill_vec, passed_tests.second);
	std::cout << "\nbase vectors now look like:\n";
	printVector(ft_vec, std_vec, passed_tests.second);
}