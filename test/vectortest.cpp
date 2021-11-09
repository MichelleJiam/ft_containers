/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vectortest.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/26 15:15:28 by mjiam         #+#    #+#                 */
/*   Updated: 2021/11/09 21:26:34 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iostream>
#include <exception>
#include <iterator>
#include <cassert>

#define size_type std::size_t

// namespace   ft {

// template < class T, class Alloc = std::allocator<T> >
// class vector : public std::vector<T, Allocator> {
// 	public:
//     iterator	erase (iterator position) {
//         return this.erase(position, position + 1);
//     }

// 		// Erases a range of elements [first,last].
// 		iterator	erase (iterator first, iterator last) {
//             size_type	n_to_erase = std::distance(first, last);
//             size_type	start = std::distance(std::vector::begin(), first);
//             size_type	end;
            
//             if (n_to_erase == 0)
//                 return last;
//             for (end = 0; end < n_to_erase; end++)
//                 _alloc.destroy(_array[start + end]);
//             for (size_type j = 0; end + j < _size; j++) {
//                 _alloc.construct(_array[start + j], _array[end + j]);
//                 _alloc.destroy(_array[end + j]);
//             }
//             this->_size -= n_to_erase;
//             if (end >= _size)
//                 return std::vector::end();
//             else
//                 return (std::vector::begin() + start + end);
//         }

// 	private:
// 		allocator_type	_alloc;
// 		size_type		_size;
// 		size_type		_capacity;
// 		pointer			_array;
// };

// } // ft namespace

using namespace std;

template <class T, class A>
void    vector_print(vector<T,A> vec, char const* name)
{
    cout << name << " contains " << vec.size() << " elements:\t";
    for (unsigned i = 0; i < vec.size(); ++i)
        cout << ' ' << vec[i];
    cout << '\n';
}

template <class T, class A>
typename vector<T,A>::iterator	erase(vector<T,A> &vec,
    typename vector<T,A>::iterator first, typename vector<T,A>::iterator last) {
    size_type	n_to_erase = std::distance(first, last);
    size_type	start = std::distance(vec.begin(), first);
    size_type	end;
    
    if (n_to_erase == 0)
        return last;
    if (first == vec.end() || first > last)
        return first;
    // std::cout << "start is at " << start << endl;
    for (end = start; end < start + n_to_erase; end++)
        vec.get_allocator().destroy(&vec.data()[end]);
    // std::cout << "end is at " << end << endl;
    // std::cout << "size after destroying elements: " << vec.size() << endl;
    for (size_type j = 0; end + j < vec.size(); j++) {
        vec.get_allocator().construct(&vec.data()[start + j], vec.data()[end + j]);
        vec.get_allocator().destroy(&vec.data()[end + j]);
    }
    size_type new_size = vec.size() - n_to_erase;
    vec.resize(new_size);
    // cout << "new size: " << new_size << endl;
    if (end >= vec.size())
        return vec.end();
    else
        return (last - n_to_erase);
}

template <class T, class A>
typename vector<T,A>::iterator	erase1 (vector<T,A> &vec,
    typename vector<T,A>::iterator position) {
    // assert(position != vec.end());
    return erase(vec, position, position + 1);
}

int main() {
    vector<int>     myvector;
    vector<int>     stdvector;
    // std::cout << vec.max_size() << std::endl; // testing what max_size of vector is

	// set some values (from 1 to 10)
    for (int i = 1; i <= 10; i++){
        myvector.push_back(i);
        stdvector.push_back(i);
    }
    vector_print(myvector, "myvector");
    vector_print(stdvector, "stdvector");

    // erase the 6th element
    vector<int>::iterator myit;
    vector<int>::iterator stdit;
    myit = erase(myvector, myvector.begin() + 5, myvector.begin() + 6);
    stdit = stdvector.erase(stdvector.begin() + 5, stdvector.begin() + 6);
    cout << "- erasing 6th element -\n";
    vector_print(myvector, "myvector");
    vector_print(stdvector, "stdvector");
    cout << "myiterator is at " << *myit << endl;
    cout << "stditerator is at " << *stdit << endl;

    // erase the first 3 elements:
    myit = erase(myvector, myvector.begin(), myvector.begin() + 3);
    stdit = stdvector.erase(stdvector.begin(), stdvector.begin() + 3);
    cout << "- erasing first 3 elements -\n";
    vector_print(myvector, "myvector");
    vector_print(stdvector, "stdvector");
    cout << "myiterator is at " << *myit << endl;
    cout << "stditerator is at " << *stdit << endl;

    // erase last 2 elements:
    myit = erase(myvector, myvector.end() - 2, myvector.end());
    stdit = stdvector.erase(stdvector.end() - 2, stdvector.end());
    cout << "- erasing last 2 elements -\n";
    vector_print(myvector, "myvector");
    vector_print(stdvector, "stdvector");
    cout << "myiterator is at " << *myit << endl;
    cout << "stditerator is at " << *stdit << endl;

    cout << "- erasing end() -\n";
    try {
        myit = erase1(myvector, myvector.end()); // segfaults because end is not valid dereferencable iterator
        // stdit = stdvector.erase(stdvector.end());
    }
    catch (const std::exception& e) {
        std::cerr << e.what();
    }
    vector_print(myvector, "myvector");
    // vector_print(stdvector, "stdvector");
    cout << "myiterator is at " << *myit << endl;
    // cout << "stditerator is at " << *stdit << endl;

    cout << "- testing erase invalid range -\n";
    myit = erase(myvector, myvector.end() - 1, myvector.end() - 2); // no-op due to invalid range, lib erase hangs
   vector_print(myvector, "myvector");
    cout << "myiterator is at " << *myit << endl;
    // stdit = stdvector.erase(stdvector.end() - 1, stdvector.end() - 2); // no-op due to invalid range, lib erase hangs
    // vector_print(stdvector, "stdvector");
    // cout << "stditerator is at " << *stdit << endl;

    // cout << "distance returns " << std::distance(stdvector.end(), stdvector.end() + 1) << endl;
    // cout << "distance returns " << std::distance(stdvector.end() - 2, stdvector.end() - 1) << endl;
    
    // stdvector.assign(0, 42); // zeroes out container
    // cout << "- assign with count 0 -\n";
    // vector_print(stdvector, "stdvector");

    cout << "- inserting same value at begin as end to test == comparison -\n";
    stdvector.insert(stdvector.end()-4, 9);
    vector_print(stdvector, "stdvector");
    cout << "begin() returns " << *(stdvector.begin()) << endl;
    if (stdvector.begin() == stdvector.end())
        cout << "begin is same as end\n";
    else
        cout << "begin NOT same as end\n";
    
    cout << "- testing iterator arithmetic -\n";
    vector<int>::iterator it = stdvector.begin();
    vector<int>::iterator it2 = stdvector.end();
    vector<int>::iterator it3 = stdvector.begin() + 2;
    vector<int>::difference_type dist = it2 - it;
    vector<int>::difference_type dist2 = it3 - it;
    cout << "end() - begin() = " << dist << endl;
    cout << "begin+2(" << *it3 << ") - begin(" << *it << ") = " << dist2 << endl;
    
    return 0;
}