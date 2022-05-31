/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_map.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/15 22:22:07 by mjiam         #+#    #+#                 */
/*   Updated: 2022/05/31 21:46:34 by mjiam         ########   odam.nl         */
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
	printTestCase("empty() on filled map, default constructed map, after assignment, and after clear");

	T	map1;
	for (size_t i = 0; i < 10; i++)
		map1['a' + i] = i;

	std::cout << std::boolalpha;
	std::cout << "is map1 empty: " << map1.empty() << std::endl;
	printMap(map1, (size < 100), "map1");

	T map2;
	std::cout << "is map2 empty: " << map2.empty() << std::endl;
	printMap(map2, (size < 100), "map2");

	map2 = map1;
	std::cout << "is map2 empty: " << map2.empty() << std::endl;
	printMap(map2, (size < 100), "map2");
	
	map2.clear();
	std::cout << "is map2 empty: " << map2.empty() << std::endl;
	printMap(map2, (size < 100), "map2");
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
class foo {
	public:
		typedef T	value_type;

		foo(void) : value(), _verbose(false) { };
		foo(value_type src, const bool verbose = false) : value(src), _verbose(verbose) { };
		foo(foo const &src, const bool verbose = false) : value(src.value), _verbose(verbose) { };
		~foo(void) { if (this->_verbose) std::cout << "~foo::foo()" << std::endl; };
		void m(void) { std::cout << "foo::m called [" << this->value << "]" << std::endl; };
		void m(void) const { std::cout << "foo::m const called [" << this->value << "]" << std::endl; };
		foo &operator=(value_type src) { this->value = src; return *this; };
		foo &operator=(foo const &src) {
			if (this->_verbose || src._verbose)
				std::cout << "foo::operator=(foo) CALLED" << std::endl;
			this->value = src.value;
			return *this;
		};
		value_type	getValue(void) const { return this->value; };
		void		switchVerbose(void) { this->_verbose = !(this->_verbose); };

		operator value_type(void) const {
			return value_type(this->value);
		}
	private:
		value_type	value;
		bool		_verbose;
};

// #include <list>
// #define T4 foo<int>
// #define _pair IMPL::pair
// typedef IMPL::map<T1, T4>::value_type T5;
// typedef IMPL::map<T1, T4>::iterator ft_iterator;
// typedef IMPL::map<T1, T4>::const_iterator ft_const_iterator;

// static int iter = 0;

// template <typename T>
// std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
// {
// 	o << "key: " << iterator->first << " | value: " << iterator->second;
// 	if (nl)
// 		o << std::endl;
// 	return ("");
// }

// template <typename MAP>
// void	ft_bound(MAP &mp, const T1 &param)
// {
// 	ft_iterator ite = mp.end(), it[2];
// 	_pair<ft_iterator, ft_iterator> ft_range;

// 	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
// 	std::cout << "with key [" << param << "]:" << std::endl;
// 	it[0] = mp.lower_bound(param); it[1] = mp.upper_bound(param);
// 	ft_range = mp.equal_range(param);
// 	std::cout << "lower_bound: " << (it[0] == ite ? "end()" : printPair(it[0], false)) << std::endl;
// 	std::cout << "upper_bound: " << (it[1] == ite ? "end()" : printPair(it[1], false)) << std::endl;
// 	std::cout << "equal_range: " << (ft_range.first == it[0] && ft_range.second == it[1]) << std::endl;
// }

// template <typename MAP>
// void	ft_const_bound(const MAP &mp, const T1 &param)
// {
// 	ft_const_iterator ite = mp.end(), it[2];
// 	_pair<ft_const_iterator, ft_const_iterator> ft_range;

// 	std::cout << "\t-- [" << iter++ << "] (const) --" << std::endl;
// 	std::cout << "with key [" << param << "]:" << std::endl;
// 	it[0] = mp.lower_bound(param); it[1] = mp.upper_bound(param);
// 	ft_range = mp.equal_range(param);
// 	std::cout << "lower_bound: " << (it[0] == ite ? "end()" : printPair(it[0], false)) << std::endl;
// 	std::cout << "upper_bound: " << (it[1] == ite ? "end()" : printPair(it[1], false)) << std::endl;
// 	std::cout << "equal_range: " << (ft_range.first == it[0] && ft_range.second == it[1]) << std::endl;
// }

void test_map() {
#ifndef SIMPLE
	printHeader("map");
#else
	std::cout << "MAP\n";
#endif

	// // constructor test
	// benchmarkFunction_stress(test_map_constructors<t_iimap>, "default/range/copy constructors");
	
	// // empty test
	// benchmarkFunction(test_map_empty<t_cimap>, "empty");

	// // key/value_comp test
	// benchmarkFunction(test_map_compare<t_cimap>, "key/value_comp");

	// // operator[] test
	// benchmarkFunction_stress(test_map_operatorat<t_iimap>, "operator[]");

	// // insert test
	// benchmarkFunction_stress(test_map_insert<t_iimap>, "insert");
	
	// erase test
	benchmarkFunction_stress(test_map_erase<t_iimap>, "erase");
	// test();
}
