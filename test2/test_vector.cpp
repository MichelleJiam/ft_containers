/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_vector.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 16:54:47 by mjiam         #+#    #+#                 */
/*   Updated: 2022/01/25 22:30:36 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"
#include "vector.hpp"

template <class T>
void    printVector(IMPL::vector<T> &base_vec, int &test_count,
					std::string const &test_name = std::string())
{
	if (!test_name.empty())
		printTest(test_name, test_count);
	std::cout << "\ncapacity: " << base_vec.capacity() << std::endl;
	std::cout << "size:     " << base_vec.size() << std::endl;
	std::cout << "contents: [";
	for (unsigned i = 0; i < base_vec.size(); i++)
		std::cout << ' ' << base_vec[i];
	std::cout << " ]\n";
}

void test_vector(IMPL::pair<int,int> &passed_tests) {
#ifndef SIMPLE
	printHeader("testing vector");
#endif

	IMPL::vector<int>		base_vec;
	
	// push_back test
	printTest("push_back", passed_tests.second);
	clock_t start = clock();
	for (int i = 1; i <= 10; i++)
		base_vec.push_back(i);
	printVector(base_vec, passed_tests.second);
	std::cout << "Duration of operation: " << ((clock() - start) / (double)CLOCKS_PER_SEC) * 1000 << "seconds." << std::endl;

	// empty test
	printTest("empty", passed_tests.second);
	start = clock();
	std::cout << std::boolalpha << "is base_vec empty: " << base_vec.empty() << std::endl;
	printVector(base_vec, passed_tests.second);
	std::cout << "Duration of operation: " << ((clock() - start) / (double)CLOCKS_PER_SEC) * 1000 << "seconds." << std::endl;

	// pop_back test
	printTest("pop_back", passed_tests.second);
	start = clock();
	base_vec.pop_back();
	printVector(base_vec, passed_tests.second);
	std::cout << "Duration of operation: " << ((clock() - start) / (double)CLOCKS_PER_SEC) * 1000 << "seconds." << std::endl;

	// fill constructor test
	printTest("fill constructor", passed_tests.second);
	start = clock();
	IMPL::vector<int>	fill_vec(4, 42);
	printVector(fill_vec, passed_tests.second);
	std::cout << "Duration of operation: " << ((clock() - start) / (double)CLOCKS_PER_SEC) * 1000 << "seconds." << std::endl;

	// copy constructor test
	printTest("copy constructor", passed_tests.second);
	start = clock();
	IMPL::vector<int>	copy_vec(base_vec);
	printVector(copy_vec, passed_tests.second);
	std::cout << "Duration of operation: " << ((clock() - start) / (double)CLOCKS_PER_SEC) * 1000 << "seconds." << std::endl;

	// range constructor test
	printTest("range constructor", passed_tests.second);
	start = clock();
	IMPL::vector<int>	range_vec(fill_vec.begin(), fill_vec.end() - 2);
	printVector(range_vec, passed_tests.second);
	std::cout << "Duration of operation: " << ((clock() - start) / (double)CLOCKS_PER_SEC) * 1000 << "seconds." << std::endl;

	// clear test
	printTest("clear", passed_tests.second);
	start = clock();
	copy_vec.clear();
	printVector(copy_vec, passed_tests.second);
	std::cout << "Duration of operation: " << ((clock() - start) / (double)CLOCKS_PER_SEC) * 1000 << "seconds." << std::endl;
	
	// reserve test
	printTest("reserve", passed_tests.second);
	start = clock();
	size_t   oldcap = fill_vec.capacity();
	fill_vec.reserve(10);
	printVector(fill_vec, passed_tests.second);
	std::cout << "Duration of operation: " << ((clock() - start) / (double)CLOCKS_PER_SEC) * 1000 << "seconds." << std::endl;
	std::cout << "fill vec capacity was " << oldcap << ", is now " << fill_vec.capacity() << ".\n";
	
	// insert test
	printTest("insert", passed_tests.second);
	start = clock();
	IMPL::vector<int>::iterator it;
	it = fill_vec.end();
	fill_vec.insert(it - 1, 2, 13);
	std::cout << "Duration of operation: " << ((clock() - start) / (double)CLOCKS_PER_SEC) * 1000 << "seconds." << std::endl;
	printVector(fill_vec, passed_tests.second);
	it = fill_vec.begin();
	fill_vec.insert(it + 2, 2, 0);
	printVector(fill_vec, passed_tests.second);
	std::cout << "Duration of operation: " << ((clock() - start) / (double)CLOCKS_PER_SEC) * 1000 << "seconds." << std::endl;

	// resize test
	printTest("resize", passed_tests.second);
	start = clock();
	fill_vec.resize(8, 7);
	printVector(fill_vec, passed_tests.second);
	std::cout << "Duration of operation: " << ((clock() - start) / (double)CLOCKS_PER_SEC) * 1000 << "seconds." << std::endl;

	// erase test
	printTest("erase", passed_tests.second);
	start = clock();
	fill_vec.erase(fill_vec.end() - 2);
	printVector(fill_vec, passed_tests.second);
	std::cout << "Duration of operation: " << ((clock() - start) / (double)CLOCKS_PER_SEC) * 1000 << "seconds." << std::endl;
	fill_vec.erase(fill_vec.end() - 3, fill_vec.end() - 1);
	fill_vec.erase(fill_vec.begin() + 2, fill_vec.begin() + 4);
	printVector(fill_vec, passed_tests.second);
	std::cout << "Duration of operation: " << ((clock() - start) / (double)CLOCKS_PER_SEC) * 1000 << "seconds." << std::endl;

	// swap test
	printTest("swap", passed_tests.second);
	start = clock();
	fill_vec.swap(base_vec);
	std::cout << "fill_vector now looks like:\n";
	printVector(fill_vec, passed_tests.second);
	std::cout << "Duration of operation: " << ((clock() - start) / (double)CLOCKS_PER_SEC) * 1000 << "seconds." << std::endl;
	std::cout << "\nbase vector now looks like:\n";
	printVector(base_vec, passed_tests.second);
}