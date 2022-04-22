/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_map.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/15 22:22:07 by mjiam         #+#    #+#                 */
/*   Updated: 2022/04/19 19:58:15 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

#define T1 int
#define T2 char
#define T3 std::string
typedef IMPL::pair<const T1, T3>	t_ispair; // TODO: fix, won't compile unless changed to std::
typedef IMPL::pair<const T2, T1>	t_cipair;
typedef IMPL::map<T1, T3>	t_ismap;
typedef IMPL::map<T2, T1>	t_cimap;

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
			std::cout << "\t" << it->first << " " << it->second << std::endl;
		std::cout << std::endl;
	}
}

// void	test_map_erase() {
// 	printTest("erase");

// 	t_ismap	map;
// 	map.insert(std::pair<int,std::string>(1, "one"));
// 	map.insert(std::pair<int,std::string>(2, "two"));
// 	std::cout << "map size: " << map.size() << std::endl;
// 	try {
// 		map.erase(42);
// 	} catch (...) {
// 		std::cerr << "erase failed\n";
// 	}
// 	std::cout << "map size: " << map.size() << std::endl;
// 	map.erase(2);
// 	std::cout << "map size: " << map.size() << std::endl;
		
// 	t_cimap map2;
// 	map2.insert(t_cipair('a', 10));
// 	map2.insert(t_cipair('b', 20));
// 	map2.insert(t_cipair('c', 30));
// 	map2.insert(t_cipair('d', 40));
// 	map2.insert(t_cipair('e', 50));
// 	map2.insert(t_cipair('f', 60));
// 	// map2.print_tree();
// 	typename t_cimap::iterator it = map2.find('b');
// 	map2.erase (it);                   // erasing by iterator
// 	// map2.print_tree();
// 	map2.erase ('c');                  // erasing by key
// 	// map2.print_tree();
// 	it = map2.find ('e');
// 	map2.erase (it, map2.end());
// 	// map2.print_tree();
// }

template <typename T>
void	test_map_constructors(size_t size) {
	T	empty_map;

	printMap(empty_map, (size < 100), "empty_map");
}

template <typename T>
void	test_map_empty(size_t size) {
	printTestCase("empty()");

	T	map1;
	for (size_t i = 0; i < size; i++)
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

typedef IMPL::map<char, foo<float> > _map;
typedef _map::const_iterator const_it;
static unsigned int i = 0;

void	ft_comp(const _map &mp, const const_it &it1, const const_it &it2)
{
	bool res[2];

	std::cout << "\t-- [" << ++i << "] --" << std::endl;
	res[0] = mp.key_comp()(it1->first, it2->first);
	res[1] = mp.value_comp()(*it1, *it2);
	std::cout << "with [" << it1->first << " and " << it2->first << "]: ";
	std::cout << "key_comp: " << res[0] << " | " << "value_comp: " << res[1] << std::endl;
}

void test() {
	// std::list<T5> lst;
	// unsigned int lst_size = 10;
	// for (unsigned int i = 0; i < lst_size; ++i)
	// 	lst.push_back(T5(i + 1, (i + 1) * 3));
	// IMPL::map<T1, T4> mp(lst.begin(), lst.end());
	// printMap(mp);

	// ft_const_bound(mp, -10);
	// ft_const_bound(mp, 1);
	// ft_const_bound(mp, 5);
	// ft_const_bound(mp, 10);
	// ft_const_bound(mp, 50);

	// printMap(mp);

	// mp.lower_bound(3)->second = 404;
	// mp.upper_bound(7)->second = 842;
	// ft_bound(mp, 5);
	// ft_bound(mp, 7);

	// printMap(mp);
	_map	mp;

	mp['a'] = 2.3;
	mp['b'] = 1.4;
	mp['c'] = 0.3;
	mp['d'] = 4.2;
	printMap(mp);

	for (const_it it1 = mp.begin(); it1 != mp.end(); ++it1)
		for (const_it it2 = mp.begin(); it2 != mp.end(); ++it2)
			ft_comp(mp, it1, it2);

	printMap(mp);
}

void test_map() {
#ifndef SIMPLE
	printHeader("testing map");
#endif

	// constructor test
	// benchmarkFunction_stress(test_map_constructors<t_ismap>, "default/range/copy constructors");
	
	// empty test
	// benchmarkFunction_stress(test_map_empty<t_cimap>, "empty");
	
	// test_map_erase();
	test();
}
