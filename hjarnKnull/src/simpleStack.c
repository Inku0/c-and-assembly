#include <stdio.h>
#include <stdlib.h>
#include "simpleStack.h"

int push(stack_t *stack, const int value) {
	// check if memory has been allocated, otherwise init it
	if (stack->len == 0) {
		stack->capacity = 1;

		// allocate 1 int worth of memory
		if (stack->items == NULL) {
			stack->items = malloc(sizeof(int) * stack->capacity);
		}

		// if it's null, then the OS failed to allocate memory for it
		if (stack->items == NULL) {
			OOM; // Out Of Memory
		}

	// more elements than capacity allows
	} else if (stack->len >= stack->capacity) {
		const int new_capacity = stack->capacity * 2;

		// try to get more memory
		int *new_items = realloc(stack->items, new_capacity * sizeof(int));

		if (new_items == NULL) {
			OOM;
		}

		stack->capacity = new_capacity;
		stack->items = new_items;
	}

	// memory has definitely been allocated for it
	stack->items[stack->len] = value;

	// increase len as well
	stack->len++;

	return stack->items[stack->len - 1];
}

bool pop(stack_t *stack, int *out) {
	// if it's 0 or less, then it's empty
	// or if its pointer is NULL, it's also empty
	if (stack->len <= 0 || stack->items == NULL) {
		// fprintf(stderr, "Stack underflow!\n");
		return false;
	}

	const int value = stack->items[stack->len - 1];

	--stack->len;

	if (stack->len == 0) {
		stack->capacity = 0;
		free(stack->items);
		stack->items = NULL; // to prevent a dangling pointer
		goto control;
	}

	// if there are 4x fewer elements than the capacity allows, then reduce capacity by 2x
	if (stack->len <= (stack->capacity / 4)) {
		const int new_capacity = (stack->capacity / 2) + (stack->capacity % 2 != 0); // ceiling division
		int *new_items = realloc(stack->items, (new_capacity) * sizeof(int));

		if (new_items == NULL) {
			OOM;
		}

		stack->capacity = new_capacity;
		stack->items = new_items;
	}

	control:
		if (out) {
			*out = value;
		}
		return true;
}

bool isEmpty(stack_t *stack) {
	return !(stack->len > 0);
}

int peek(stack_t *stack) {
	if (stack->isEmpty(stack)) {
		return 0;
	}
	return stack->items[stack->len - 1];
}

void printStack(stack_t *stack) {
	int temp_stack_size = stack->len;

	while (temp_stack_size > 0) {
		printf("%d\n", stack->items[temp_stack_size - 1]);
		temp_stack_size--;
	}
}

void clear(stack_t *stack) {
	// pop() already frees items when len reaches 0
	while (stack->len > 0) {
		stack->pop(stack, NULL);
	}
	// items should already be NULL and freed by pop()
	// but just to be safe:
	if (stack->items != NULL) {
		free(stack->items);
		stack->items = NULL;
	}
	stack->capacity = 0;
	stack->len = 0;
}

stack_t *create_stack(int starting_size) {
	stack_t *new_stack = malloc(sizeof(stack_t));

	if (new_stack == NULL) {
		OOM;
	}

	new_stack->items = calloc(starting_size, sizeof(int));

	if (new_stack->items == NULL) {
		free(new_stack);
		OOM;
	}

	new_stack->len = 0;
	new_stack->capacity = starting_size;
	new_stack->push = push;
	new_stack->pop = pop;
	new_stack->isEmpty = isEmpty;
	new_stack->peek = peek;
	new_stack->printStack = printStack;
	new_stack->clear = clear;

	return new_stack;
}
