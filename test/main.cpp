/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 16:45:04 by mjiam         #+#    #+#                 */
/*   Updated: 2022/01/20 21:13:56 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

int main() {
    // pair containing (passed_count, test_count)
    ft::pair<int,int>   passed_tests(0,0);

    test_utils(passed_tests);
    test_vector(passed_tests);
    printPassing(passed_tests);
    return 0;
}
