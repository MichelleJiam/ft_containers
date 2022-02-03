/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_stack.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/03 20:21:37 by mjiam         #+#    #+#                 */
/*   Updated: 2022/02/03 21:18:44 by mjiam         ########   odam.nl         */
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

void    test_stack_pop(void) {
	printTest("pop");
	
	t_istack    stack;

	for (int i = 1; i <= 10; i++)
		stack.push(i);
	stack.pop();
	printStack(stack, "stack", "pop()");
}

void    test_stack_push(void) {
	printTest("push");
	
	t_istack    stack;

	for (int i = 1; i <= 10; i++)
		stack.push(i);
	printStack(stack, "stack", "push([1-10])");
}

void    test_stack_constructors(void) {
	printTest("default/copy constructors");
	
	t_istack    		stack1;
	printStack(stack1, "empty stack", "default constructor with no argument");

	IMPL::vector<int>	vec(5, 42);
	t_istack			stack2(vec);
	printStack(stack2, "copy stack 1", "copy constructor with vector");
	printVector(vec, "source vector");

	t_istack			stack3(stack2);
	printStack(stack2, "copy stack 2", "copy constructor with another stack object");

	stack1 = stack3;
	printStack(stack1, "formerly-empty stack", "empty stack = copy stack 2");
}

void test_stack() {
#ifndef SIMPLE
	printHeader("testing stack");
#endif

	test_stack_constructors();
	test_stack_push();
	test_stack_pop();
}
