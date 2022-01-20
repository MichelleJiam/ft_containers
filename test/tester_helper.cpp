/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tester_helper.cpp                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 16:54:22 by mjiam         #+#    #+#                 */
/*   Updated: 2022/01/20 18:52:43 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

#define header_width 42

// helper function for centering output
void	alignedPrint(std::string str, int linelength, bool newline = true)
{
	int spaces = (linelength - str.size()) / 2;
	
	if (spaces > 0)
		std::cout << std::string(spaces, ' ');
	std::cout << str;
	if (spaces > 0)
   		std::cout << std::string(spaces, ' ');
	if (newline)
		std::cout << "\n";
}

void	printHeader(std::string unit_name) {
	// converting unit_name to uppercase
	std::transform(unit_name.begin(), unit_name.end(),
						unit_name.begin(), ::toupper);
	std::string text = "TESTING " + unit_name;
	// for aligning text within header
	int	inner_width = 23;
	std::string	spaces((inner_width - text.size()) / 2, ' ');
	std::string header = "/*-----------------------+";
	std::string footer = "  +-----------------------*/";

	std::cout << "\n" << YEL;
	alignedPrint(header, header_width);
	alignedPrint(" |" + spaces + text + spaces + "|", header_width);
	alignedPrint(footer, header_width);
	std::cout << WHT;
}

void	printTest(std::string const test_name, int &test_count) {	
	std::string header(header_width, '=');
	std::cout << "\n" << header << "\n" << CYN;
	alignedPrint(test_name, header_width);
	std::cout << WHT << header << "\n";
	test_count += 1;
}

int		printResult(bool const passed) {
	if (passed == true)
		std::cout << "RESULT: Contents are " << GRN << "equal.\n" << WHT;
	else
		std::cout << "RESULT: Contents are " << RED << "NOT equal.\n" << WHT;
	return (passed == true);
}

void	printPassing(ft::pair<int,int> const passed_tests) {
	// passed_tests pair containing (passed_count, test_count)
	if (passed_tests.first == passed_tests.second) {
		std::cout << GRN << "\nPassed: " << passed_tests.first << "/"
			<< passed_tests.second << WHT << std::endl;
	}
	else {
		std::cout << RED << "\nFailed: "
			<< (passed_tests.second - passed_tests.first) << "/"
			<< passed_tests.second << WHT << std::endl;
	}
}

// used to test lexicographical_compare
bool	mycomp(char const c1, char const c2) {
	return std::tolower(c1) < std::tolower(c2);
}
