/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   type_traits.hpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 21:47:38 by mjiam         #+#    #+#                 */
/*   Updated: 2022/01/20 16:13:07 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

namespace ft {
// Primary template for enable_if
// Defines a member typedef `type` if boolean constant `B` is true.
template <bool B, typename T = void>
struct  enable_if
{};

// Partial specialization for true
template <class T>
struct  enable_if<true, T> {
    typedef T   type;
};

// `is_integral` inherits the following from `integral_constant`:
//  - member constant `value`,
//  - member functions operator bool & operator(),
//  - member types `value_type` and `type`.
typedef std::integral_constant<bool, true> true_type;
typedef std::integral_constant<bool, false> false_type;

// C++11
// Checks whether T is an integral type.
// Provides member constant `value` which is equal to true if `T` is
// an integral type, or a cv-qualified form of one of those types, 
// otherwise value is equal to false.
// Integral types:  bool, char, unsigned char, signed char, wchar_t, short, 
//                  unsigned short, int, unsigned int, long, and unsigned long.
//  In addition, with compilers that provide them, an integral type can be 
//  one of long long, unsigned long long, __int64, and unsigned __int64.
template <class T>
struct  is_integral : public ft::false_type
{};

template <>
struct  is_integral<bool> : public ft::true_type
{};

template <>
struct  is_integral<char> : public ft::true_type
{};

template <>
struct  is_integral<unsigned char> : public ft::true_type
{};

template <>
struct  is_integral<wchar_t> : public ft::true_type
{};

template <>
struct  is_integral<short> : public ft::true_type
{};

template <>
struct  is_integral<unsigned short> : public ft::true_type
{};

template <>
struct  is_integral<int> : public ft::true_type
{};

template <>
struct  is_integral<unsigned int> : public ft::true_type
{};

template <>
struct  is_integral<long> : public ft::true_type
{};

template <>
struct  is_integral<unsigned long> : public ft::true_type
{};

template <>
struct  is_integral<long long> : public ft::true_type
{};

template <>
struct  is_integral<unsigned long long> : public ft::true_type
{};

} // namespace ft

#endif
