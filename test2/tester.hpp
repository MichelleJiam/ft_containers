/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tester.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/12 17:46:50 by mjiam         #+#    #+#                 */
/*   Updated: 2022/03/30 17:30:03 by mjiam         ########   odam.nl         */
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

#include <vector>
#include "../containers/vector.hpp"
#include <stack>
#include "../containers/stack.hpp"
#include <map>
#include "../containers/map.hpp"
#include "../utils/pair.hpp"

# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"

# define STRESS_TIMES (INT_MAX / 100)

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

// TESTER_HELPER.CPP
// prints test unit header, taking unit name (e.g. "vector") as parameter
void	printHeader(std::string unit_name);
// prints test name and increments test_count
void	printTest(std::string const test_name);
// prints test case. see pre-function comment for example use.
void	printTestCase(std::string const test_case);
int		printResult(bool const passed);  // TODO: remove
void	printPassing(int passed, int tests);
template <typename T>
void    printVector(T& base_vec, std::string const ctnr_name = std::string(),
						std::string const test_case = std::string());
bool	mycomp(char const c1, char const c2);

// MAIN.CPP
void	benchmarkFunction(void (*testFunction)(unsigned long times),
							std::string const test_name);
void	benchmarkFunction_stress(void (*testFunction)(unsigned long times),
								std::string const test_name);

// used to print the contents of a container, e.g. after tests.
template <typename T>
void	printAtEnd(void (*printFunction)(T& container,
										std::string const cntr_name,
										std::string const test_case),
					T& container, std::string const cntr_name,
					std::string const test_case = std::string()) {
	std::cout << "\nCurrent state of container: " << std::endl;
	printFunction(container, cntr_name, test_case);
}

// container test units
void	test_vector();
void	test_utils();
void	test_stack();

#endif
