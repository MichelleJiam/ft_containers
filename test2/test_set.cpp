/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_set.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 15:52:37 by mjiam         #+#    #+#                 */
/*   Updated: 2022/06/09 21:29:32 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

#define T1 int
#define T2 std::string
#define T3 char

typedef IMPL::set<T1>	t_iset;
typedef IMPL::set<T2>	t_sset;
typedef IMPL::set<T3>	t_cset;

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

	T	assign_set;
	assign_set = range_set;
	printSet(assign_set, (size < 100), "assign_set");

	assert(empty_set.size() == 0
			&& range_set.size() == copy_set.size()
			&& assign_set.size() == range_set.size());
}

// doesn't use `size` because complexity is constant
template <typename T>
void	test_set_empty(size_t size) {
	std::list<T1>	list(size, 42);
	T				set1(list.begin(), list.end());
	
	std::cout << std::boolalpha;
	std::cout << "is set1 empty: " << set1.empty() << std::endl;
	printSet(set1, (size < 100), "set1", "empty on filled set");

	T set2;
	std::cout << "is set2 empty: " << set2.empty() << std::endl;
	printSet(set2, (size < 100), "set2", "empty on default constructed set");

	set2 = set1;
	std::cout << "is set2 empty: " << set2.empty() << std::endl;
	printSet(set2, (size < 100), "set2", "empty on copy assigned set");
	
	set2.clear();
	std::cout << "is set2 empty: " << set2.empty() << std::endl;
	printSet(set2, (size < 100), "set2", "empty after clear");
	(void)size;
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

template <typename T, typename P>
static void	test_set_insert_helper(T &set, P param) {
	IMPL::pair<typename T::iterator, bool> ret;

	ret = set.insert(param);
	std::cout << "insert [" << param << "]\n";
	if (ret.second == true)
		std::cout << "success - [" << *(ret.first) << "] inserted\n\n";
	else
		std::cout << "failed - [" << *(ret.first) << "] already in set\n\n";
}

template <typename T>
void	test_set_insert(size_t size) {
	IMPL::pair<typename T::iterator, bool>	ret;
	T	set1, set2;

	test_set_insert_helper(set1, "hello");
	test_set_insert_helper(set1, "42");
	test_set_insert_helper(set1, "world");
	test_set_insert_helper(set1, "world");
	printSet(set1, (size < 100), "set1", "single insert");

	set2.insert(set1.begin(), set1.end());
	printSet(set2, (size < 100), "set2", "range insert(set1.begin, set1.end)");

	t_iset set3;

	for (size_t i = 0; i < size; i++)
		set3.insert(i + 1);
	set3.insert(set3.end(), 0);
	printSet(set3, (size < 100), "set3", "insert with hint");
}

template <typename T>
void	test_set_erase(size_t size) {
	std::list<T1>	list(size, 42);
	T				set(list.begin(), list.end());
	printSet(set, (size < 100), "set before erase");

	std::cout << "erase(" << (size / 2) << ")\n";
	std::cout << "set size before: " << set.size() << std::endl;
	size_t ret = set.erase(size / 2);
	std::cout << "elements erased: " << ret << std::endl;
	std::cout << "set size after: " << set.size() << std::endl << std::endl;

	std::cout << "erase(begin)\n";
	std::cout << "set size before: " << set.size() << std::endl;
	set.erase(set.begin());
	std::cout << "set size after: " << set.size() << std::endl << std::endl;

	std::cout << "erase([non-existant key])\n";
	std::cout << "set size before: " << set.size() << std::endl;
	set.erase(120);
	std::cout << "set size after: " << set.size() << std::endl << std::endl;

	std::cout << "erase(begin, end)\n";
	std::cout << "set size before: " << set.size() << std::endl;
	set.erase(set.begin(), set.end());
	std::cout << "set size after: " << set.size() << std::endl << std::endl;

	printSet(set, (size < 100), "set after erase");
}

// doesn't use `size` because complexity is constant
template <typename T>
void	test_set_compare(size_t size) {
	printTestCase("key_comp & value_comp on identical and different keys");

	T	set1, set2;

	set1.insert('a');
	set1.insert('b');
	set1.insert('e');
	
	set2.insert('a');
	set2.insert('c');
	set2.insert('d');

	typename T::iterator it1 = set1.begin(), it2 = set2.begin();
	std::cout << std::boolalpha;
	while (it1 != set1.end() && it2 != set2.end()) {
		std::cout << *it1 << " vs "<< *it2 << "\n"
			<< "key_comp: " << set1.key_comp()(*it1, *it2)
			<< " | value_comp: " << set1.value_comp()(*it1, *it2)
			<< "\n\n";
		++it1, ++it2;
	}
	(void)size;
}

void test_set() {
#ifndef SIMPLE
	printHeader("set");
#else
	std::cout << "SET\n";
#endif

	// constructor test
	benchmarkFunction_stress(test_set_constructors<t_iset>, "default/range/copy constructors");
	
	// empty test
	benchmarkFunction(test_set_empty<t_iset>, "empty");
	
	// clear test
	benchmarkFunction_stress(test_set_clear<t_iset>, "clear");

	// insert test
	benchmarkFunction_stress(test_set_insert<t_sset>, "insert");
		
	// erase test
	benchmarkFunction_stress(test_set_erase<t_iset>, "erase");

	// key/value_comp test
	benchmarkFunction(test_set_compare<t_cset>, "key/value_comp");
}
