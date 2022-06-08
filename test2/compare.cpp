/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   compare.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 18:52:21 by mjiam         #+#    #+#                 */
/*   Updated: 2022/06/08 19:08:35 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <sstream> // stringstream
#include <cstdio> // sscanf
#include <cstring> // strcmp
#include <algorithm> // equal
#include <iterator> // istreambuf_iterator

#include "tester.hpp"

#define NOTFOUND std::string::npos

void	resetTimesStream(std::stringstream& times) {
	times.str(std::string());
	times.clear();
}

void    compareTimes(std::stringstream& times,
						std::string std_line, std::string ft_line) {
	// clears single op timing if stress op is also done
	if (times.tellp() != std::streampos(0))
		resetTimesStream(times);

	float	ft_time, std_time;

	sscanf(ft_line.substr(ft_line.find(":\t") + 2).c_str(), "%f", &ft_time);
	sscanf(std_line.substr(std_line.find(":\t") + 2).c_str(), "%f", &std_time);

	float	time_diff = ft_time / std_time;
	
	times << "ft version is ";
	if (time_diff > 20.0)
		times << RED << "more than 20 times slower.\n" << WHT;
	else if (time_diff > 1.0)
		times << time_diff << " slower than std version.\n";
	else if (time_diff < 1.0)
		times << (std_time / ft_time) << " faster than std version.\n";
	else
		times << "equally as fast as std version.\n";
}

int	printFailedTest(std::string std_line, std::string ft_line,
					int new_test, int &failed, int line) {
	if (std_line.find("max_size") != NOTFOUND) { // if difference is in max_size
		std::cout << "Diff in max_size on line "
			<< CYN << line << WHT << " but allowed\n";
		std::cout << YEL << "\t[STD]\t" << std_line << std::endl;
		std::cout << "\t[FT]\t" << ft_line << WHT << std::endl;
		return 1;
	}
	else {
		if (new_test) {
			std::cout << RED << "-- TEST FAILED --" << WHT << std::endl;
			failed++;
		}
		std::cout << "Diff on line " << CYN << line << WHT << "\n";
		std::cout << GRN << "\t[STD]\t" << std_line << std::endl;
		std::cout << RED << "\t[FT]\t" << ft_line << WHT << std::endl;
		return 0;
	}
}

int	printTestCase(std::string std_line, int &tests) {
	std::string test_name = std_line.substr(std_line.find(": ") + 2);
	tests++;
	std::cout << "\nTesting: " << GRN << test_name << WHT << std::endl;
	return 1;
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
	int new_test = 0, line = 1;
	std::string std_line, ft_line;
	std::stringstream times;

 	// print container type header
	if (std::getline(std_file, std_line) && std::getline(ft_file, ft_line))
		printHeader(ft_line);
	while (std_file && ft_file && std::getline(std_file, std_line)
			&& std::getline(ft_file, ft_line)) {
		line++;
		// skip empty lines
		if (std_line.size() == 0 && ft_line.size() == 0)
			continue;
		// print buffered comparison times if filled and no stress duration to process
		else if (times.tellp() != std::streampos(0)
			&& std_line.find("Duration") == NOTFOUND) {
			std::cout << times.str() << std::flush;
			resetTimesStream(times);
		}
		// print test cases
		if (std_line.find("TESTING") != NOTFOUND)
			new_test = printTestCase(std_line, tests);
		// if different output is found
		else if (std_line.compare(ft_line) != 0
			&& std_line.find("Duration") == NOTFOUND)
			new_test = printFailedTest(std_line, ft_line, new_test, failed, line);
		// does duration comparison, unless test failed
		else if (std_line.find("Duration") != NOTFOUND && new_test != 0) 
			compareTimes(times, std_line, ft_line);
	}
	// prints buffered time comparison after EOF
	if (times.tellp() != std::streampos(0))
		std::cout << times.str() << std::flush;
	printPassing(tests - failed, tests);
	return (failed != 0); // return 1 if tests failed
}
