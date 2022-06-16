/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tester_helper.cpp                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 16:54:22 by mjiam         #+#    #+#                 */
/*   Updated: 2022/06/16 23:08:06 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

#define header_width 42
#define ISEVENLEN(String) (String.length() % 2 == 0 ? true : false)

// helper function for centering output
void	alignedPrint(std::string str,
						int linelength, bool newline = true) {
	int spaces = (linelength - str.size()) / 2;
	if (spaces > 0)
		std::cout << std::string(spaces, ' ');
	std::cout << str;
	if (spaces > 0)
   		std::cout << std::string(spaces, ' ');
	if (newline)
		std::cout << "\n";
}

// aligns header text by adding spaces to left & right sides
std::string	spaceHeaderText(int num_spaces, std::string const& text) {
	std::string	spaces(num_spaces, ' ');
	
	if (ISEVENLEN(text)) // if text len is even
		return (spaces + text + spaces.substr(1)); // print uneven number of spaces
	else
		return (spaces + text + spaces);
}

std::string	formatMiddle(int inner_width, std::string const& lside,
							std::string text, std::string const& rside) {
	if (text[0] == ' ')	// so leading spaces don't throw off banner alignment
		text = text.substr(1);
	int num_spaces = (inner_width - text.length()) / 2;
	std::string	spacedText;
	if (text.length() % 2 == 0) // if text len is even
		spacedText = spaceHeaderText(num_spaces + 1, text);
	else
		spacedText = spaceHeaderText(num_spaces, text);
	return (lside + spacedText + rside);
}

void	printHeader(std::string header_text) {
	// converting header_text to uppercase
	std::transform(header_text.begin(), header_text.end(),
						header_text.begin(), ::toupper);
	
	std::string header = "/*-----------------------+";
	std::string footer = "  +-----------------------*/";

	std::cout << "\n" << YEL;
	alignedPrint(header, header_width);
	// loop for printing longer header text in multiple lines
	for (size_t i = 0; i < header_text.length(); i += 20) {
		std::string middle = formatMiddle(23, "  |", header_text.substr(i, 20), "|");
		alignedPrint(middle, header_width);
	}
	alignedPrint(footer, header_width);
	std::cout << WHT;
}

void	printTest(std::string const& test_name) {
#ifdef SIMPLE
	std::cout << "\nTESTING: " << test_name << std::endl;
#else
	std::string header(header_width, '=');
	std::cout << "\n" << header << "\n" << CYN;
	alignedPrint(test_name, header_width);
	std::cout << WHT << header << "\n";
#endif
}

// Example test_case argument: "insert(begin + 1, [1], [2])"
//		where [n] denotes value at address for visual simplicity
void	printTestCase(std::string const& test_case) {
#ifndef SIMPLE
	std::cout << "\nTest case: " << GRN << test_case << WHT << "\n\n";
#else
	std::cout << "\nTest case: " << test_case << "\n\n";
#endif
}

int		printResult(bool const passed) {
	if (passed == true)
		std::cout << "RESULT: Contents are " << GRN << "equal.\n" << WHT;
	else
		std::cout << "RESULT: Contents are " << RED << "NOT equal.\n" << WHT;
	return (passed == true);
}

void	printPassing(int const passed, int const tests) {
	// passed_tests pair containing (passed_count, test_count)
	if (passed == tests) {
		std::cout << GRN << "\nPassed: " << passed << "/"
			<< tests << WHT << std::endl;
	}
	else {
		std::cout << RED << "\nFailed: "
			<< (tests - passed) << "/"
			<< tests << WHT << std::endl;
	}
}

// used to test lexicographical_compare
bool	mycomp(char const c1, char const c2) {
	return std::tolower(c1) < std::tolower(c2);
}

#undef header_width
