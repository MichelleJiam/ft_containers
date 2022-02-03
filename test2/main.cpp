/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 16:45:04 by mjiam         #+#    #+#                 */
/*   Updated: 2022/02/03 21:20:01 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

namespace std {
    inline std::string get_name() { return "std"; }
} // TODO: remove

namespace ft {
    inline std::string get_name() { return "ft"; }
} // TODO: remove

int main() {

    // std::cout << "version: " << IMPL::get_name() << std::endl;

    test_utils();
    test_vector();
    test_stack();
    
    return 0;
}
