/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 16:45:04 by mjiam         #+#    #+#                 */
/*   Updated: 2022/01/25 17:31:58 by mjiam         ########   odam.nl         */
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

// #include "vector.hpp"
// template <class T, typename S>
// void    printVector(S &out, IMPL::vector<T> &base_vec, int &test_count,
// 					std::string const &test_name = std::string())
// {
// 	// if (!test_name.empty())
// 	// 	printTest(out, test_name, test_count);
//     (void)test_count;
//     out << test_name << std::endl;
// 	out << "\n- Vector -\n";
// 	out << "capacity: " << base_vec.capacity() << std::endl;
// 	out << "size:     " << base_vec.size() << std::endl;
// 	out << "contents: [";
// 	for (unsigned i = 0; i < base_vec.size(); i++)
// 		out << ' ' << base_vec[i];
// 	out << " ]\n";
// }

int main() {
    // pair containing (passed_count, test_count)
    IMPL::pair<int,int>   passed_tests(0,0);

    // std::cout << "version: " << IMPL::get_name() << std::endl;

#if SAVE
    std::ofstream out;
    std::string file_name = IMPL::get_name() + "_output.txt";
    out.open(file_name);
    // test_utils(passed_tests, out);
    test_vector<std::ofstream>(passed_tests, out);
#else
    // test_utils(passed_tests, out);
    test_vector<std::ostream>(passed_tests, std::cout);
    // printPassing(passed_tests);
#endif

#if SAVE
    out.close();
#endif
    
    return 0;
}
