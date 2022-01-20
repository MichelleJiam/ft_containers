/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 16:45:04 by mjiam         #+#    #+#                 */
/*   Updated: 2022/01/20 21:11:00 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

namespace std {
    inline std::string get_name() { return "std"; }
}

namespace ft {
    inline std::string get_name() { return "ft"; }
}

int main() {
    // pair containing (passed_count, test_count)
    IMPL::pair<int,int>   passed_tests(0,0);

    std::cout << "version: " << IMPL::get_name() << std::endl;
    test_utils(passed_tests);
    // test_vector(passed_tests);
    printPassing(passed_tests);
    return 0;
}
