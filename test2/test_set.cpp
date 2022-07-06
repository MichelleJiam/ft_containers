/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_set.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 15:52:37 by mjiam         #+#    #+#                 */
/*   Updated: 2022/06/16 23:10:02 by mjiam         ########   odam.nl         */
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

template <typename Iterator>
void	printEndorVal(Iterator it, Iterator end, bool print_newline = true) {
	if (it == end)
		std::cout << "end";
	else
		std::cout << *it;
	if (print_newline)
		std::cout << "\n";
}

template <typename T>
void	test_set_constructors(size_t size) {
	printTestCase("default/copy/range constructors & assignment op");
	
	T	empty_set;
	printSet(empty_set, (size < 100), "empty_set");

	std::list<T1> list;
	for (size_t i = 0; i < size; i++)
		list.push_back(i + 1);
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
	T	set1;
	for (size_t i = 0; i < size; i++)
		set1.insert(i + 1);
	
	std::cout << std::boolalpha;
	printSet(set1, (size < 100), "set1", "empty on filled set");
	std::cout << "is set1 empty: " << set1.empty() << std::endl;

	T set2;
	printSet(set2, (size < 100), "set2", "empty on default constructed set");
	std::cout << "is set2 empty: " << set2.empty() << std::endl;

	set2 = set1;
	printSet(set2, (size < 100), "set2", "empty on copy assigned set");
	std::cout << "is set2 empty: " << set2.empty() << std::endl;
	
	set2.clear();
	printSet(set2, (size < 100), "set2", "empty after clear");
	std::cout << "is set2 empty: " << set2.empty() << std::endl;
	(void)size;
}

template <typename T>
void	test_set_clear(size_t size) {
	printTestCase("clear() on set of [size] size");

	T	set;
	for (size_t i = 0; i < size; i++)
		set.insert(i + 1);

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
	printTestCase("insert new & existant values");

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
	printTestCase("erase existant & non-existant values");

	T	set;
	for (size_t i = 0; i < size; i++)
		set.insert(i + 1);
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

template <typename T>
void	test_set_swap(size_t size) {
	printTestCase("set1.swap(set2)");

	T	set1, set2;
	for (size_t i = 0; i < size / 2; i++)
		set1.insert(i * 2);
	for (size_t i = size / 2; i < size; i++)
		set2.insert(i * 2);

	typename T::const_iterator it1 = set1.begin();
	typename T::const_iterator it2 = set2.begin();
	
	printSet(set1, (size < 100), "set1 BEFORE swap");
	printSet(set2, (size < 100), "set2 BEFORE swap");
	set1.swap(set2);
	printSet(set1, (size < 100), "set1 AFTER swap");
	printSet(set2, (size < 100), "set2 AFTER swap");

	std::cout << std::boolalpha;
	std::cout << "it1 points to " << *it1 << " & is equal to set2.begin(): "
		<< (it1 == set2.begin()) << std::endl;
	std::cout << "it2 points to " << *it2 << " & is equal to set1.begin(): "
		<< (it2 == set1.begin()) << std::endl;
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

template <typename T, typename K>
static void	test_set_find_helper(T &set, K k) {
	typename T::iterator	ret;

	ret = set.find(k);
	std::cout << "find (" << k << ")\n";
	if (ret != set.end())
		std::cout << "success - found " << *ret << "\n";
	else
		std::cout << "failed - find() returned end\n\n";
}

template <typename T>
void	test_set_find(size_t size) {
	printTestCase("find values within & not within set");

	T	set;
	for (size_t i = 0; i < size; i++)
		set.insert(size - 1);
	printSet(set, (size < 100), "set");
	
	test_set_find_helper(set, size / 2);
	test_set_find_helper(set, size);
	test_set_find_helper(set, size - 1);
	test_set_find_helper(set, -1);
}

template <typename T>
void	test_set_count(size_t size) {
	printTestCase("count values within & not within set");

	T	set;
	for (size_t i = 0; i < size; i++)
		set.insert(size - 1);
	printSet(set, (size < 100), "set");

	std::cout << "set.count(" << (size / 2) << ") returned " << set.count(size / 2) << std::endl;
	std::cout << "set.count(" << size << ") returned " << set.count(size) << std::endl;
	std::cout << "set.count(" << (size - 1) << ") returned " << set.count(size - 1) << std::endl;
	std::cout << "set.count(" << -1 << ") returned " << set.count(-1) << std::endl;
}

template <typename T, typename K>
static void	test_set_bounds_helper(T &set, K const& k) {
	typename T::iterator		itlow, itup;
	typename T::const_iterator	citlow, citup;

	itlow = set.lower_bound(k);
	std::cout << "lower_bound (" << k  << ") returned ";
	printEndorVal(itlow, set.end());

	itup = set.upper_bound(k);
	std::cout << "upper_bound (" << k  << ") returned ";
	printEndorVal(itup, set.end());

	citlow = set.lower_bound(k);
	std::cout << "const lower_bound (" << k  << ") returned ";
	printEndorVal(citlow, set.end());

	citup = set.upper_bound(k);
	std::cout << "const upper_bound (" << k  << ") returned ";
	printEndorVal(citup, set.end());
	std::cout << std::endl;
}

template <typename T>
void	test_set_bounds(size_t size) {
	printTestCase("upper/lower_bounds on values within, above & below set");

	T	set;
	for (size_t i = 0; i < size; i++)
		set.insert(size - i);
	printSet(set, (size < 100), "set");

	test_set_bounds_helper(set, size / 2);
	test_set_bounds_helper(set, size);
	test_set_bounds_helper(set, size - 1);
	test_set_bounds_helper(set, -1);
}

template <typename T, typename K>
static void	test_set_eqrange_helper(T &set, K const& k) {
	IMPL::pair<typename T::iterator, typename T::iterator>	ret;
	
	ret = set.equal_range(k);
	std::cout << "equal_range (" << k << "): ";
	if (std::distance(ret.first, ret.second) == 0) {
		std::cout << "no match found, return points to ";
		printEndorVal(ret.first, set.end());
	}
	else {
		std::cout << "match found between " << *(ret.first) << " and ";
		printEndorVal(ret.second, set.end());
	}
}

template <typename T>
void	test_set_eqrange(size_t size) {
	printTestCase("equal_range on values within, above & below set");

	T	set;
	for (size_t i = 0; i < size; i++)
		set.insert(size - i);
	printSet(set, (size < 100), "set");

	test_set_eqrange_helper(set, size / 2);
	test_set_eqrange_helper(set, size);
	test_set_eqrange_helper(set, size - 1);
	test_set_eqrange_helper(set, -1);
}

template <typename T>
void	test_set_iterators(size_t size) {
	printTestCase("set (const) iterator & (const) reverse it");

	T	set;
	for (size_t i = 0; i < size; i++)
		set.insert(size - i);
	printSet(set, (size < 100), "set");

	typename T::iterator	it(set.begin());
	typename T::const_iterator	cit(set.begin());
	typename T::reverse_iterator	rit(set.rbegin());
	typename T::const_reverse_iterator	crit(rit);

	std::cout << "++begin: " <<*(++it) << std::endl;
	std::cout << "begin++: " << *(it++) << std::endl;
	std::cout << "++rbegin: " << *(++rit) << std::endl;
	std::cout << "rbegin++: " << *(rit++) << std::endl;
	std::cout << "const ++begin: " << *(++cit) << std::endl;
	std::cout << "const begin++: " << *(cit++) << std::endl;
	std::cout << "const ++rbegin: " << *(++crit) << std::endl;
	std::cout << "const rbegin++: " << *(crit++) << std::endl;

	std::cout << "--begin: " << *(--it) << std::endl;
	std::cout << "begin--: " << *(it--) << std::endl;
	std::cout << "--rbegin: " << *(--rit) << std::endl;
	std::cout << "rbegin--: " << *(rit--) << std::endl;
	std::cout << "const --begin: " << *(--cit) << std::endl;
	std::cout << "const begin--: " << *(cit--) << std::endl;
	std::cout << "const --rbegin: " << *(--crit) << std::endl;
	std::cout << "const rbegin--: " << *(crit--) << std::endl;

	std::cout << "*it: " << *it << std::endl;
	std::cout << "*cit: " << *cit << std::endl;
	
	std::cout << std::boolalpha;
	std::cout << "it == cit: " << (it == cit) << std::endl;
	std::cout << "it != cit: " << (it != cit) << std::endl;
}

template <typename T>
void	test_set_relationalops(size_t size) {
	printTestCase("set == != < <= > >=");

	T	set1, set2;

	for (size_t i = 0; i < size / 2; i++)
		set1.insert(i * 2);
	for (size_t i = size / 2; i < size; i++)
		set2.insert(i * 2);
	printSet(set1, (size < 100), "set1");
	printSet(set2, (size < 100), "set2");
	
	std::cout << std::boolalpha;
	std::cout << "set1 == set2: " << (set1 == set2) << std::endl;
	std::cout << "set1 != set2: " << (set1 != set2) << std::endl;
	std::cout << "set1 < set2: " << (set1 < set2) << std::endl;
	std::cout << "set1 <= set2: " << (set1 <= set2) << std::endl;
	std::cout << "set1 > set2: " << (set1 > set2) << std::endl;
	std::cout << "set1 >= set2: " << (set1 >= set2) << std::endl;	
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

	// swap test
	benchmarkFunction_stress(test_set_swap<t_iset>, "swap");

	// key/value_comp test
	benchmarkFunction(test_set_compare<t_cset>, "key/value_comp");

	// find test
	benchmarkFunction_stress(test_set_find<t_iset>, "find");

	// count test
	benchmarkFunction_stress(test_set_count<t_iset>, "count");

	// lower/upper bound test
	benchmarkFunction_stress(test_set_bounds<t_iset>, "lower/upper bound");

	// equal_range test
	benchmarkFunction_stress(test_set_eqrange<t_iset>, "equal_range");

	// iterator test
	benchmarkFunction_stress(test_set_iterators<t_iset>, "iterators");

	// relational operators test
	benchmarkFunction_stress(test_set_relationalops<t_iset>, "relational operators");
}
