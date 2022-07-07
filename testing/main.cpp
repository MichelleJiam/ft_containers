/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 16:45:04 by mjiam         #+#    #+#                 */
/*   Updated: 2022/07/07 17:43:50 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

// Times a single execution of a function on the container
// that's been passed as reference.
// Accepts as param a `testFunction` that executes a container method on a
// container of size 10. See `benchmarkFunction_stress` for larger size test.
// Also prints the test name at the beginning.
void	benchmarkFunction(void (*testFunction)(size_t size),
							std::string const& test_name) {
	printTest(test_name);
	
	clock_t start = clock();
	testFunction(10);
	clock_t	end = clock();
	std::cout << "\nDuration of single operation:\t"
		<< std::fixed << std::setprecision(4)
		<< ((end - start) / (double)CLOCKS_PER_SEC) * 1000 << " milliseconds."
		<< std::endl;
	std::cout.unsetf(std::ios::fixed);	// restores cout to general format
}

// Runs single-run benchmarking, then runs stress test using a container
// of INT_MAX / 2000 size to more visibly demonstrate slowdown
// that comes with large sizes.
// Exits after only single-run benchmarking if QUICK macro has been passed during
// compilation (by running `make quick`), if user desires to only compare outputs
// and skip the potentially slow stress test.
// Accepts as param a `testFunction` that executes a container method on a
// container of `size` size (in this case, STRESS_SIZE which is defined in
// tester.hpp as INT_MAX / 2000).
void	benchmarkFunction_stress(void (*testFunction)(size_t size),
								std::string const& test_name) {
	benchmarkFunction(testFunction, test_name);
#ifdef QUICK
	return ;
#endif
	
	// saving cout buffer for restoring later
	std::streambuf	*orig_buf = std::cout.rdbuf();
	// disconnecting cout buffer to silence output
	std::cout.rdbuf(NULL);
	
	clock_t start = clock();
	testFunction(STRESS_SIZE);
	clock_t	end = clock();

	// restoring cout buffer
	std::cout.rdbuf(orig_buf);
	
	std::cout << "\nDuration of stress operation:\t"
		<< std::fixed << std::setprecision(4)
		<< ((end - start) / (double)CLOCKS_PER_SEC) * 1000 << " milliseconds."
		<< std::endl;
	std::cout.unsetf(std::ios::fixed);	// restores cout to general format
}

int main() {
	test_utils();
	test_vector();
	test_stack();
	test_map();
	test_set();
	
	// system("leaks ft_bin");
	return 0;
}
