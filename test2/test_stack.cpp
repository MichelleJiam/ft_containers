/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_stack.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/03 20:21:37 by mjiam         #+#    #+#                 */
/*   Updated: 2022/04/07 17:40:48 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

#define T1 int
typedef IMPL::stack< T1, IMPL::vector<T1> >	t_stack;

// Prints if stack is empty, stack size, stack top,
// and optionally test-case and container name.
// See printTestCase for test_case argument example.
template <typename T>
void    printStack(T& stack, std::string const cntr_name = std::string(),
					std::string const test_case = std::string()) {
	if (!test_case.empty())
		printTestCase(test_case);
	if (!cntr_name.empty())
		std::cout << "[ " << cntr_name << " ]\n";
	std::cout << "empty: " << std::boolalpha << stack.empty() << std::endl;
	std::cout << "size: " << stack.size() << std::endl;
	if (!stack.empty())
		std::cout << "top: " << stack.top() << std::endl;
	std::cout << std::endl;
}

template <typename T>
void    test_stack_constructors(size_t size) {
	T	empty_stack;
	printStack(empty_stack, "empty stack", "default constructor with no argument");

	IMPL::vector<T1>	stack(size, 42);
	T					copy_stack(stack);

	printStack(copy_stack, "copy stack 1", "copy constructor with vector");
	printVector<IMPL::vector<T1> >(stack, (size < 100), "source vector");

	T	copy_stack2(copy_stack);
	printStack(copy_stack2, "copy stack 2", "copy constructor with another stack object");

	empty_stack = copy_stack2;
	printStack(empty_stack, "formerly-empty stack", "empty stack = copy stack 2");

	assert(copy_stack.size() == stack.size()
			&& copy_stack2.size() == copy_stack.size()
			&& empty_stack.size() == copy_stack2.size());
}

template <typename T>
void    test_stack_push(size_t size) {
	printTestCase("stack.push([1-size])");
	
	T	stack;

	for (size_t i = 1; i <= size; i++)
		stack.push(i);

	assert(stack.size() == size);
	printStack(stack, "stack");
}

template <typename T>
void    test_stack_pop(size_t size) {
	printTestCase("stack.pop() x size");
	
	T    stack;

	for (size_t i = 1; i <= size; i++)
		stack.push(i);
	for (size_t i = 1; i <= size; i++)
		stack.pop();
	
	assert(stack.size() == 0);
	printStack(stack, "stack");
}

template <typename T>
void    test_stack_relationalOps(size_t size) {
	printTestCase("stack == != < <= > >=");
	typename T::container_type	c;

	for (size_t i = 0; i < size; i++)
		c.push_back(i);

	T	stack1(c);
	T	stack2(c);

	std::cout << std::boolalpha;
	std::cout << "stack1 == stack2: " << (stack1 == stack2) << std::endl;
	std::cout << "stack1 != stack2: " << (stack1 != stack2) << std::endl;
	std::cout << "stack1 < stack2: " << (stack1 < stack2) << std::endl;
	std::cout << "stack1 <= stack2: " << (stack1 <= stack2) << std::endl;
	std::cout << "stack1 > stack2: " << (stack1 > stack2) << std::endl;
	std::cout << "stack1 >= stack2: " << (stack1 >= stack2) << std::endl;

	stack1.push(42);
	std::cout << "stack1 == stack2: " << (stack1 == stack2) << std::endl;
	std::cout << "stack1 != stack2: " << (stack1 != stack2) << std::endl;
	std::cout << "stack1 < stack2: " << (stack1 < stack2) << std::endl;
	std::cout << "stack1 <= stack2: " << (stack1 <= stack2) << std::endl;
	std::cout << "stack1 > stack2: " << (stack1 > stack2) << std::endl;
	std::cout << "stack1 >= stack2: " << (stack1 >= stack2) << std::endl;
}

void test_stack() {
#ifndef SIMPLE
	printHeader("testing stack");
#endif

	// constructor test
	benchmarkFunction_stress(test_stack_constructors<t_stack>, "default/copy constructors");

	// push test
	benchmarkFunction_stress(test_stack_push<t_stack>, "push");

	// pop test
	benchmarkFunction_stress(test_stack_pop<t_stack>, "pop");

	// relational operators
	benchmarkFunction_stress(test_stack_relationalOps<t_stack>, "relational operators");
}
