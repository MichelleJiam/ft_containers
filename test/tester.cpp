/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tester.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/12 17:49:42 by mjiam         #+#    #+#                 */
/*   Updated: 2022/01/12 17:57:44 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

void	printTest(std::string const testname) {
	std::cout << WHT << "\n===== " << testname << " test =====\n";
}

void	printResult(bool passed) {
	if (passed == true)
		std::cout << "RESULT: Contents are " << GRN << "equal.\n" << WHT;
	else
		std::cout << "RESULT: Contents are " << RED << "NOT equal.\n" << WHT;  
}

// used to test lexicographical_compare
bool	mycomp(char c1, char c2) {
	return std::tolower(c1) < std::tolower(c2);
}
