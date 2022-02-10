/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 16:45:04 by mjiam         #+#    #+#                 */
/*   Updated: 2022/02/10 22:43:55 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

#include "../utils/rb_tree.hpp" // TODO: remove

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
    
    ft::rb_tree<int, ft::pair<int, int> > RB;
    RB.debug_empty();

    ft::pair<int,int> key1(1, 42);
    RB.insert(key1);
    RB.debug_single();
    
    system("leaks ft_bin");
    return 0;
}
