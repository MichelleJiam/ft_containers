/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   newmain.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/30 18:13:43 by mjiam         #+#    #+#                 */
/*   Updated: 2022/01/11 17:55:59 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"

template <class T>
void    printVector(std::string const testname, ft::vector<T> &ftvec, std::vector<T> &stdvec)
{
	int error = 0;

	std::cout << "\n===== " << testname << " test =====\n";
	std::cout << "- STL vector -\n";
	std::cout << "capacity: " << stdvec.capacity() << std::endl;
	std::cout << "size:     " << stdvec.size() << std::endl;
	std::cout << "contents: [";
	for (unsigned i = 0; i < stdvec.size(); i++)
		std::cout << ' ' << stdvec[i];
	std::cout << " ]\n";
	std::cout << "\n- FT vector -\n";
	std::cout << "capacity: " << ftvec.capacity() << std::endl;
	std::cout << "size:     " << ftvec.size() << std::endl;
	std::cout << "contents: [";
	for (unsigned i = 0; i < ftvec.size(); i++) {
		std::cout << ' ' << ftvec[i];
		ftvec[i] == stdvec[i] ? error : error++;
	}
	std::cout << " ]\n";
	if (stdvec.size() == ftvec.size()
		&& stdvec.capacity() == ftvec.capacity()
		&& error == 0)
		std::cout << "RESULT: Vectors are " << GRN << "equal.\n" << WHT;
	else
		std::cout << "RESULT: Vectors are " << RED << "NOT equal.\n" << WHT;   
}

int main() {
	ft::vector<int> ftvec;
	std::vector<int> stdvec;

	for (int i = 1; i <= 10; i++){
		ftvec.push_back(i);
		stdvec.push_back(i);
	}
	printVector("push_back", ftvec, stdvec);
	// std::cout << "is ftvec empty: " << (ftvec.empty() ? "true" : "false") << std::endl;

	// fill constructor test
	ft::vector<int>     ft_fill_vec(4, 42);
	std::vector<int>    std_fill_vec(4, 42);
	printVector("fill constructor", ft_fill_vec, std_fill_vec);

	// reserve test
	size_t   ft_oldcap = ft_fill_vec.capacity(), std_oldcap = std_fill_vec.capacity();
	ft_fill_vec.reserve(10);
	std_fill_vec.reserve(10);
	printVector("reserve", ft_fill_vec, std_fill_vec);
	std::cout << "ft fill vec capacity was " << ft_oldcap << ", is now " << ft_fill_vec.capacity() << ".\n";
	std::cout << "std fill vec capacity was " << std_oldcap << ", is now "  << std_fill_vec.capacity() << ".\n";

	// insert test
	ft::vector<int>::iterator ft_it;
	std::vector<int>::iterator std_it;
	ft_it = ft_fill_vec.end();
	std_it = std_fill_vec.end();
	ft_fill_vec.insert(ft_it - 1, 2, 13);
	std_fill_vec.insert(std_it - 1, 2, 13);
	printVector("insert", ft_fill_vec, std_fill_vec);
	ft_it = ft_fill_vec.begin();
	std_it = std_fill_vec.begin();
	ft_fill_vec.insert(ft_it + 2, 2, 0);
	std_fill_vec.insert(std_it + 2, 2, 0);
	ft_fill_vec.insert(ft_it + 1, 2, 10);
	std_fill_vec.insert(std_it + 1, 2, 10);
	printVector("insert", ft_fill_vec, std_fill_vec);

	// resize test
	ft_fill_vec.resize(8, 7);
	std_fill_vec.resize(8, 7);
	printVector("resize", ft_fill_vec, std_fill_vec);

	// erase test
	ft_fill_vec.erase(ft_fill_vec.end() - 2);
	std_fill_vec.erase(std_fill_vec.end() - 2);
	printVector("erase", ft_fill_vec, std_fill_vec);
	ft_fill_vec.erase(ft_fill_vec.end() - 3, ft_fill_vec.end() - 1);
	std_fill_vec.erase(std_fill_vec.end() - 3, std_fill_vec.end() - 1);
	// ft_fill_vec.erase(ft_fill_vec.begin() + 2, ft_fill_vec.begin() + 4);
	// std_fill_vec.erase(std_fill_vec.begin() + 2, std_fill_vec.begin() + 4);
	printVector("erase range", ft_fill_vec, std_fill_vec);

	// ft::vector<int>     ft_range_vec(ft_fill_vec.begin(), ft_fill_vec.end());
	// std::vector<int>    std_range_vec(std_fill_vec.begin(), std_fill_vec.end());
	// printVector(ft_range_vec, std_range_vec);
	return 0;
}