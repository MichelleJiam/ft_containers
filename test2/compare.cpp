/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   compare.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 18:52:21 by mjiam         #+#    #+#                 */
/*   Updated: 2022/03/29 21:19:33 by mjiam         ########   odam.nl         */
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

	sscanf(ft_line.substr(ft_line.find(": ") + 2).c_str(), "%f", &ft_time);
	sscanf(std_line.substr(std_line.find(": ") + 2).c_str(), "%f", &std_time);

	float	time_diff = ft_time / std_time;
	std::cout << "ft version is ";
	if (time_diff > 1.0)
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

	while (std_file && ft_file
			&& std::getline(std_file, std_line)
			&& std::getline(ft_file, ft_line)) {
		if (std_line.find("TESTING") != std::string::npos) {
			test_name = std_line.substr(std_line.find(": ") + 2);
			tests++;
			new_test = 1;
			std::cout << "\nTesting: " << GRN << test_name << WHT << std::endl;
		}
		else if (std_line.find("Duration of operation") != std::string::npos)
			continue;
		else if (std_line.find("Duration of 1000 operations") != std::string::npos)
			compareTimes(std_line, ft_line);
		else if (std_line.compare(ft_line) != 0) {
			if (new_test) {
				std::cout << RED << "\nFailed test: " << WHT << test_name << std::endl;
				failed++;
			}
			std::cout << "std container:\t" << std_line << std::endl;
			std::cout << "ft container:\t" << ft_line << std::endl;
			status = 1;
			new_test = 0;
		}
	}
	printPassing(tests - failed, tests);
	return status;
}
