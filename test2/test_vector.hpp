/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_vector.hpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 17:38:26 by mjiam         #+#    #+#                 */
/*   Updated: 2022/01/25 17:52:30 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_VECTOR_HPP
#define TEST_VECTOR_HPP

#include "tester.hpp"
#include "vector.hpp"

template <class T, typename S>
void    printVector(S &out, T &base_vec, int &test_count,
					std::string const &test_name = std::string())
{
	if (!test_name.empty())
		printTest(out, test_name, test_count);
	out << "\n- Vector -\n";
	out << "capacity: " << base_vec.capacity() << std::endl;
	out << "size:     " << base_vec.size() << std::endl;
	out << "contents: [";
	for (unsigned i = 0; i < base_vec.size(); i++)
		out << ' ' << base_vec[i];
	out << " ]\n";
}

template <typename S>
void test_vector(IMPL::pair<int,int> &passed_tests, S &out) {
	printHeader(out, "vector");

	IMPL::vector<int>		base_vec;

	// push_back test
	printTest(out, "push_back", passed_tests.second);
	for (int i = 1; i <= 10; i++)
		base_vec.push_back(i);
	printVector(out, base_vec, passed_tests.second);
	// passed_tests.first += printVector(out, base_vec, std_vec, passed_tests.second, "push_back");

	// empty test
	printTest(out, "empty", passed_tests.second);
	out << std::boolalpha << "is base_vec empty: " << base_vec.empty() << std::endl;
	printVector(out, base_vec, passed_tests.second);
	// passed_tests.first += printResult(base_vec.empty() == std_vec.empty());

	// pop_back test
	printTest(out, "pop_back", passed_tests.second);
	base_vec.pop_back();
	printVector(out, base_vec, passed_tests.second);
	// passed_tests.first += printVector(out, base_vec, std_vec, passed_tests.second, "pop_back");

	// fill constructor test
	printTest(out, "fill constructor", passed_tests.second);
	IMPL::vector<int>	fill_vec(4, 42);
	printVector(out, fill_vec, passed_tests.second);
	// passed_tests.first += printVector(out, fill_vec, std_fill_vec, passed_tests.second, "fill constructor");

	// copy constructor test
	printTest(out, "copy constructor", passed_tests.second);
	IMPL::vector<int>	copy_vec(base_vec);
	printVector(out, copy_vec, passed_tests.second);
	// passed_tests.first += printVector(copy_vec, std_copy_vec, passed_tests.second, "copy constructor");

	// range constructor test
	printTest(out, "range constructor", passed_tests.second);
	IMPL::vector<int>	range_vec(fill_vec.begin(), fill_vec.end() - 2);
	printVector(out, range_vec, passed_tests.second);
	// passed_tests.first += printVector(range_vec, std_range_vec, passed_tests.second, "range constructor");

	// clear test
	printTest(out, "clear", passed_tests.second);
	copy_vec.clear();
	printVector(out, copy_vec, passed_tests.second);
	// passed_tests.first += printVector(copy_vec, std_copy_vec, passed_tests.second, "clear");
	
	// reserve test
	printTest(out, "reserve", passed_tests.second);
	size_t   oldcap = fill_vec.capacity();
	fill_vec.reserve(10);
	printVector(out, fill_vec, passed_tests.second);
	// passed_tests.first += printVector(out, fill_vec, std_fill_vec, passed_tests.second, "reserve");
	out << "fill vec capacity was " << oldcap << ", is now " << fill_vec.capacity() << ".\n";
	
	// insert test
	printTest(out, "insert", passed_tests.second);
	IMPL::vector<int>::iterator it;
	it = fill_vec.end();
	fill_vec.insert(it - 1, 2, 13);
	// passed_tests.first += printVector(out, fill_vec, std_fill_vec, passed_tests.second, "insert");
	printVector(out, fill_vec, passed_tests.second);
	it = fill_vec.begin();
	fill_vec.insert(it + 2, 2, 0);
	printVector(out, fill_vec, passed_tests.second);
	// passed_tests.first += printVector(out, fill_vec, std_fill_vec, passed_tests.second, "insert");

	// resize test
	printTest(out, "resize", passed_tests.second);
	fill_vec.resize(8, 7);
	printVector(out, fill_vec, passed_tests.second);
	// passed_tests.first += printVector(out, fill_vec, std_fill_vec, passed_tests.second, "resize");

	// erase test
	printTest(out, "erase", passed_tests.second);
	fill_vec.erase(fill_vec.end() - 2);
	printVector(out, fill_vec, passed_tests.second);
	// passed_tests.first += printVector(out, fill_vec, std_fill_vec, passed_tests.second, "erase");
	fill_vec.erase(fill_vec.end() - 3, fill_vec.end() - 1);
	fill_vec.erase(fill_vec.begin() + 2, fill_vec.begin() + 4);
	printVector(out, fill_vec, passed_tests.second);
	// passed_tests.first += printVector(out, fill_vec, std_fill_vec, passed_tests.second, "erase range");

	// swap test
	printTest(out, "swap", passed_tests.second);
	fill_vec.swap(base_vec);
	out << "fill_vector now looks like:\n";
	printVector(out, fill_vec, passed_tests.second);
	// passed_tests.first += printVector(out, fill_vec, std_fill_vec, passed_tests.second);
	out << "\nbase vector now looks like:\n";
	printVector(out, base_vec, passed_tests.second);
}

#endif
