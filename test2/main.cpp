/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 16:45:04 by mjiam         #+#    #+#                 */
/*   Updated: 2022/01/21 19:14:21 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

// #ifndef SAVE
// #define out std::cout
// #endif

namespace std {
    inline std::string get_name() { return "std"; }

    // std::ofstream get_file() {
    //     std::ofstream out;
    //     out.open("std_output.txt");
    //     return out;
    // }
    // inline void close_file() { out.close(); }
}

namespace ft {
    inline std::string get_name() { return "ft"; }
    // std::ofstream get_file() {
    //     std::ofstream out;
    //     out.open("ft_output.txt");
    //     return out;
    // }
    // inline void close_file() { out.close(); }
}

int main() {
    // pair containing (passed_count, test_count)
    IMPL::pair<int,int>   passed_tests(0,0);

    // std::cout << "version: " << IMPL::get_name() << std::endl;

// #if SAVE
    std::ofstream out;
    std::string file_name = IMPL::get_name() + "_output.txt";
    out.open(file_name);
    // test_utils(passed_tests, out);
    test_vector<std::ofstream>(passed_tests, out);
    out.close();
// #endif

    // test_utils(passed_tests, out);
    // test_vector(passed_tests, out);
    // printPassing(passed_tests);
    
    
    return 0;
}
