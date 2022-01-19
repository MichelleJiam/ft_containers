/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   type_traits.hpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 21:47:38 by mjiam         #+#    #+#                 */
/*   Updated: 2022/01/19 17:24:12 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

namespace ft {
// Primary template for enable_if
template <bool B, typename T = void>
struct  enable_if
{};

// Partial specialization
// Defines a member typedef `type` if boolean constant `B` is true.
template <typename T>
struct  enable_if<true, T> {
    typedef T   type;
};



} // namespace ft

#endif
