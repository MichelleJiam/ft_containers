/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tester.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/12 17:46:50 by mjiam         #+#    #+#                 */
/*   Updated: 2022/07/07 17:43:43 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_HPP
#define TESTER_HPP

#include <iostream>
#include <fstream>
#include <algorithm> // transform
#include <cassert> // assert
#include <cctype> // tolower
#include <climits> // INT_MAX
#include <iomanip> // setprecision
#include <time.h>  // clock

#include <vector>
#include "../containers/vector.hpp"
#include <stack>
#include "../containers/stack.hpp"
#include <map>
#include "../containers/map.hpp"
#include <set>
#include "../containers/set.hpp"
#include <list> // for testing map & set
#include "../utils/pair.hpp"

# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"

# define STRESS_SIZE (INT_MAX / 2000)

#ifndef IMPL
# define IMPL ft
#endif

// TESTER_HELPER.CPP
// prints test unit header, taking unit name (e.g. "vector") as parameter
void	printHeader(std::string header_text);
// prints test name and increments test_count
void	printTest(std::string const& test_name);
// prints test case. see pre-function comment for example use.
void	printTestCase(std::string const& test_case);
int		printResult(bool const passed);  // TODO: remove
void	printPassing(int const passed, int const tests);
bool	mycomp(char const c1, char const c2);

// TEST_VECTOR.CPP
template <typename T>
void    printVector(T& base_vec, bool print_contents = true,
						std::string const& cntr_name = std::string(),
						std::string const& test_case = std::string());

// MAIN.CPP
void	benchmarkFunction(void (*testFunction)(size_t size),
							std::string const& test_name);
void	benchmarkFunction_stress(void (*testFunction)(size_t size),
								std::string const& test_name);

// container test units
void	test_vector();
void	test_utils();
void	test_stack();
void	test_map();
void	test_set();

#endif
