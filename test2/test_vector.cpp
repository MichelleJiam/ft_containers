/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_vector.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 16:54:47 by mjiam         #+#    #+#                 */
/*   Updated: 2022/02/25 18:43:41 by mjiam         ########   odam.nl         */
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
}

template <typename T>
void	test_vec_assign(T& vector) {
	T	vec1, vec2, vec3;

	vec1.assign(7, vector[0]); // 7 ints
	printVector(vec1, "vector 1", "assign(7, [42])");

	typename T::iterator it = vec1.begin();
	vec2.assign(it + 1, it + 6); // 5 central values from vec1
	printVector(vec2, "vector 2", "assign(vec1.begin + 1, vec1.begin + 6)");

	int	i_array[] = {32, 1, 100};
	
	vec3.assign(i_array, i_array + 3); // 3 ints from array
	printVector(vec3, "vector 3", "assign(array[0], array[3])");

	assert(vec1.size() == 7);
	assert(vec2.size() == 5);
	assert(vec3.size() == 3);
}

template <typename T>
void	test_vec_clear(T& vector) {
	vector.clear();
}

template <typename T>
void	test_vec_empty(T& vector) {
	std::cout << std::boolalpha
		<< "is vector empty: " << vector.empty() << std::endl;
}

template <typename T>
void	test_vec_erase(T& vector) {
	typename T::iterator it = vector.end();

	vector.erase(it - 2);
	printVector(vector, "vector", "erase(end - 2)");

	it = vector.end();
	vector.erase(it - 3, it - 1);
	printVector(vector, "vector", "erase(end - 3, end - 1)");

	it = vector.begin();
	vector.erase(it + 2, it + 4);
	printVector(vector, "vector", "erase(begin + 2, begin + 4)");
}

template <typename T>
void	test_vec_insert(T& vector) {
	T	copyvector(vector);
	typename T::iterator it = copyvector.end();
	
	copyvector.insert(it, 88);
	printVector(copyvector, "copyvector", "insert(end, 88)");

	it = copyvector.end();
	copyvector.insert(it - 1, 13);
	printVector(copyvector, "copyvector", "insert(end - 1, 13)");

	it = copyvector.begin();
	copyvector.insert(it + 2, 4, 7);
	printVector(copyvector, "copyvector", "insert(begin + 2, 4, 7)");

	T	anothervector(3, 42);
	it = copyvector.begin();
	anothervector.insert(anothervector.begin() + 1,
							it, it + 2);
	printVector(anothervector, "anothervector", "insert(begin + 1, [1], [2])");

	it = anothervector.begin();
	anothervector.insert(it, 100);
	printVector(anothervector, "anothervector", "insert(begin, 100)");
}


template <typename T>
void	test_vec_pushback(T& vector) {
	printTestCase("push_back([1-10])");
	for (int i = 1; i <= 10; i++)
		vector.push_back(i);
}

template <typename T>
void	test_vec_popback(T& vector) {
	vector.pop_back();
}

template <typename T>
void	test_vec_reserve(T& vector) {
	size_t   oldcap = vector.capacity();

	printTestCase("reserve(42)");
	vector.reserve(42);
	std::cout << "\nvector capacity was " << oldcap
		<< ", is now " << vector.capacity() << ".\n";
}

template <typename T>
void	test_vec_resize(T& vector) {
	printTestCase("resize(5, 42)");
	vector.resize(5, 42);
}

template <typename T>
void	test_vec_swap(T& vector) {
	T	vector_b(vector.size(), 13);

	printVector(vector, "vector 1 BEFORE swap");
	printVector(vector_b, "vector 2 BEFORE swap");
	vector.swap(vector_b);
	printVector(vector_b, "vector 2 AFTER swap");
	assert(vector.size() == vector_b.size());
}

template <typename T>
void	test_vec_constructors(T& vector) {
	T	fill_vec(1000, 42);
	T	range_vec(fill_vec.begin(), fill_vec.end() - 2);
	T	copy_vec(vector);
	
	assert(fill_vec.size() == 1000
			&& range_vec.size() == 998
			&& copy_vec.size() == vector.size());
}

void test_vector() {
#ifndef SIMPLE
	printHeader("testing vector");
#endif

	t_ivec		base_vec;
	
	// push_back test
	benchmarkFunction_multirun(test_vec_pushback<t_ivec>, base_vec,
								"push_back", true, "vector");
	// // benchmarkFunction(base_vec.push_back)

	// empty test
	benchmarkFunction_multirun(test_vec_empty<t_ivec>, base_vec, "empty",
								true, "vector");
	
	// pop_back test
	benchmarkFunction_multirun(test_vec_popback<t_ivec>, base_vec, "pop_back",
								true, "vector");

	// fill constructor test
	benchmarkFunction_multirun(test_vec_constructors<t_ivec>, base_vec,
								"fill/range/copy constructors", false);

	// clear test
	t_ivec	copy_vec(base_vec);
	benchmarkFunction_multirun(test_vec_clear<t_ivec>, copy_vec, "clear",
								true, "vector");
	
	// reserve test
	benchmarkFunction_multirun(test_vec_reserve<t_ivec>, base_vec, "reserve",
								true, "vector");
	
	// insert test
	benchmarkFunction_multirun(test_vec_insert<t_ivec>, base_vec, "insert", false);

	// resize test
	benchmarkFunction_multirun(test_vec_resize<t_ivec>, copy_vec, "resize",
								true, "vector");

	// erase test
	benchmarkFunction_multirun(test_vec_erase<t_ivec>, base_vec, "erase",
								true, "vector");

	// assign test
	benchmarkFunction_multirun(test_vec_assign<t_ivec>, copy_vec, "assign", false);

	// swap test
	benchmarkFunction_multirun(test_vec_swap<t_ivec>, copy_vec, "swap",
								true, "vector 1 AFTER swap");

	// element access functions
	benchmarkFunction_multirun(test_vec_elementAccess<t_ivec>, base_vec, 
								"element access", true, "vector");

	// relational operators
	benchmarkFunction_multirun(test_vec_relationalOps<t_ivec>, base_vec,
								"relational operators", false);

	// iterators
	benchmarkFunction_multirun(test_vec_iterators<t_ivec>, base_vec,
								"iterators", true, "vector");
}