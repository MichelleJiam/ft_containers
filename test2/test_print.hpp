/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_print.hpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/31 17:00:20 by mjiam         #+#    #+#                 */
/*   Updated: 2022/03/31 17:04:41 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_PRINT_HPP
#define TEST_PRINT_HPP

#include "tester.hpp"

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

// Prints vector capacity, size, and contents,
// and optionally test case and container name.
// See printTestCase for test_case argument example.
template <typename T>
void    printVector(T& base_vec, std::string const cntr_name = std::string(),
						std::string const test_case = std::string()) {
	if (!test_case.empty())
		printTestCase(test_case);
	if (!cntr_name.empty())
		std::cout << "[ " << cntr_name << " ]\n";
	std::cout << "capacity: " << base_vec.capacity() << std::endl;
	std::cout << "size:     " << base_vec.size() << std::endl;
	std::cout << "contents: [";
	for (unsigned i = 0; i < base_vec.size(); i++)
		std::cout << ' ' << base_vec[i];
	std::cout << " ]\n\n";
}

#endif
