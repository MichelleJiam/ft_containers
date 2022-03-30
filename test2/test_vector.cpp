/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_vector.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 16:54:47 by mjiam         #+#    #+#                 */
/*   Updated: 2022/03/30 18:09:24 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"
#include "../containers/vector.hpp"

typedef IMPL::vector<int> t_ivec;

// Prints vector capacity, size, and contents,
// and optionally test case and container name.
// See printTestCase for test_case argument example.
template <typename T>
void    printVector(T& base_vec, std::string const cntr_name,
					std::string const test_case) {
	if (!test_case.empty())
		printTestCase(test_case);
	if (!cntr_name.empty())
		std::cout << "[ " << cntr_name << " ]\n";
	std::cout << "capacity: " << base_vec.capacity() << std::endl;
	std::cout << "size:     " << base_vec.size() << std::endl;
	std::cout << "contents: [";
	for (unsigned i = 0; i < base_vec.size(); i++)
		std::cout << ' ' << base_vec[i];
	std::cout << " ]\n\n";
}

template <typename T>
void	test_vec_elementAccess(T& vector) {
	std::cout << "vec[3]: " << vector[3] << std::endl;
	std::cout << "vec.at(1): " << vector.at(1) << std::endl;
	std::cout << "vec.front(): " << vector.front() << std::endl;
	std::cout << "vec.back(): " << vector.back() << std::endl;
	printVector(vector, "vector");
}

template <typename T>
void	test_vec_relationalOps(T& vector) {
	T	vec1(3, 42);
	T	vec2(2, 13);

	printVector(vec1, "vector 1");
	printVector(vec2, "vector 2");
	std::cout << std::boolalpha;
	std::cout << "vec1 == vec2: " << (vec1 == vec2) << std::endl;
	std::cout << "vec1 != vec2: " << (vec1 != vec2) << std::endl;
	std::cout << "vec1 < vec2: " << (vec1 < vec2) << std::endl;
	std::cout << "vec1 <= vec2: " << (vec1 <= vec2) << std::endl;
	std::cout << "vec1 > vec2: " << (vec1 > vec2) << std::endl;
	std::cout << "vec1 >= vec2: " << (vec1 >= vec2) << std::endl;
	std::cout << "vector != vec1: " << (vector != vec1) << std::endl;
}

template <typename T>
void	test_vec_iterators(T& vector) {
	std::cout << "begin: " << *vector.begin() << std::endl;
	std::cout << "begin + 1: " << *(vector.begin() + 1) << std::endl;
	std::cout << "end - 1: " << *(vector.end() - 1) << std::endl;
	std::cout << "rbegin: " << *vector.rbegin() << std::endl;
	std::cout << "rbegin + 1: " << *(vector.rbegin() + 1) << std::endl;
	std::cout << "rend - 1: " << *(vector.rend() - 1) << std::endl;
	std::cout << "iterating from begin to end: ";
	for (t_ivec::iterator it = vector.begin(); it != vector.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
	std::cout << "iterating backwards from rbegin to rend: ";
	for (t_ivec::reverse_iterator rit = vector.rbegin(); rit != vector.rend(); ++rit)
		std::cout << *rit << " ";
	std::cout << std::endl;
	printVector(vector, "vector");
}

template <typename T>
void	test_vec_swap(T& vector) {
	T	vector_b(vector.size(), 13);

	printVector(vector, "vector 1 BEFORE swap");
	printVector(vector_b, "vector 2 BEFORE swap");
	vector.swap(vector_b);
	printVector(vector_b, "vector 2 AFTER swap");
	assert(vector.size() == vector_b.size());
	printVector(vector, "vector 1 AFTER swap");
}

template <typename T>
void	test_vec_constructors(unsigned long times) {
	T	fill_vec(times, 42);
	T	range_vec(fill_vec.begin(), fill_vec.end() - 2);
	T	copy_vec(range_vec);
	
	assert(fill_vec.size() == times
			&& range_vec.size() == (times) - 2
			&& copy_vec.size() == range_vec.size());
}

template <typename T>
void	test_vec_pushback(unsigned long times) {
	printTestCase("push_back([1-10])");

	T	vector;

	for (size_t i = 1; i <= times; i++)
		vector.push_back(i);

	assert(vector.size() == times);

	if (times < INT_MAX / 100)	// only print vector contents when not stress testing
		printVector(vector, "vector");
}

template <typename T>
void	test_vec_popback(unsigned long times) {
	printTestCase("pop_back() x times");

	T	vector(times, 42);

	for (size_t i = 1; i <= times; i++)
		vector.pop_back();

	assert(vector.size() == 0);

	if (times < INT_MAX / 100)
		printVector(vector, "vector");
}

template <typename T>
void	test_vec_empty(unsigned long times) {
	printTestCase("empty() on vector containing 2 elements");

	T	vector(2, 42);

	(void)times;
	std::cout << std::boolalpha
		<< "is vector empty: " << vector.empty() << std::endl;
	printVector(vector, "vector");
}

template <typename T>
void	test_vec_clear(unsigned long times) {
	printTestCase("clear() on vector of [times] size");

	T	vector(times, 42);
	vector.clear();

	if (times < INT_MAX / 100)
		printVector(vector, "vector");
}

template <typename T>
void	test_vec_reserve(unsigned long times) {
	printTestCase("reserve([times])");
	
	T		vector;
	size_t	oldcap = vector.capacity();

	vector.reserve(times);
	std::cout << "\nvector capacity was " << oldcap
		<< ", is now " << vector.capacity() << ".\n";
	
	if (times < INT_MAX / 100)
		printVector(vector, "vector");
}

template <typename T>
void	test_vec_resize(unsigned long times) {
	printTestCase("resize(times, 42)");

	T	vector(4, 20);

	vector.resize(times, 42);

	if (times < INT_MAX / 100)
		printVector(vector, "vector");
}

template <typename T>
void	test_vec_insert(unsigned long times) {
	T						vector(times, 42);
	typename T::iterator	it = vector.end();
	
	vector.insert(it, 88);
	if (times < INT_MAX / 100)
		printVector(vector, "vector", "insert(end, 88)");

	it = vector.end();
	vector.insert(it - 1, 13);
	if (times < INT_MAX / 100)
		printVector(vector, "vector", "insert(end - 1, 13)");

	it = vector.begin();
	vector.insert(it + 2, 4, 7);
	if (times < INT_MAX / 100)
		printVector(vector, "vector", "insert(begin + 2, 4, 7)");

	T	anothervector(3, 21);
	it = vector.begin();
	anothervector.insert(anothervector.begin() + 1,
							it, it + 2);
	if (times < INT_MAX / 100)
		printVector(anothervector, "anothervector", "insert(begin + 1, [42], [42])");

	it = anothervector.begin();
	anothervector.insert(it, 100);
	if (times < INT_MAX / 100)
		printVector(anothervector, "anothervector", "insert(begin, 100)");
}

template <typename T>
void	test_vec_erase(unsigned long times) {
	T						vector(times, 42);
	typename T::iterator	it = vector.end();

	vector.erase(it - 2);
	if (times < INT_MAX / 100)
		printVector(vector, "vector", "erase(end - 2)");

	it = vector.end();
	vector.erase(it - 3, it - 1);
	if (times < INT_MAX / 100)
		printVector(vector, "vector", "erase(end - 3, end - 1)");

	it = vector.begin();
	vector.erase(it + 2, it + 4);
	if (times < INT_MAX / 100)
		printVector(vector, "vector", "erase(begin + 1, begin + 3)");
}

template <typename T>
void	test_vec_assign(unsigned long times) {
	T	vector(times, 42);
	T	vec1, vec2, vec3;

	vec1.assign(7, vector[0]); // 7 ints
	printVector(vec1, "vector 1", "assign(7, [42])");

	typename T::iterator it = vec1.begin();
	vec2.assign(it + 1, it + 6); // 5 central values from vec1
	printVector(vec2, "vector 2", "assign(vec1.begin + 1, vec1.begin + 6)");
	
	vec3.assign(vector.begin(), vector.end()); // [times] elements
	if (times < INT_MAX / 100)
		printVector(vec3, "vector 3", "assign(vector.begin, vector.end)");

	assert(vec1.size() == 7);
	assert(vec2.size() == 5);
	assert(vec3.size() == times);
}

void test_vector() {
#ifndef SIMPLE
	printHeader("testing vector");
#endif

	// constructor test
	benchmarkFunction_stress(test_vec_constructors<t_ivec>, "fill/range/copy constructors");
	
	// push_back test
	benchmarkFunction_stress(test_vec_pushback<t_ivec>, "push_back");

	// pop_back test
	benchmarkFunction_stress(test_vec_popback<t_ivec>, "pop_back");

	// empty test
	benchmarkFunction_stress(test_vec_empty<t_ivec>, "empty");

	// clear test
	benchmarkFunction_stress(test_vec_clear<t_ivec>, "clear");
	
	// reserve test
	benchmarkFunction_stress(test_vec_reserve<t_ivec>, "reserve");

	// resize test
	benchmarkFunction_stress(test_vec_resize<t_ivec>, "resize");
	
	// insert test
	benchmarkFunction_stress(test_vec_insert<t_ivec>, "insert");

	// erase test
	benchmarkFunction_stress(test_vec_erase<t_ivec>, "erase");

	// assign test
	benchmarkFunction_stress(test_vec_assign<t_ivec>, "assign");

	// // swap test
	// benchmarkFunction_stress(test_vec_swap<t_ivec>, "swap");

	// // element access functions
	// benchmarkFunction_stress(test_vec_elementAccess<t_ivec>, "element access");

	// // relational operators
	// benchmarkFunction_stress(test_vec_relationalOps<t_ivec>, "relational operators");

	// // iterators
	// benchmarkFunction_stress(test_vec_iterators<t_ivec>, "iterators");
}