/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tester_helper.cpp                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 16:54:22 by mjiam         #+#    #+#                 */
/*   Updated: 2022/01/25 17:43:46 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

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