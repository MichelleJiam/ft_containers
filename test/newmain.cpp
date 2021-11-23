#include "vector.hpp"

template <class T>
void    printVector(ft::vector<T> ftvec, std::vector<T> stdvec)
{
    std::cout << "- STL vector -\n";
    std::cout << "Contains " << stdvec.size() << " elements:\t[";
    for (unsigned i = 0; i < stdvec.size(); ++i)
        std::cout << ' ' << stdvec[i];
    std::cout << "]\n";
    std::cout << "- FT vector -\n";
    std::cout << "Contains " << ftvec.size() << " elements:\t[";
    for (unsigned i = 0; i < ftvec.size(); ++i)
        std::cout << ' ' << ftvec[i];
    std::cout << "]\n";
}

int main() {
    ft::vector<int> ftvec;
    std::vector<int> stdvec;

    // for (int i = 1; i <= 10; i++){
    //     ftvec.push_back(i);
    //     stdvec.push_back(i);
    // }
    printVector(ftvec, stdvec);
    std::cout << "is ftvec empty: " << (ftvec.empty() ? "true" : "false") << std::endl;

    ft::vector<int>     ft_fill_vec(4, 42);
    std::vector<int>    std_fill_vec(4, 42);
    std::cout << "ft fill vec contains " << ft_fill_vec.size() << " elements.\n";
    std::cout << "std fill vec contains " << std_fill_vec.size() << " elements.\n";
    // printVector(ft_fill_vec, std_fill_vec);
    return 0;
}