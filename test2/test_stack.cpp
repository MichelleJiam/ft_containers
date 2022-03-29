/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_stack.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/03 20:21:37 by mjiam         #+#    #+#                 */
/*   Updated: 2022/03/29 22:02:43 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"
#include "../containers/stack.hpp"
#include "../containers/vector.hpp"

typedef IMPL::stack< int, IMPL::vector<int> >	t_istack;

template <typename T>
void    printStack(T& stack, std::string const cntr_name,
					std::string const test_case) {
	if (!test_case.empty())
		printTestCase(test_case);
	if (!cntr_name.empty())
		std::cout << "[ " << cntr_name << " ]\n";
	std::cout << "empty: " << std::boolalpha << stack.empty() << std::endl;
	std::cout << "size: " << stack.size() << std::endl;
	if (stack.empty() == false)
		std::cout << "top: " << stack.top() << std::endl;
	std::cout << std::endl;
}

template <typename T>
void    test_stack_pop(T& stack) {
	// printTest("pop");
	
	// t_istack    stack;

	// for (int i = 1; i <= 10; i++)
	// 	stack.push(i);
	stack.pop();
	printStack(stack, "stack", "pop()");
}

template <typename T>
void    test_stack_push(T& stack) {
	// printTest("push");
	
	// t_istack    stack;

	for (int i = 1; i <= 6; i++)
		stack.push(i);
	printStack(stack, "stack", "push([1-5])");
}

template <typename T>
void    test_stack_constructors(T& stack) {
	// printTest("default/copy constructors");

	printStack(stack, "empty stack", "default constructor with no argument");

	IMPL::vector<int>	vec(5, 42);
	t_istack			stack2(vec);
	printStack(stack2, "copy stack 1", "copy constructor with vector");
	printVector(vec, "source vector");

	t_istack			stack3(stack2);
	printStack(stack2, "copy stack 2", "copy constructor with another stack object");

	stack = stack3;
	printStack(stack, "formerly-empty stack", "empty stack = copy stack 2");
}

void test_stack() {
#ifndef SIMPLE
	printHeader("testing stack");
#endif

	t_istack	base_stack;

	// test_stack_constructors();
	// benchmarkFunction_multirun(test_stack_constructors<t_istack>, base_stack,
	// 	base_stack, "default/copy constructors");
	// // test_stack_push(base_stack);
	// benchmarkFunction_multirun(test_stack_push<t_istack>, base_stack, base_stack, "push");
	// // test_stack_pop();
	// benchmarkFunction_multirun(test_stack_pop<t_istack>, base_stack, base_stack, "pop");
}
