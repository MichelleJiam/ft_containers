/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_set.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 15:52:37 by mjiam         #+#    #+#                 */
/*   Updated: 2022/04/19 21:51:06 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

#define T1 int
#define T2 std::string

typedef IMPL::set<T1>	t_iset;
typedef IMPL::set<T2>	t_sset;

template <typename T>
void    printSet(T& base_set, bool print_contents = true,
					std::string const& cntr_name = std::string(),
					std::string const& test_case = std::string()) {
	if (!test_case.empty())
		printTestCase(test_case);
	if (!cntr_name.empty())
		std::cout << "[ " << cntr_name << " ]\n";
	std::cout << "size: " << base_set.size() << std::endl;
	std::cout << "max_size: " << base_set.max_size() << std::endl;
	if (print_contents) {
		std::cout << "contents:\n";
		for (typename T::iterator it = base_set.begin(); it != base_set.end(); ++it)
			std::cout << "\t" << *it << std::endl;
		std::cout << std::endl;
	}
}

template <typename T>
void	test_set_constructors(size_t size) {
	T	empty_set;
	printSet(empty_set, (size < 100), "empty_set");

	std::list<T1> list(size, 42);
	T	range_set(list.begin(), list.end());
	printSet(range_set, (size < 100), "range_set");

	T	copy_set(range_set);
	printSet(copy_set, (size < 100), "copy_set");

	assert(empty_set.size() == 0
			&& range_set.size() == copy_set.size());
}

template <typename T>
void	test_set_empty(size_t size) {
	T	set1;

	std::cout << std::boolalpha;
	std::cout << "set 1 is empty: " << set1.empty() << std::endl;
	printSet(set1, (size < 100), "set1");

	std::list<T1>	list(size, 42);
	T				set2(list.begin(), list.end());
	std::cout << "set 2 is empty: " << set2.empty() << std::endl;
	printSet(set2, (size < 100), "set2");
}

template <typename T>
void	test_set_clear(size_t size) {
	printTestCase("clear() on set of [size] size");

	std::list<T1>	list(size, 42);
	T				set(list.begin(), list.end());
	set.clear();
	printSet(set, (size < 100), "set");
	
	assert(set.size() == 0);
}

template <typename Pair>
void	printInsertReturn(Pair ret, bool newline = false) {
	std::cout << *(ret.first) << ", " << std::boolalpha << ret.second;
	if (newline)
		std::cout << "\n";
}

template <typename T>
void	test_set_insert(size_t size) {
	IMPL::pair<typename T::iterator, bool>	ret;
	T	set1, set2;

	ret = set1.insert("hello");
	std::cout << "insert(hello) returns: "; printInsertReturn(ret, true);
	ret = set1.insert("42");
	std::cout << "insert(42) returns: "; printInsertReturn(ret, true);
	ret = set1.insert("world");
	std::cout << "insert(world) returns: "; printInsertReturn(ret, true);
	ret = set1.insert("world");
	std::cout << "insert(world) (2nd time) returns: "; printInsertReturn(ret, true);
	std::cout << std::endl;
	printSet(set1, (size < 100), "set1");

	set2.insert(set1.begin(), set1.end());
	printSet(set2, (size < 100), "set2");

	t_iset set3;

	for (size_t i = 0; i < size; i++)
		set3.insert(i + 1);
	set3.insert(0);
	printSet(set3, (size < 100), "set3");
}

void test_set() {
#ifndef SIMPLE
	printHeader("testing set");
#endif

	// constructor test
	benchmarkFunction_stress(test_set_constructors<t_iset>, "default/range/copy constructors");
	
	// empty test
	benchmarkFunction_stress(test_set_empty<t_iset>, "empty");
	
	// clear test
	benchmarkFunction_stress(test_set_clear<t_iset>, "insert");

	// insert test
	benchmarkFunction_stress(test_set_insert<t_sset>, "insert");
}
