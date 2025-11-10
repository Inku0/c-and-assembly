#pragma once

#include <stdbool.h>

typedef struct stack_st {
	int len;
	int capacity;
	int *items;

	void (*push)(struct stack_st *stack, int value);
	int (*pop)(struct stack_st *stack);
	bool (*isEmpty)(struct stack_st *stack);
	int (*peek)(struct stack_st *stack);
	void (*printStack)(struct stack_st *stack);
	void (*clear)(struct stack_st *stack);
	// TODO: implement these as almost class-like methods
} stack_t;

stack_t *create_stack(int starting_size);
