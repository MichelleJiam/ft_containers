/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   compare.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 18:52:21 by mjiam         #+#    #+#                 */
/*   Updated: 2022/05/26 17:24:27 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <cstdio> // sscanf
#include <cstring> // strcmp
#include <algorithm> // equal
#include <iterator> // istreambuf_iterator

#include "tester.hpp"

void    compareTimes(std::string std_line, std::string ft_line) {
	float	ft_time, std_time;

	sscanf(ft_line.substr(ft_line.find(":\t") + 2).c_str(), "%f", &ft_time);
	sscanf(std_line.substr(std_line.find(":\t") + 2).c_str(), "%f", &std_time);

	float	time_diff = ft_time / std_time;
	std::cout << "ft version is ";
	if (time_diff > 20.0)
		std::cout << RED << "more than 20 times slower.\n" << WHT;
	else if (time_diff > 1.0)
		std::cout << time_diff << " slower than std version.\n";
	else if (time_diff < 1.0)
		std::cout  << (std_time / ft_time) << " faster than std version.\n";
	else
		std::cout << "equally as fast as std version.\n";
}

int main() {
	std::ifstream   std_file, ft_file;
	// binary mode makes sure newlines aren't translated
	std_file.open("./std_output.txt", std::ifstream::binary);
	ft_file.open("./ft_output.txt", std::ifstream::binary);
	
	if (std_file.fail() || ft_file.fail()) {
		std::cerr << "Failed to open files\n";
		return 1;
	}

	printHeader("comparing std and ft containers");

	int tests = 0, failed = 0;
	int status = 0;
	int new_test = 0;
	std::string std_line, ft_line;
	std::string test_name;

	if (std::getline(std_file, std_line) && std::getline(ft_file, ft_line)) // print container type header
		printHeader(ft_line);

	while (std_file && ft_file
			&& std::getline(std_file, std_line)
			&& std::getline(ft_file, ft_line)) {
		if (std_line.find("TESTING") != std::string::npos) { // printing test cases
			test_name = std_line.substr(std_line.find(": ") + 2);
			tests++;
			new_test = 1;
			std::cout << "\nTesting: " << GRN << test_name << WHT << std::endl;
		}
		else if (std_line.compare(ft_line) != 0
			&& std_line.find("Duration") == std::string::npos) { // if different output is found
			if (new_test) {
				std::cout << RED << "TEST FAILED" << WHT << " | Diff: " << std::endl;
				failed++;
			}
			std::cout << "std container:\t" << std_line << std::endl;
			std::cout << "ft container:\t" << ft_line << std::endl;
			status = 1;
			new_test = 0;
		}
		else if (std_line.find("single operation") != std::string::npos) // don't print single op timing
			continue;
		else if (std_line.find("stress operation") != std::string::npos // print only stress op comparison
					&& new_test == 1) // doesn't print times if test fails
			compareTimes(std_line, ft_line);
	}
	if (std_file && ft_file
		&& (std::getline(std_file, std_line) || std::getline(ft_file, ft_line))) {
		std::cout << RED << "Difference found at end of file:" << WHT << std::endl;
		std::cout << "std container:\t" << std_line << std::endl;
		std::cout << "ft container:\t" << ft_line << std::endl;
	}
	printPassing(tests - failed, tests);
	return status;
}
