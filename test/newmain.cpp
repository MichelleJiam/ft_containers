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

    for (int i = 1; i <= 10; i++){
        ftvec.push_back(i);
        stdvec.push_back(i);
    }
    std::cout << "size of ftvec: " << ftvec.size() << std::endl;
    printVector(ftvec, stdvec);
    return 0;
}