/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function.hpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 17:43:26 by mjiam         #+#    #+#                 */
/*   Updated: 2022/04/19 17:55:35 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_HPP
#define FUNCTION_HPP

template <class Arg, class Result>
struct UnaryFunction {
	typedef Arg argument_type;
	typedef Result result_type;
};

// Used by set to pass as KeyOfValue template param to rb_tree
template <class T>
struct Identity : public UnaryFunction<T,T> {
	T& operator()(T& x) const {
		return x;
	}

	T const& operator()(T const& x) const {
		return x;
	}
};

// Used by map to pass as KeyOfValue template param to rb_tree
template <class Pair>
struct Select1st : public UnaryFunction<Pair, typename Pair::first_type> {
	typename Pair::first_type& operator()(Pair& x) const {
		return x.first;
	}

	typename Pair::first_type const& operator()(Pair const& x) const {
		return x.first;
	}
};

#endif