/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tester.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/12 17:46:50 by mjiam         #+#    #+#                 */
/*   Updated: 2022/01/25 18:06:22 by mjiam         ########   odam.nl         */
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

#define header_width 42

// used for comparison between ft and std results
template <class T>
bool	is_not_equal(T const& lhs, T const& rhs) {
	return (lhs != rhs);
}

// helper function used by printing functions for centering output
template <typename S>
void	alignedPrint(S &out, std::string str,
						int linelength, bool newline = true)
{
	int spaces = (linelength - str.size()) / 2;
	
	if (spaces > 0)
		out << std::string(spaces, ' ');
	out << str;
	if (spaces > 0)
   		out << std::string(spaces, ' ');
	if (newline)
		out << "\n";
}

// prints test unit header, taking unit name (e.g. "vector") as parameter
template <typename S>
void	printHeader(S &out, std::string unit_name) {
	// converting unit_name to uppercase
	std::transform(unit_name.begin(), unit_name.end(),
						unit_name.begin(), ::toupper);
	std::string text = "TESTING " + unit_name;
	// for aligning text within header
	int	inner_width = 23;
	std::string	spaces((inner_width - text.size()) / 2, ' ');
	std::string header = "/*-----------------------+";
	std::string footer = "  +-----------------------*/";

	// don't output with colour if saving output to txt file
#if !SAVE
	out << YEL;
#endif

	out << "\n";
	alignedPrint(out, header, header_width);
	alignedPrint(out, " |" + spaces + text + spaces + " |", header_width);
	alignedPrint(out, footer, header_width);

#if !SAVE
	out << WHT;
#endif
}

// prints test name and increments test_count
template <typename S>
void	printTest(S &out, std::string const test_name, int &test_count) {	
	std::string header(header_width, '=');
	out << "\n" << header << "\n";

#if !SAVE
	out << CYN;
#endif

	alignedPrint(out, test_name, header_width);

#if !SAVE
	out << WHT;
#endif

	out << header << "\n";
	test_count += 1;
}

int		printResult(bool const passed);
void	printPassing(IMPL::pair<int,int> const passed_tests);
bool	mycomp(char const c1, char const c2);

// std::ofstream	&getoutputfile(void);

// Unit tests
#include "test_vector.hpp"

#undef header_width 
#endif
