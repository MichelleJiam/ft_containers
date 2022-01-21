/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tester_helper.cpp                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 16:54:22 by mjiam         #+#    #+#                 */
/*   Updated: 2022/01/21 19:01:47 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

#define header_width 42

// helper function for centering output
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

	out << "\n" << YEL;
	alignedPrint(out, header, header_width);
	alignedPrint(out, " |" + spaces + text + spaces + "|", header_width);
	alignedPrint(out, footer, header_width);
	out << WHT;
}

template <typename S>
void	printTest(S &out, std::string const test_name, int &test_count) {	
	std::string header(header_width, '=');
	out << "\n" << header << "\n" << CYN;
	alignedPrint(out, test_name, header_width);
	out << WHT << header << "\n";
	test_count += 1;
}

int		printResult(bool const passed) {
	if (passed == true)
		std::cout << "RESULT: Contents are " << GRN << "equal.\n" << WHT;
	else
		std::cout << "RESULT: Contents are " << RED << "NOT equal.\n" << WHT;
	return (passed == true);
}

void	printPassing(IMPL::pair<int,int> const passed_tests) {
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

// namespace std {
// 	inline std::string	get_name() { return "std"; }
// }

// namespace ft {
// 	inline std::string	get_name() { return "ft"; }
// 	std::ofstream		&getoutputfile(std::string impl_name) {

// 	}
// }