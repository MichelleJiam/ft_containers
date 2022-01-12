/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tester.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/12 17:46:50 by mjiam         #+#    #+#                 */
/*   Updated: 2022/01/12 17:57:54 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_HPP
#define TESTER_HPP

#include <iostream>
#include <cctype>	// tolower

# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"

template <class T>
bool	isNotEqual(const T& lhs, const T& rhs) {
    return (lhs != rhs);
}

void	printTest(std::string const testname);
void	printResult(bool passed);
bool	mycomp(char c1, char c2);

#endif
