/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_vector.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 16:54:47 by mjiam         #+#    #+#                 */
/*   Updated: 2022/03/31 17:01:42 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

typedef IMPL::vector<int> t_ivec;

template <typename T>
void	test_vec_constructors(size_t size) {
	T	fill_vec(size, 42);
	T	range_vec(fill_vec.begin(), fill_vec.end() - 2);
	T	copy_vec(range_vec);
	
	assert(fill_vec.size() == size
			&& range_vec.size() == (size) - 2
			&& copy_vec.size() == range_vec.size());
	
	T vct(5);
	typename T::iterator it = vct.begin(), ite = vct.end();

	std::cout << "len: " << (ite - it) << std::endl;
	for (; it != ite; ++it)
		*it = (ite - it);
}

template <typename T>
void	test_vec_pushback(size_t size) {
	printTestCase("vector.push_back([1-size])");

	T	vector;

	for (size_t i = 1; i <= size; i++)
		vector.push_back(i);

	assert(vector.size() == size);

	if (size < 100)	// only print vector contents when not stress testing
		printVector(vector, "vector");
}

template <typename T>
void	test_vec_popback(size_t size) {
	printTestCase("vector.pop_back() x size");

	T	vector(size, 42);

	for (size_t i = 1; i <= size; i++)
		vector.pop_back();

	assert(vector.size() == 0);

	if (size < 100)
		printVector(vector, "vector");
}

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

	T	vector(size, 42);
	vector.clear();

	if (size < 100)
		printVector(vector, "vector");
}

template <typename T>
void	test_vec_reserve(size_t size) {
	printTestCase("vector.reserve([size])");
	
	T		vector;
	size_t	oldcap = vector.capacity();

	vector.reserve(size);
	std::cout << "vector capacity was " << oldcap
		<< ", is now " << vector.capacity() << ".\n";
	
	if (size < 100)
		printVector(vector, "vector");
}

template <typename T>
void	test_vec_resize(size_t size) {
	printTestCase("vector.resize(size, 42)");

	T	vector(4, 20);

	vector.resize(size, 42);

	if (size < 100)
		printVector(vector, "vector");
}

template <typename T>
void	test_vec_insert(size_t size) {
	T						vector(size, 42);
	typename T::iterator	it = vector.end();
	
	vector.insert(it, 88);
	if (size < 100)
		printVector(vector, "vector", "insert(end, 88)");

	it = vector.end();
	vector.insert(it - 1, 13);
	if (size < 100)
		printVector(vector, "vector", "insert(end - 1, 13)");

	it = vector.begin();
	vector.insert(it + 2, 4, 7);
	if (size < 100)
		printVector(vector, "vector", "insert(begin + 2, 4, 7)");

	T	anothervector(3, 21);
	it = vector.begin();
	anothervector.insert(anothervector.begin() + 1,
							it, it + 2);
	if (size < 100)
		printVector(anothervector, "anothervector", "insert(begin + 1, [42], [42])");

	it = anothervector.begin();
	anothervector.insert(it, 100);
	if (size < 100)
		printVector(anothervector, "anothervector", "insert(begin, 100)");
}

template <typename T>
void	test_vec_erase(size_t size) {
	T						vector(size, 42);
	typename T::iterator	it = vector.end();

	vector.erase(it - 2);
	if (size < 100)
		printVector(vector, "vector", "erase(end - 2)");

	it = vector.end();
	vector.erase(it - 3, it - 1);
	if (size < 100)
		printVector(vector, "vector", "erase(end - 3, end - 1)");

	it = vector.begin();
	vector.erase(it + 2, it + 4);
	if (size < 100)
		printVector(vector, "vector", "erase(begin + 1, begin + 3)");
}

template <typename T>
void	test_vec_assign(size_t size) {
	T	vector(size, 42);
	T	vec1, vec2, vec3;

	vec1.assign(7, vector[0]); // 7 ints
	if (size < 100)
		printVector(vec1, "vector 1", "assign(7, [42])");

	typename T::iterator it = vec1.begin();
	vec2.assign(it + 1, it + 6); // 5 central values from vec1
	if (size < 100)
		printVector(vec2, "vector 2", "assign(vec1.begin + 1, vec1.begin + 6)");
	
	vec3.assign(vector.begin(), vector.end()); // [size] elements
	if (size < 100)
		printVector(vec3, "vector 3", "assign(vector.begin, vector.end)");

	assert(vec1.size() == 7);
	assert(vec2.size() == 5);
	assert(vec3.size() == size);
}

template <typename T>
void	test_vec_swap(size_t size) {
	printTestCase("vec1.swap(vec2)");

	T	vec1(size, 13);
	T	vec2(size, 42);

	if (size < 100) {
		printVector(vec1, "vector 1 BEFORE swap");
		printVector(vec2, "vector 2 BEFORE swap");
	}
	vec1.swap(vec2);
	assert(vec1.size() == vec2.size());
	if (size < 100) {
		printVector(vec1, "vector 1 AFTER swap");
		printVector(vec2, "vector 2 AFTER swap");
	}
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
	
	if (size < 100)
		printVector(vector, "vector");
}

template <typename T>
void	test_vec_relationalOps(size_t size) {
	printTestCase("vector == != < <= > >=");

	T	vec1(size, 42);
	T	vec2(size / 2, 13);

	if (size < 100) {
		printVector(vec1, "vector 1");
		printVector(vec2, "vector 2");
	}
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

	std::cout << "begin: " << *vector.begin() << std::endl;
	std::cout << "begin + 1: " << *(vector.begin() + 1) << std::endl;
	std::cout << "end - 1: " << *(vector.end() - 1) << std::endl;
	std::cout << "rbegin: " << *vector.rbegin() << std::endl;
	std::cout << "rbegin + 1: " << *(vector.rbegin() + 1) << std::endl;
	std::cout << "rend - 1: " << *(vector.rend() - 1) << std::endl;
	
	if (size < 100) {
		std::cout << "iterating from begin to end: ";
		for (t_ivec::iterator it = vector.begin(); it != vector.end(); ++it)
			std::cout << *it << " ";
		std::cout << "\niterating backwards from rbegin to rend: ";
		for (t_ivec::reverse_iterator rit = vector.rbegin(); rit != vector.rend(); ++rit)
			std::cout << *rit << " ";
		std::cout << std::endl << std::endl;
		printVector(vector, "vector");
	}
}

void test_vector() {
#ifndef SIMPLE
	printHeader("testing vector");
#endif

	// constructor test
	benchmarkFunction_stress(test_vec_constructors<t_ivec>, "fill/range/copy constructors");
	
	// // push_back test
	// benchmarkFunction_stress(test_vec_pushback<t_ivec>, "push_back");

	// // pop_back test
	// benchmarkFunction_stress(test_vec_popback<t_ivec>, "pop_back");

	// // empty test
	// benchmarkFunction_stress(test_vec_empty<t_ivec>, "empty");

	// // clear test
	// benchmarkFunction_stress(test_vec_clear<t_ivec>, "clear");
	
	// // reserve test
	// benchmarkFunction_stress(test_vec_reserve<t_ivec>, "reserve");

	// // resize test
	// benchmarkFunction_stress(test_vec_resize<t_ivec>, "resize");
	
	// // insert test
	// benchmarkFunction_stress(test_vec_insert<t_ivec>, "insert");

	// // erase test
	// benchmarkFunction_stress(test_vec_erase<t_ivec>, "erase");

	// // assign test
	// benchmarkFunction_stress(test_vec_assign<t_ivec>, "assign");

	// // swap test
	// benchmarkFunction_stress(test_vec_swap<t_ivec>, "swap");

	// // element access functions
	// benchmarkFunction_stress(test_vec_elementAccess<t_ivec>, "element access");

	// // relational operators
	// benchmarkFunction_stress(test_vec_relationalOps<t_ivec>, "relational operators");

	// // iterators
	// benchmarkFunction_stress(test_vec_iterators<t_ivec>, "iterators");
}