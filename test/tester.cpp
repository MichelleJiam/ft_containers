/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tester.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/12 17:49:42 by mjiam         #+#    #+#                 */
/*   Updated: 2022/01/18 19:36:44 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

void	printTest(std::string const test_name, int &test_count) {
	std::cout << WHT << "\n===== " << CYN << test_name << WHT << " test =====\n";
	test_count += 1;
}

int		printResult(bool passed) {
	if (passed == true)
		std::cout << "RESULT: Contents are " << GRN << "equal.\n" << WHT;
	else
		std::cout << "RESULT: Contents are " << RED << "NOT equal.\n" << WHT;
	return (passed == true);
}

void	printPassing(int const pass_count, int const test_count) {
	if (pass_count == test_count) {
		std::cout << GRN << "\nPassed: " << pass_count << "/" << test_count
			<< WHT << std::endl;
	}
	else {
		std::cout << RED << "\nFailed: " << (test_count - pass_count) << "/"
			<< test_count << WHT << std::endl;
	}
}

// used to test lexicographical_compare
bool	mycomp(char c1, char c2) {
	return std::tolower(c1) < std::tolower(c2);
}
