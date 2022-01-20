/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tester.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/12 17:46:50 by mjiam         #+#    #+#                 */
/*   Updated: 2022/01/20 21:37:24 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_HPP
#define TESTER_HPP

#include <iostream>
#include <fstream>
#include <algorithm> // transform
#include <cctype> // tolower
#include <iomanip> // setw
#include "../utils/pair.hpp" // pair

# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"

template <class T>
bool	is_not_equal(T const& lhs, T const& rhs) {
    return (lhs != rhs);
}

// prints test unit header, taking unit name (e.g. "vector") as parameter
void	printHeader(std::string unit_name);
// prints test name and increments test_count
void	printTest(std::string const test_name, int &test_count);
int     printResult(bool const passed);
void	printPassing(IMPL::pair<int,int> const passed_tests);
bool	mycomp(char const c1, char const c2);

// container test units
void    test_vector(IMPL::pair<int,int> &passed_tests, std::ofstream &outfile);
void    test_utils(IMPL::pair<int,int> &passed_tests, std::ofstream &outfile);

#endif
