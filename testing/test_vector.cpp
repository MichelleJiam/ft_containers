/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_vector.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 16:54:47 by mjiam         #+#    #+#                 */
/*   Updated: 2022/07/07 15:46:48 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

#define T1 int
#define T2 char
#define T3 std::string

typedef IMPL::vector<T1> t_ivec;
typedef IMPL::vector<T2> t_cvec;
typedef IMPL::vector<T3> t_svec;

// Prints vector capacity, size, and contents,
// and optionally a toggle for not printing contents when size is big,
// + test case + container name.
// See printTestCase for test_case argument example.
template <typename T>
void    printVector(T& base_vec, bool print_contents,
						std::string const& cntr_name,
						std::string const& test_case) {
	if (!test_case.empty())
		printTestCase(test_case);
	if (!cntr_name.empty())
		std::cout << "[ " << cntr_name << " ]\n";
	std::cout << "capacity: " << base_vec.capacity() << std::endl;
	std::cout << "size:     " << base_vec.size() << std::endl;
	std::cout << "max_size: " << base_vec.max_size() << std::endl;
	if (print_contents) {
		std::cout << "contents: [";
		for (unsigned i = 0; i < base_vec.size(); i++)
			std::cout << ' ' << base_vec[i];
		std::cout << " ]\n\n";
	}
}

template <typename T>
void	test_vec_constructors(size_t size) {
	T	fill_vec(size, 42);
	T	range_vec(fill_vec.begin(), fill_vec.end() - 2);
	T	copy_vec(range_vec);
	
	assert(fill_vec.size() == size
			&& range_vec.size() == (size) - 2
			&& copy_vec.size() == range_vec.size());
}

template <typename T>
void	test_vec_pushback(size_t size) {
	printTestCase("vector.push_back([1-size])");

	T	vector;

	for (size_t i = 1; i <= size; i++)
		vector.push_back(i);

	assert(vector.size() == size);
	printVector(vector, (size < 100), "vector");
}

template <typename T>
void	test_vec_popback(size_t size) {
	printTestCase("vector.pop_back() x size");

	T	vector(size, 42);

	for (size_t i = 1; i <= size; i++)
		vector.pop_back();

	assert(vector.size() == 0);
	printVector(vector, (size < 100), "vector");
}

// doesn't use size because empty is constant
template <typename T>
void	test_vec_empty(size_t size) {
	printTestCase("empty() on vector containing 2 elements");

	T	vector(2, 42);

	(void)size;
	std::cout << std::boolalpha
		<< "is vector empty: " << vector.empty() << std::endl;
	printVector(vector, "vector");
}

template <typename T>
void	test_vec_clear(size_t size) {
	printTestCase("clear() on vector of [size] size");

	T	vector(size, "hello");

	vector.clear();
	printVector(vector, (size < 100), "vector");
}

template <typename T>
void	test_vec_reserve(size_t size) {
	printTestCase("vector.reserve([size])");
	
	T		vector;
	size_t	oldcap = vector.capacity();

	vector.reserve(size);
	std::cout << "vector capacity was " << oldcap
		<< ", is now " << vector.capacity() << ".\n";
	printVector(vector, (size < 100), "vector");
}

template <typename T>
void	test_vec_resize(size_t size) {
	printTestCase("vector.resize(size, 42)");

	T	vector(4, 'a');

	printVector(vector, (size < 100), "vector before resize");
	vector.resize(size, 'b');
	printVector(vector, (size < 100), "vector after resize");
}

template <typename T>
void	test_vec_insert(size_t size) {
	T						vector(size, 42);
	typename T::iterator	it = vector.end();
	typename T::iterator	ret = vector.insert(it, 88);
	
	std::cout << "insert(it, 88) returns " << *ret << std::endl;
	printVector(vector, (size < 100), "vector", "insert(end, 88)");

	it = vector.end();
	ret = vector.insert(it - 1, 13);
	std::cout << "insert(it - 1, 13) returns " << *ret << std::endl;
	printVector(vector, (size < 100), "vector", "insert(end - 1, 13)");

	it = vector.begin();
	vector.insert(it + 2, 4, 7);
	printVector(vector, (size < 100), "vector", "insert(begin + 2, 4, 7)");

	T	vector2;
	it = vector2.begin();
	ret = vector2.insert(it, 100);
	std::cout << "insert(it, 100) returns " << *ret << std::endl;
	printVector(vector2, (size < 100), "empty vector2", "insert(begin, 100)");

	it = vector.begin();
	vector2.insert(vector2.begin(), it, it + 2);
	printVector(vector2, (size < 100), "vector2", "insert(begin, [42], [42])");
}

template <typename T>
void	test_vec_erase(size_t size) {
	T						vector(size, 42);
	typename T::iterator	it = vector.end();

	vector.erase(it - 2);
	printVector(vector, (size < 100), "vector", "erase(end - 2)");

	it = vector.end();
	vector.erase(it - 3, it - 1);
	printVector(vector, (size < 100), "vector", "erase(end - 3, end - 1)");

	it = vector.begin();
	vector.erase(it + 2, it + 4);
	printVector(vector, (size < 100), "vector", "erase(begin + 1, begin + 3)");
}

template <typename T>
void	test_vec_assign(size_t size) {
	T	vector(size, 42);
	T	vec1, vec2, vec3;

	vec1.assign(7, vector[0]); // 7 ints
	printVector(vec1, (size < 100), "vector 1", "assign(7, [42])");

	typename T::iterator it = vec1.begin();
	vec2.assign(it + 1, it + 6); // 5 central values from vec1
	printVector(vec2, (size < 100), "vector 2", "assign(vec1.begin + 1, vec1.begin + 6)");
	
	vec3.assign(vector.begin(), vector.end()); // [size] elements
	printVector(vec3, (size < 100), "vector 3", "assign(vector.begin, vector.end)");

	assert(vec1.size() == 7);
	assert(vec2.size() == 5);
	assert(vec3.size() == size);
}

template <typename T>
void	test_vec_swap(size_t size) {
	printTestCase("vec1.swap(vec2)");

	T	vec1(size, 13);
	T	vec2(size, 42);

	printVector(vec1, (size < 100), "vector 1 BEFORE swap");
	printVector(vec2, (size < 100), "vector 2 BEFORE swap");

	vec1.swap(vec2);
	assert(vec1.size() == vec2.size());
	printVector(vec1, (size < 100), "vector 1 AFTER swap");
	printVector(vec2, (size < 100), "vector 2 AFTER swap");
}

template <typename T>
void	test_vec_elementAccess(size_t size) {
	printTestCase("vector.op[] - at - front - back");
	
	T	vector;

	for (size_t i = 0; i < size; i++)
		vector.push_back(i);

	std::cout << "vector[3]: " << vector[3] << std::endl;
	std::cout << "vector.at(1): " << vector.at(1) << std::endl;
	std::cout << "vector.front(): " << vector.front() << std::endl;
	std::cout << "vector.back(): " << vector.back() << std::endl;
	std::cout << std::endl;
	printVector(vector, (size < 100), "vector");
}

template <typename T>
void	test_vec_relationalOps(size_t size) {
	printTestCase("vector == != < <= > >=");

	T	vec1(size, 42);
	T	vec2(size / 2, 13);

	printVector(vec1, (size < 100), "vector 1");
	printVector(vec2, (size < 100), "vector 2");
	std::cout << std::boolalpha;
	std::cout << "vec1 == vec2: " << (vec1 == vec2) << std::endl;
	std::cout << "vec1 != vec2: " << (vec1 != vec2) << std::endl;
	std::cout << "vec1 < vec2: " << (vec1 < vec2) << std::endl;
	std::cout << "vec1 <= vec2: " << (vec1 <= vec2) << std::endl;
	std::cout << "vec1 > vec2: " << (vec1 > vec2) << std::endl;
	std::cout << "vec1 >= vec2: " << (vec1 >= vec2) << std::endl;
}

template <typename T>
void	test_vec_iterators(size_t size) {
	printTestCase("vector.begin - end - rbegin - rend");

	T	vector;

	for (size_t i = 0; i < size; i++)
		vector.push_back(i);

	typename T::iterator it = vector.begin();
	it[0] = 42;
	std::cout << "begin: " << *it << std::endl;
	std::cout << "begin + 1: " << *(it += 1) << std::endl;
	it = 3 + it;
	it = it - 2;
	std::cout << "it + 3 - 2: " << *it << std::endl;
	std::cout << "end - 1: " << *(vector.end() - 1) << std::endl;
	std::cout << "rbegin: " << *vector.rbegin() << std::endl;
	std::cout << "rbegin + 1: " << *(vector.rbegin() + 1) << std::endl;
	std::cout << "rend - 1: " << *(vector.rend() - 1) << std::endl;

	it = vector.begin();
	typename T::const_iterator ite = vector.end();

	std::cout << "len: " << (ite - it) << std::endl;
	std::cout << std::boolalpha;
	std::cout << "it (begin) == const_it (end): " << (it == ite) << std::endl;
	std::cout << "it (begin) != const_it (end): " << (it != ite) << std::endl;
	std::cout << "it (begin) <= const_it (end): " << (it <= ite) << std::endl;
	std::cout << "it (begin) >= const_it (end): " << (it >= ite) << std::endl;
	std::cout << "it (begin) < const_it (end): " << (it < ite) << std::endl;
	std::cout << "it (begin) > const_it (end): " << (it > ite) << std::endl;

	typename T::reverse_iterator rit = vector.rbegin();
	typename T::const_reverse_iterator rite = vector.rend();

	std::cout << "rit (rbegin) == const_rit (rend): " << (rit == rite) << std::endl;
	std::cout << "rit (rbegin) != const_rit (rend): " << (rit != rite) << std::endl;
	std::cout << "rit (rbegin) <= const_rit (rend): " << (rit <= rite) << std::endl;
	std::cout << "rit (rbegin) >= const_rit (rend): " << (rit >= rite) << std::endl;
	std::cout << "rit (rbegin) < const_rit (rend): " << (rit < rite) << std::endl;
	std::cout << "rit (rbegin) > const_rit (rend): " << (rit > rite) << std::endl;
	
	if (size < 100) {
		std::cout << "iterating from begin to end: ";
		for (it = vector.begin(); it != vector.end(); ++it)
			std::cout << *it << " ";
		std::cout << "\niterating backwards from rbegin to rend: ";
		for (typename T::reverse_iterator rit = vector.rbegin(); rit != vector.rend(); ++rit)
			std::cout << *rit << " ";
		std::cout << std::endl << std::endl;
		printVector(vector, (size < 100), "vector");
	}
}
#include <memory>
void test_vector() {
#ifndef SIMPLE
	printHeader("vector");
#else
	std::cout << "VECTOR\n";
#endif

	// constructor test
	benchmarkFunction_stress(test_vec_constructors<t_ivec>, "fill/range/copy constructors");
	
	// push_back test
	benchmarkFunction_stress(test_vec_pushback<t_ivec>, "push_back");

	// pop_back test
	benchmarkFunction_stress(test_vec_popback<t_ivec>, "pop_back");

	// empty test
	benchmarkFunction(test_vec_empty<t_ivec>, "empty");

	// clear test
	benchmarkFunction_stress(test_vec_clear<t_svec>, "clear");
	
	// reserve test
	benchmarkFunction_stress(test_vec_reserve<t_cvec>, "reserve");

	// resize test
	benchmarkFunction_stress(test_vec_resize<t_cvec>, "resize");
	
	// insert test
	benchmarkFunction_stress(test_vec_insert<t_ivec>, "insert");

	// erase test
	benchmarkFunction_stress(test_vec_erase<t_ivec>, "erase");

	// assign test
	benchmarkFunction_stress(test_vec_assign<t_ivec>, "assign");

	// swap test
	benchmarkFunction_stress(test_vec_swap<t_ivec>, "swap");

	// element access functions
	benchmarkFunction_stress(test_vec_elementAccess<t_ivec>, "element access");

	// relational operators
	benchmarkFunction_stress(test_vec_relationalOps<t_ivec>, "relational operators");

	// iterators
	benchmarkFunction_stress(test_vec_iterators<t_ivec>, "iterators");
}