/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vectortest.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/26 15:15:28 by mjiam         #+#    #+#                 */
/*   Updated: 2021/11/16 21:34:19 by mjiam         ########   odam.nl         */
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
void	_range_copy(vector<T,A> &vec, typename vector<T,A>::iterator pos, typename vector<T,A>::iterator first,
					typename vector<T,A>::iterator last) {

    // cout << "_range_copy received: pos (" << *pos << "), first (" << *first << "), last (" << *last << ")\n";
    size_type   to_copy = last - first;
    // cout << "to_copy: " << to_copy << endl;
    try {
		for (size_type i = to_copy; i; i--){
            // cout << "constructing " <<*(first + i - 1) << " at place of " << *(pos + i - 1) << endl;
			vec.get_allocator().construct(&*(pos + i - 1), *(first + i - 1));
            // cout << "vec[" << i - 1 << "] is " << vec[i - 1] << endl;
            // vector_print(vec, "myvector in range_copy");
        }
	}
	catch (...) {
		for (size_type i = 0; i < to_copy; i++)
			vec.get_allocator().destroy(&*(pos + i));
		throw;
	}
    // vector_print(vec, "myvector after range");
}

//	Internal fn called by fill constructor and insert (fill version).
//	Inserts `count` elements with value `value` at `pos`.
template <class T, class A>
void	_fill_insert(vector<T,A> &vec, typename vector<T,A>::iterator pos, size_type count,
											T const& value) {
	size_type constructed = 0;
	
	try {
		for (; constructed < count; constructed++) {
			vec.get_allocator().construct(&*(pos + constructed), value);
		}
	}
	catch (...) {
		for (size_type i = 0; i < constructed; i++)
			vec.get_allocator().destroy(&*(pos + i));
		throw;
	}
}

template <class T, class A>
void	insert(vector<T,A> &vec, typename vector<T,A>::iterator pos,
                        size_type count, T const& value) {
	size_type	old_cap = vec.capacity();
    size_type   old_size = vec.size();

	try {
		vec.reserve(vec.size() + count);
        vec.resize(vec.size() + count);
        // cout << "capacity: " << vec.capacity() << " old_cap: " << old_cap << endl;
		if (pos < vec.end() - 1){
            // cout << "_range_copy required: pos (" << *pos << ") < end - 1 (" << *(vec.end() - 1) << ")\n";
			_range_copy(vec, pos + count, pos, vec.end());
            }
        // vector_print(vec, "myvector after range_copy");
		_fill_insert(vec, pos, count, value);
	}
	catch (...) {
		if (old_cap < vec.capacity())
			vec.get_allocator().deallocate(&*pos, vec.capacity() - old_cap);
        if (old_size < vec.size())
            vec.resize(old_size);
		throw;
	}
}

template <class T, class A>
void	insert(vector<T,A> &vec, typename vector<T,A>::iterator pos,
    typename vector<T,A>::iterator first, typename vector<T,A>::iterator last){
    // typename iterator_traits<I>::type* = NULL) {
	size_type	old_cap = vec.capacity();
    size_type   old_size = vec.size();
	size_type	count = last - first;

	try {
		vec.reserve(vec.size() + count);
        vec.resize(vec.size() + count);
		if (pos < vec.end() - 1)
			_range_copy(vec, pos + count, pos, vec.end());
		_range_copy(vec, pos, first, last);
	}
	catch (...) {
		if (old_cap < vec.capacity())
			vec.get_allocator().deallocate(&*pos, vec.capacity() - old_cap);
        if (old_size < vec.size())
            vec.resize(old_size);
		throw;
	}
}

template <class T, class A>
typename vector<T,A>::iterator	erase(vector<T,A> &vec,
    typename vector<T,A>::iterator first, typename vector<T,A>::iterator last) {
    // size_type	n_to_erase = std::distance(first, last);
    size_type	n_to_erase = last - first;
    size_type	start = first - vec.begin();
    size_type	end;
    
    if (n_to_erase < 1)
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

    // cout << "- erasing end() -\n";
    // try {
    //     myit = erase1(myvector, myvector.end()); // segfaults because end is not valid dereferencable iterator
    //     // stdit = stdvector.erase(stdvector.end());
    // }
    // catch (const std::exception& e) {
    //     std::cerr << e.what();
    // }
    // vector_print(myvector, "myvector");
    // // vector_print(stdvector, "stdvector");
    // cout << "myiterator is at " << *myit << endl;
    // cout << "stditerator is at " << *stdit << endl;

//     cout << "- testing erase invalid range -\n";
//     myit = erase(myvector, myvector.end() - 1, myvector.end() - 2); // no-op due to invalid range, lib erase hangs
//    vector_print(myvector, "myvector");
//     cout << "myiterator is at " << *myit << endl;
    // stdit = stdvector.erase(stdvector.end() - 1, stdvector.end() - 2); // hangs
    // vector_print(stdvector, "stdvector");
    // cout << "stditerator is at " << *stdit << endl;

    cout << "- testing erase empty range -\n";
    stdit = stdvector.erase(stdvector.end(), stdvector.end()); // no-op due to invalid range, lib erase hangs
    vector_print(stdvector, "stdvector");
    cout << "stditerator is at " << *stdit << endl;
    myit = erase(myvector, myvector.end(), myvector.end()); // no-op due to invalid range, lib erase hangs
   vector_print(myvector, "myvector");
    cout << "myiterator is at " << *myit << endl;

    // cout << "distance returns " << std::distance(stdvector.end(), stdvector.end() + 1) << endl;
    // cout << "distance returns " << std::distance(stdvector.end() - 2, stdvector.end() - 1) << endl;
    
    // stdvector.assign(0, 42); // zeroes out container
    // cout << "- assign with count 0 -\n";
    // vector_print(stdvector, "stdvector");

    cout << "- inserting same value at begin as end to test == comparison -\n";
    stdvector.insert(stdvector.end()-4, 1, 9);
    vector_print(stdvector, "stdvector");
    insert(myvector, myvector.end()-4, 1, 9);
    vector_print(myvector, "myvector");
    // cout << "begin() returns " << *(stdvector.begin()) << endl;

    cout << "- inserting range -\n";
    // int myarray[3] = { 42, 13, 100 }; // doesn't work until iterator traits implemented
    stdvector.insert(stdvector.end() - 2, myvector.begin(), myvector.end() - 3);
    vector_print(stdvector, "stdvector");
    insert(myvector, myvector.end() - 2, stdvector.begin(), stdvector.end() - 5);
    vector_print(myvector, "myvector");

    cout << "- testing _range_copy -\n";
    vector<int> copyvector;
    copyvector.reserve(myvector.size());
    copyvector.resize(myvector.size());
    _range_copy(copyvector, copyvector.begin(), myvector.begin(), myvector.end());
    vector_print(copyvector, "copyvector");
    
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