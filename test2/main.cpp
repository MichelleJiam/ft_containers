/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 16:45:04 by mjiam         #+#    #+#                 */
/*   Updated: 2022/02/11 18:09:57 by mjiam         ########   odam.nl         */
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
    
    ft::rb_tree<std::string, ft::pair<std::string,int> > RB;
    RB.debug_empty();

    ft::pair<std::string,int> key1("one", 42);
    RB.insert(key1);
    RB.debug_single();
    
    system("leaks ft_bin");
    return 0;
}
