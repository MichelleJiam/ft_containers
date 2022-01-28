/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 16:45:04 by mjiam         #+#    #+#                 */
/*   Updated: 2022/01/28 13:28:32 by mjiam         ########   odam.nl         */
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

    // std::cout << "version: " << IMPL::get_name() << std::endl;

    test_utils();
    test_vector();
    // printPassing(passed_tests);
    
    return 0;
}
