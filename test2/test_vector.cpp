/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_vector.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 16:54:47 by mjiam         #+#    #+#                 */
/*   Updated: 2022/04/07 16:54:25 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

#define T1 int
typedef IMPL::vector<T1> t_vec;

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
	typename T::iterator	ret = vector.insert(it, 88);
	
	std::cout << "insert(it, 88) returns " << *ret << std::endl;
	if (size < 100)
		printVector(vector, "vector", "insert(end, 88)");

	it = vector.end();
	ret = vector.insert(it - 1, 13);
	std::cout << "insert(it - 1, 13) returns " << *ret << std::endl;
	if (size < 100)
		printVector(vector, "vector", "insert(end - 1, 13)");

	it = vector.begin();
	vector.insert(it + 2, 4, 7);
	if (size < 100)
		printVector(vector, "vector", "insert(begin + 2, 4, 7)");

	T	vector2;
	it = vector2.begin();
	ret = vector2.insert(it, 100);
	std::cout << "insert(it, 100) returns " << *ret << std::endl;
	if (size < 100)
		printVector(vector2, "empty vector2", "insert(begin, 100)");

	it = vector.begin();
	vector2.insert(vector2.begin(), it, it + 2);
	if (size < 100)
		printVector(vector2, "vector2", "insert(begin, [42], [42])");
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
void	printSize(T const &vct, bool print_content = true)
{
	const typename T::size_type size = vct.size();
	const typename T::size_type capacity = vct.capacity();
	const std::string isCapacityOk = (capacity >= size) ? "OK" : "KO";
	// Cannot limit capacity's max value because it's implementation dependent

	std::cout << "size: " << size << std::endl;
	std::cout << "capacity: " << capacity << " " << isCapacityOk << std::endl;
	std::cout << "max_size: " << vct.max_size() << std::endl;
	if (print_content)
	{
		typename T::const_iterator it = vct.begin();
		typename T::const_iterator ite = vct.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}
template <typename T>
void	prepost_incdec(T &vct)
{
	typename T::iterator it = vct.begin();
	typename T::iterator it_tmp;

	std::cout << "Pre inc" << std::endl;
	it_tmp = ++it;
	std::cout << *it_tmp << " | " << *it << std::endl;

	std::cout << "Pre dec" << std::endl;
	it_tmp = --it;
	std::cout << *it_tmp << " | " << *it << std::endl;

	std::cout << "Post inc" << std::endl;
	it_tmp = it++;
	std::cout << *it_tmp << " | " << *it << std::endl;

	std::cout << "Post dec" << std::endl;
	it_tmp = it--;
	std::cout << *it_tmp << " | " << *it << std::endl;
	std::cout << "###############################################" << std::endl;
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
		for (t_vec::reverse_iterator rit = vector.rbegin(); rit != vector.rend(); ++rit)
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
	benchmarkFunction_stress(test_vec_constructors<t_vec>, "fill/range/copy constructors");
	
	// push_back test
	benchmarkFunction_stress(test_vec_pushback<t_vec>, "push_back");

	// pop_back test
	benchmarkFunction_stress(test_vec_popback<t_vec>, "pop_back");

	// empty test
	benchmarkFunction_stress(test_vec_empty<t_vec>, "empty");

	// clear test
	benchmarkFunction_stress(test_vec_clear<t_vec>, "clear");
	
	// reserve test
	benchmarkFunction_stress(test_vec_reserve<t_vec>, "reserve");

	// resize test
	benchmarkFunction_stress(test_vec_resize<t_vec>, "resize");
	
	// insert test
	benchmarkFunction_stress(test_vec_insert<t_vec>, "insert");

	// erase test
	benchmarkFunction_stress(test_vec_erase<t_vec>, "erase");

	// assign test
	benchmarkFunction_stress(test_vec_assign<t_vec>, "assign");

	// swap test
	benchmarkFunction_stress(test_vec_swap<t_vec>, "swap");

	// element access functions
	benchmarkFunction_stress(test_vec_elementAccess<t_vec>, "element access");

	// relational operators
	benchmarkFunction_stress(test_vec_relationalOps<t_vec>, "relational operators");

	// iterators
	benchmarkFunction_stress(test_vec_iterators<t_vec>, "iterators");
}