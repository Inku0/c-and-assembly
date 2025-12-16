#pragma once

#include <stdbool.h>

typedef struct stack_st {
	int len;
	int capacity;
	int *items;

	// push a value to the stack and return it
	int (*push)(struct stack_st *stack, int value);

	// remove the top-most value from the stack and set *value to its value, returns false for a stack underflow
	bool (*pop)(struct stack_st *stack, int *value);

	// returns true if stack is empty
	bool (*isEmpty)(struct stack_st *stack);

	// return the top-most value from the stack without removing it
	int (*peek)(struct stack_st *stack);

	// print all elements of a stack
	void (*printStack)(struct stack_st *stack);

	// destroy the stack
	void (*clear)(struct stack_st *stack);
} stack_t;

stack_t *create_stack(int starting_size);
