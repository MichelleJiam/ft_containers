/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 16:45:04 by mjiam         #+#    #+#                 */
/*   Updated: 2022/01/20 21:46:11 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

namespace std {
    inline std::string get_name() { return "std"; }

    // std::ofstream get_file() {
    //     std::ofstream outfile;
    //     outfile.open("std_output.txt");
    //     return outfile;
    // }
    // inline void close_file() { outfile.close(); }
}

namespace ft {
    inline std::string get_name() { return "ft"; }
    // std::ofstream get_file() {
    //     std::ofstream outfile;
    //     outfile.open("ft_output.txt");
    //     return outfile;
    // }
    // inline void close_file() { outfile.close(); }
}

int main() {
    // pair containing (passed_count, test_count)
    IMPL::pair<int,int>   passed_tests(0,0);

    // std::cout << "version: " << IMPL::get_name() << std::endl;

    std::ofstream outfile;
    std::string file_name = IMPL::get_name() + "_output.txt";
    outfile.open(file_name);

    test_utils(passed_tests, outfile);
    // test_vector(passed_tests);
    // printPassing(passed_tests);
    
    outfile.close();
    return 0;
}
