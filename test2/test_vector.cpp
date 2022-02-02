/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_vector.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 16:54:47 by mjiam         #+#    #+#                 */
/*   Updated: 2022/02/02 18:39:20 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"
#include "../containers/vector.hpp"

typedef IMPL::vector<int> t_ivec;

template <typename T>
void    printVector(T &base_vec, std::string const &test_name)
{
	if (!test_name.empty())
		printTest(test_name);
	std::cout << "\ncapacity: " << base_vec.capacity() << std::endl;
	std::cout << "size:     " << base_vec.size() << std::endl;
	std::cout << "contents: [";
	for (unsigned i = 0; i < base_vec.size(); i++)
		std::cout << ' ' << base_vec[i];
	std::cout << " ]\n";
}

template <typename T>
void	test_vec_elementAccess(T &vector) {
	std::cout << std::endl;
	std::cout << "vec[3]: " << vector[3] << std::endl;
	std::cout << "vec.at(1): " << vector.at(1) << std::endl;
	std::cout << "vec.front(): " << vector.front() << std::endl;
	std::cout << "vec.back(): " << vector.back() << std::endl;
}

template <typename T>
void	test_vec_relationalOps(T &vector) {
	T	vec1(3, 42);
	T	vec2(2, 13);

	printVector(vec1);
	printVector(vec2);
	std::cout << std::boolalpha << std::endl;
	std::cout << "vec1 == vec2: " << (vec1 == vec2) << std::endl;
	std::cout << "vec1 != vec2: " << (vec1 != vec2) << std::endl;
	std::cout << "vec1 < vec2: " << (vec1 < vec2) << std::endl;
	std::cout << "vec1 <= vec2: " << (vec1 <= vec2) << std::endl;
	std::cout << "vec1 > vec2: " << (vec1 > vec2) << std::endl;
	std::cout << "vec1 >= vec2: " << (vec1 >= vec2) << std::endl;
	std::cout << "vector != vec1: " << (vector != vec1) << std::endl;
}

template <typename T>
void	test_vec_iterators(T &vector) {
	std::cout << "begin: " << *vector.begin() << std::endl;
	std::cout << "end - 1: " << *(vector.end() - 1) << std::endl;
	std::cout << "rbegin: " << *vector.rbegin() << std::endl;
	std::cout << "rend - 1: " << *(vector.rend() - 1) << std::endl;
}

template <typename T>
void	test_vec_assign(T &vector) {
	T	vec1, vec2, vec3;

	vec1.assign(7, vector[0]); // 7 ints
	printVector(vec1);

	typename T::iterator it = vec1.begin();
	vec2.assign(it + 1, it + 6); // 5 central values from vec1
	printVector(vec2);

	int	i_array[] = {32, 1, 100};
	
	vec3.assign(i_array, i_array + 3); // 3 ints from array
	printVector(vec3);

	assert(vec1.size() == 7);
	assert(vec2.size() == 5);
	assert(vec3.size() == 3);
}

template <typename T>
void	test_vec_clear(T &vector) {
	vector.clear();
}

template <typename T>
void	test_vec_empty(T &vector) {
	std::cout << std::boolalpha
		<< "is vector empty: " << vector.empty() << std::endl;
}

template <typename T>
void	test_vec_erase(T &vector) {
	typename T::iterator it = vector.end();

	vector.erase(it - 2);
	it = vector.end();
	vector.erase(it - 3, it - 1);
	it = vector.begin();
	vector.erase(it + 2, it + 4);
}

template <typename T>
void	test_vec_insert(T &vector) {
	T	dupvector(vector);
	typename T::iterator it = dupvector.end();
	
	dupvector.insert(it - 1, 13);
	printVector(dupvector);

	it = dupvector.begin();
	dupvector.insert(it + 2, 4, 7);
	printVector(dupvector);

	T	anothervector(3, 42);
	it = dupvector.begin();
	anothervector.insert(anothervector.begin() + 1,
							it, it + 2);
	printVector(anothervector);
}


template <typename T>
void	test_vec_pushback(T &vector) {
	for (int i = 1; i <= 10; i++)
		vector.push_back(i);
}

template <typename T>
void	test_vec_popback(T &vector) {
	vector.pop_back();
}

template <typename T>
void	test_vec_reserve(T &vector) {
	size_t   oldcap = vector.capacity();

	vector.reserve(42);
	std::cout << "\nvector capacity was " << oldcap
		<< ", is now " << vector.capacity() << ".\n";
}

template <typename T>
void	test_vec_resize(T &vector) {
	vector.resize(5, 42);
}

template <typename T>
void	test_vec_swap(T &vector) {
	T	vector_b(vector.size(), 13);

	std::cout << "\nBEFORE swap vector 1:\n";
	printVector(vector);
	std::cout << "\nBEFORE swap vector 2:\n";
	printVector(vector_b);
	vector.swap(vector_b);
	std::cout << "\nAFTER swap vector 2:\n";
	printVector(vector_b);
	assert(vector.size() == vector_b.size());
}

template <typename T>
void	test_vec_constructors(T &vector) {
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
								"push_back", true);
	// // benchmarkFunction(base_vec.push_back)

	// empty test
	benchmarkFunction_multirun(test_vec_empty<t_ivec>, base_vec, "empty", true);
	
	// pop_back test
	benchmarkFunction_multirun(test_vec_popback<t_ivec>, base_vec, "pop_back", true);

	// fill constructor test
	// benchmarkFunction_multirun(test_vec_constructors<t_ivec>, base_vec,
						// "fill/range/copy constructors", false);
	// printTest("fill constructor");
	// start = clock();
	// t_ivec	fill_vec(4, 42);
	// printVector(fill_vec);
	// std::cout << std::fixed << "Duration of operation: " << ((clock() - start) / (double)CLOCKS_PER_SEC) << "seconds." << std::endl;
	// std::cout.unsetf(std::ios::fixed);

	// clear test
	t_ivec	copy_vec(base_vec);
	benchmarkFunction_multirun(test_vec_clear<t_ivec>, copy_vec, "clear", true);
	
	// reserve test
	benchmarkFunction_multirun(test_vec_reserve<t_ivec>, base_vec, "reserve", true);
	
	// insert test
	benchmarkFunction_multirun(test_vec_insert<t_ivec>, base_vec, "insert", true);

	// resize test
	benchmarkFunction_multirun(test_vec_resize<t_ivec>, copy_vec, "resize", true);

	// erase test
	benchmarkFunction_multirun(test_vec_erase<t_ivec>, base_vec, "erase", true);

	// assign test
	benchmarkFunction_multirun(test_vec_assign<t_ivec>, copy_vec, "assign", false);

	// swap test
	benchmarkFunction_multirun(test_vec_swap<t_ivec>, copy_vec, "swap", true);

	// element access functions
	benchmarkFunction_multirun(test_vec_elementAccess<t_ivec>, base_vec, "element access", true);

	// relational operators
	benchmarkFunction_multirun(test_vec_relationalOps<t_ivec>, base_vec, "relational operators", false);

	// iterators
	benchmarkFunction_multirun(test_vec_iterators<t_ivec>, base_vec, "iterators", true);
}