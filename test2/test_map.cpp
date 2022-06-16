/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_map.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/15 22:22:07 by mjiam         #+#    #+#                 */
/*   Updated: 2022/06/16 21:28:47 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

#define T1 int
#define T2 char
#define T3 std::string

typedef IMPL::map<T1, T3>::value_type	t_ispair;
typedef IMPL::map<T2, T1>::value_type	t_cipair;
typedef IMPL::map<T1, T1>::value_type	t_iipair;
typedef IMPL::map<T1, T3>	t_ismap;
typedef IMPL::map<T2, T1>	t_cimap;
typedef IMPL::map<T1, T1>	t_iimap;

template <typename T>
std::string	printPair(T const& iterator, bool print_newline = true) {
	std::cout << "[" << iterator->first << ", " << iterator->second << "]";
	if (print_newline)
		std::cout << std::endl;
	return ("");
}

template <typename Iterator>
void	printEndorVal(Iterator it, Iterator end, bool print_newline = true) {
	if (it == end)
		std::cout << "end";
	else
		std::cout << printPair(it, false);
	if (print_newline)
		std::cout << "\n";
}

template <typename T>
void    printMap(T& base_map, bool print_contents = true,
					std::string const& cntr_name = std::string(),
					std::string const& test_case = std::string()) {
	if (!test_case.empty())
		printTestCase(test_case);
	if (!cntr_name.empty())
		std::cout << "[ " << cntr_name << " ]\n";
	std::cout << "size: " << base_map.size() << std::endl;
	std::cout << "max_size: " << base_map.max_size() << std::endl;
	if (print_contents) {
		std::cout << "contents:\n";
		for (typename T::iterator it = base_map.begin(); it != base_map.end(); ++it)
			std::cout << "\t" << printPair(it);
		std::cout << std::endl;
	}
}

template <typename T>
void	test_map_constructors(size_t size) {
	T	empty_map;

	printMap(empty_map, (size < 100), "empty_map");

	for (size_t i = 0; i < size; i++)
		empty_map[i] = size - i;

	T	copy_map(empty_map);
	printMap(copy_map, (size < 100), "copy_map");
	
	typename T::iterator it = empty_map.begin(), ite = empty_map.end();

	T	range_map(it, --(--ite));
	printMap(range_map, (size < 100), "range_map");

	T	assign_map;
	assign_map = range_map;
	printMap(assign_map, (size < 100), "assign_map");

	assert(empty_map.size() == size
			&& copy_map.size() == empty_map.size()
			&& range_map.size() == empty_map.size() - 2
			&& assign_map.size() == range_map.size());
}

// doesn't use `size` because complexity is constant
template <typename T>
void	test_map_empty(size_t size) {
	T	map1;
	for (size_t i = 0; i < 10; i++)
		map1['a' + i] = i;

	std::cout << std::boolalpha;
	std::cout << "is map1 empty: " << map1.empty() << std::endl;
	printMap(map1, (size < 100), "map1", "empty on filled map");

	T map2;
	std::cout << "is map2 empty: " << map2.empty() << std::endl;
	printMap(map2, (size < 100), "map2", "empty on default constructed map");

	map2 = map1;
	std::cout << "is map2 empty: " << map2.empty() << std::endl;
	printMap(map2, (size < 100), "map2", "empty on copy assigned map");
	
	map2.clear();
	std::cout << "is map2 empty: " << map2.empty() << std::endl;
	printMap(map2, (size < 100), "map2", "empty after clear");
	(void)size;
}

// doesn't use `size` because complexity is constant
template <typename T>
void	test_map_compare(size_t size) {
	printTestCase("key_comp & value_comp on identical keys, identical values, and larger key");

	T	map1, map2;

	map1['a'] = 13;
	map1['b'] = 42;
	map1['e'] = 0;
	
	map2['a'] = 31;
	map2['c'] = 42;
	map2['d'] = 100;

	typename T::iterator it1 = map1.begin(), it2 = map2.begin();
	std::cout << std::boolalpha;
	while (it1 != map1.end() && it2 != map2.end()) {
		std::cout << printPair(it1, false)
			<< " vs "<< printPair(it2, false) << "\n"
			<< "key_comp: " << map1.key_comp()(it1->first, it2->first)
			<< " | value_comp: " << map1.value_comp()(*it1, *it2)
			<< "\n\n";
		++it1, ++it2;
	}
	(void)size;
}

template <typename T>
void	test_map_operatorat(size_t size) {
	printTestCase("Calling operator[] on nonexistant key");
	
	T map;

	for (size_t i = 0; i < size; i++)
		map[i] = size - i;

	map[size];

	printMap(map, (size < 100), "map");
	assert(map.size() == size + 1);
}

template <typename T, typename P>
static void	test_map_insert_helper(T &map, P param) {
	IMPL::pair<typename T::iterator, bool> ret;

	ret = map.insert(param);
	std::cout << "insert " << printPair(&param);
	if (ret.second == true)
		std::cout << "success - " << printPair(ret.first, false) << " inserted\n\n";
	else
		std::cout << "failed - " << printPair(ret.first, false) << " already in map\n\n";
}

template <typename T>
void	test_map_insert(size_t size) {
	printTestCase("insert existing & non-existing keys");

	T	map;
	for (size_t i = 0; i < size; i++)
		map[i] = size - i;

	// insert single
	test_map_insert_helper(map, t_iipair(size, size + 5));
	test_map_insert_helper(map, t_iipair(1, 42));
	
	// insert with hint
	typename T::iterator it = map.insert(map.begin(), t_iipair(size + 1, 42));

	std::cout << "insert [" << size + 1 << ", 42]\n";
	std::cout << "return: " << printPair(it, false) << std::endl << std::endl;

	// insert range
	std::list<t_iipair> list;
	typename std::list<t_iipair>::iterator lit;
	for (size_t i = size + 2; i < size + 12; i++)
		list.push_back(t_iipair(i, i + 1));

	std::cout << "list contents:\n";
	for (lit = list.begin(); lit != list.end(); ++lit)
		std::cout << "\t" << printPair(lit);
	std::cout << std::endl;

	map.insert(list.begin(), list.end());
	printMap(map, (size < 100), "map");
}

template <typename T>
void	test_map_erase(size_t size) {
	T	map;
	for (size_t i = 0; i < size; i++)
		map[i] = size - i;

	printMap(map, (size < 100), "map before erase");

	std::cout << "erase(" << (size / 2) << ")\n";
	std::cout << "map size before: " << map.size() << std::endl;
	size_t ret = map.erase(size / 2);
	std::cout << "elements erased: " << ret << std::endl;
	std::cout << "map size after: " << map.size() << std::endl << std::endl;

	std::cout << "erase(begin)\n";
	std::cout << "map size before: " << map.size() << std::endl;
	map.erase(map.begin());
	std::cout << "map size after: " << map.size() << std::endl << std::endl;

	std::cout << "erase([non-existant key])\n";
	std::cout << "map size before: " << map.size() << std::endl;
	map.erase(size + 1);
	std::cout << "map size after: " << map.size() << std::endl << std::endl;

	std::cout << "erase(begin, end)\n";
	std::cout << "map size before: " << map.size() << std::endl;
	map.erase(map.begin(), map.end());
	std::cout << "map size after: " << map.size() << std::endl << std::endl;

	printMap(map, (size < 100), "map after erase");
}

template <typename T>
void	test_map_swap(size_t size) {
	printTestCase("map1.swap(map2)");
	
	T	map1, map2;
	for (size_t i = 0; i < size / 2; i++)
		map1[i] = i * 2;
	for (size_t i = size / 2; i < size; i++)
		map2[i] = i * 2;

	typename T::const_iterator it1 = map1.begin();
	typename T::const_iterator it2 = map2.begin();
	
	printMap(map1, (size < 100), "map1 BEFORE swap");
	printMap(map2, (size < 100), "map2 BEFORE swap");
	map1.swap(map2);
	printMap(map1, (size < 100), "map1 AFTER swap");
	printMap(map2, (size < 100), "map2 AFTER swap");

	std::cout << std::boolalpha;
	std::cout << "it1 points to " << printPair(it1, false)
		<< " & is equal to map2.begin(): " << (it1 == map2.begin()) << std::endl;
	std::cout << "it2 points to " << printPair(it2, false)
		<< " & is equal to map1.begin(): " << (it2 == map1.begin()) << std::endl;
}

template <typename T, typename K>
static void	test_map_find_helper(T &map, K k) {
	typename T::iterator	ret;

	ret = map.find(k);
	std::cout << "find (" << k << ")\n";
	if (ret != map.end())
		std::cout << "success - found " << printPair(ret) << "\n";
	else
		std::cout << "failed - find() returned end\n\n";
}

template <typename T>
void	test_map_find(size_t size) {
	T	map;
	for (size_t i = 0; i < size; i++)
		map[i] = size - i;
	printMap(map, (size < 100), "map");
	
	test_map_find_helper(map, size / 2);
	test_map_find_helper(map, size);
	test_map_find_helper(map, size - 1);
	test_map_find_helper(map, -1);
}

template <typename T>
void	test_map_count(size_t size) {
	T	map;
	for (size_t i = 0; i < size; i++)
		map[i] = size - i;
	printMap(map, (size < 100), "map");

	std::cout << "map.count(" << (size / 2) << ") returned " << map.count(size / 2) << std::endl;
	std::cout << "map.count(" << size << ") returned " << map.count(size) << std::endl;
	std::cout << "map.count(" << (size - 1) << ") returned " << map.count(size - 1) << std::endl;
	std::cout << "map.count(" << -1 << ") returned " << map.count(-1) << std::endl;
}

template <typename T, typename K>
static void	test_map_bounds_helper(T &map, K const& k) {
	typename T::iterator	itlow, itup;
	typename T::const_iterator	citlow, citup;

	itlow = map.lower_bound(k);
	std::cout << "lower_bound (" << k  <<  ") returned ";
	printEndorVal(itlow, map.end());

	itup = map.upper_bound(k);
	std::cout << "upper_bound (" << k  <<  ") returned ";
	printEndorVal(itup, map.end());

	citlow = map.lower_bound(k);
	std::cout << "const lower_bound (" << k  <<  ") returned ";
	printEndorVal<typename T::const_iterator>(citlow, map.end());

	citup = map.upper_bound(k);
	std::cout << "const upper_bound (" << k  << ") returned ";
	printEndorVal<typename T::const_iterator>(citup, map.end());
	std::cout << std::endl;
}

template <typename T>
void	test_map_bounds(size_t size) {
	T	map;
	for (size_t i = 0; i < size; i++)
		map[i] = size - i;
	printMap(map, (size < 100), "map");

	test_map_bounds_helper(map, size / 2);
	test_map_bounds_helper(map, size);
	test_map_bounds_helper(map, size - 1);
	test_map_bounds_helper(map, -1);
}

template <typename T, typename K>
static void	test_map_eqrange_helper(T &map, K const& k) {
	IMPL::pair<typename T::iterator, typename T::iterator>	ret;
	
	ret = map.equal_range(k);
	std::cout << "equal_range (" << k << "): ";
	if (std::distance(ret.first, ret.second) == 0) {
		std::cout << "no match found, return points to ";
		printEndorVal(ret.first, map.end());
	}
	else {
		std::cout << "match found between " << printPair(ret.first, false)
			<< " and ";
			printEndorVal(ret.second, map.end());
	}
}

template <typename T>
void	test_map_eqrange(size_t size) {
	T	map;
	for (size_t i = 0; i < size; i++)
		map[i] = size - i;
	printMap(map, (size < 100), "map");

	test_map_eqrange_helper(map, size / 2);
	test_map_eqrange_helper(map, size);
	test_map_eqrange_helper(map, size - 1);
	test_map_eqrange_helper(map, -1);
}

template <typename T>
void	test_map_iterators(size_t size) {
	printTestCase("map (const) iterator & (const) reverse it");

	T	map;
	for (size_t i = 0; i < size; i++)
		map[i] = size - i;
	printMap(map, (size < 100), "map");

	typename T::iterator	it(map.begin());
	typename T::const_iterator	cit(map.begin());
	typename T::reverse_iterator	rit(map.rbegin());
	typename T::const_reverse_iterator	crit(rit);

	std::cout << "++begin: " << printPair(++it);
	std::cout << "begin++: " << printPair(it++);
	std::cout << "++rbegin: " << printPair(++rit);
	std::cout << "rbegin++: " << printPair(rit++);
	std::cout << "const ++begin: " << printPair(++cit);
	std::cout << "const begin++: " << printPair(cit++);
	std::cout << "const ++rbegin: " << printPair(++crit);
	std::cout << "const rbegin++: " << printPair(crit++);

	std::cout << "--begin: " << printPair(--it);
	std::cout << "begin--: " << printPair(it--);
	std::cout << "--rbegin: " << printPair(--rit);
	std::cout << "rbegin--: " << printPair(rit--);
	std::cout << "const --begin: " << printPair(--cit);
	std::cout << "const begin--: " << printPair(cit--);
	std::cout << "const --rbegin: " << printPair(--crit);
	std::cout << "const rbegin--: " << printPair(crit--);

	std::cout << "*it.first: " << (*it).first << std::endl;
	std::cout << "*cit.first: " << (*cit).first << std::endl;
	
	std::cout << std::boolalpha;
	std::cout << "it == cit: " << (it == cit) << std::endl;
	std::cout << "it != cit: " << (it != cit) << std::endl;
}

template <typename T>
void	test_map_relationalops(size_t size) {
	printTestCase("map == != < <= > >=");

	T	map1, map2;

	for (size_t i = 0; i < size / 2; i++)
		map1[i] = i * 2;
	for (size_t i = size / 2; i < size; i++)
		map2[i] = i * 2;
	printMap(map1, (size < 100), "map1");
	printMap(map2, (size < 100), "map2");
	
	std::cout << std::boolalpha;
	std::cout << "map1 == map2: " << (map1 == map2) << std::endl;
	std::cout << "map1 != map2: " << (map1 != map2) << std::endl;
	std::cout << "map1 < map2: " << (map1 < map2) << std::endl;
	std::cout << "map1 <= map2: " << (map1 <= map2) << std::endl;
	std::cout << "map1 > map2: " << (map1 > map2) << std::endl;
	std::cout << "map1 >= map2: " << (map1 >= map2) << std::endl;	
}

void test_map() {
#ifndef SIMPLE
	printHeader("map");
#else
	std::cout << "MAP\n";
#endif

	// constructor test
	benchmarkFunction_stress(test_map_constructors<t_iimap>, "default/range/copy constructors");
	
	// empty test
	benchmarkFunction(test_map_empty<t_cimap>, "empty");

	// key/value_comp test
	benchmarkFunction(test_map_compare<t_cimap>, "key/value_comp");

	// operator[] test
	benchmarkFunction_stress(test_map_operatorat<t_iimap>, "operator[]");

	// insert test
	benchmarkFunction_stress(test_map_insert<t_iimap>, "insert");
	
	// erase test
	benchmarkFunction_stress(test_map_erase<t_iimap>, "erase");

	// swap test
	benchmarkFunction_stress(test_map_swap<t_iimap>, "swap");

	// find test
	benchmarkFunction_stress(test_map_find<t_iimap>, "find");

	// count test
	benchmarkFunction_stress(test_map_count<t_iimap>, "count");

	// lower/upper bound test
	benchmarkFunction_stress(test_map_bounds<t_iimap>, "lower/upper bound");

	// equal_range test
	benchmarkFunction_stress(test_map_eqrange<t_iimap>, "equal_range");

	// iterator test
	benchmarkFunction_stress(test_map_iterators<t_iimap>, "iterators");

	// relational operators test
	benchmarkFunction_stress(test_map_relationalops<t_iimap>, "relational operators");
}
