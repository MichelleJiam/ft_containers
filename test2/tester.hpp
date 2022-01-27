/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tester.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/12 17:46:50 by mjiam         #+#    #+#                 */
/*   Updated: 2022/01/27 21:56:09 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_HPP
#define TESTER_HPP

#include <iostream>
#include <fstream>
#include <algorithm> // transform
#include <cctype> // tolower
#include <time.h>  // clock
#include <iomanip> // setprecision

#include "../containers/vector.hpp"
#include "../utils/pair.hpp" // pair

# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"

#ifndef IMPL
# define IMPL ft
#endif

// template <typename T>
// struct	typeHelper {
// 	typedef IMPL::vector<T>	vector;
// };

// typedef	void (IMPL::vector<int>::*vecVoidFn)(void);
// typedef void (*testFn)(IMPL::vector<int> &vector);

// #define CALL_MEMBER_FN(object, ptrToMemberFn)	((object).*(ptrToMemberFn))

// template <typename T>
// void	benchmarkFunction(T &object, vecVoidFn fn) {
// 	clock_t start = clock();

// 	CALL_MEMBER_FN(object, fn)();
// 	std::cout << "Duration of operation: " << std::fixed
// 		<< ((clock() - start) / (double)CLOCKS_PER_SEC) << "seconds."
// 		<< std::endl;
// 	std::cout.unsetf(std::ios::fixed);	// restores cout to general format
// }

// prints test unit header, taking unit name (e.g. "vector") as parameter
void	printHeader(std::string unit_name);
// prints test name and increments test_count
void	printTest(std::string const test_name);
int		printResult(bool const passed);
void	printPassing(int passed, int tests);
template <typename T>
void    printVector(T &base_vec, std::string const &test_name = std::string());
bool	mycomp(char const c1, char const c2);

// times a single execution of a function on the container
// that's been passed as reference.
// Also prints the test name and contents of the container.
template <typename T>
void	benchmarkFunction(void (*testFunction)(T &vector), T &container,
						std::string const test_name, bool print_contents) {
	printTest(test_name);
	
	clock_t start = clock();
	testFunction(container);
	clock_t	end = clock();
	std::cout << "\nDuration of operation: "
		<< std::fixed << std::setprecision(4)
		<< ((end - start) / (double)CLOCKS_PER_SEC) * 1000 << " milliseconds."
		<< std::endl;
	std::cout.unsetf(std::ios::fixed);	// restores cout to general format
	if (print_contents)
		printVector(container);
}

// runs single-run benchmarking on referenced container, then runs function
// 1000 times on a temporary copy of the container to show cumulative performance
// without affecting the container passed.
template <typename T>
void	benchmarkFunction_multirun(void (*testFunction)(T &vector), T &container,
						std::string const test_name, bool print_contents) {
	benchmarkFunction(testFunction, container, test_name, print_contents);
	
	// saving cout buffer for restoring later
	std::streambuf	*orig_buf = std::cout.rdbuf();
	// disconnecting cout buffer to silence output
	std::cout.rdbuf(NULL);

	clock_t start = clock();
	// run test on a fresh vector 1000 times
	for (size_t i = 0; i < 1000; i++) {
		T	tmp_vec(20, 42);
		testFunction(tmp_vec);
	}
	clock_t	end = clock();

	// restoring cout buffer
	std::cout.rdbuf(orig_buf);
	
	std::cout << "\nDuration of 1000 operations: "
		<< std::fixed << std::setprecision(4)
		<< ((end - start) / (double)CLOCKS_PER_SEC) * 1000 << " milliseconds."
		<< std::endl;
	std::cout.unsetf(std::ios::fixed);	// restores cout to general format
}

// container test units
void	test_vector();
void	test_utils();

#endif
