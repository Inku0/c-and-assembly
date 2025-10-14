#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "coolStack.h"
#include "macros.h"

#define OOM \
printf("OOM at %d\n", __LINE__); \
exit(-1);

void stack_push(stack_t *stack, int value) {
	// check if memory has been allocated, otherwise init it
	if (stack->len == 0) {
		stack->capacity = 1;

		// allocate 1 int worth of memory
		if (stack->items == NULL) {
			stack->items = malloc(sizeof(int) * stack->capacity);
		}

		// if it's null, then the OS failed to allocate memory for it
		if (stack->items == NULL) {
			OOM // Out Of Memory
		}

	// more elements than capacity allows
	} else if (stack->len >= stack->capacity) {
		int new_capacity = stack->capacity * 2;

		// try to get more memory
		int *new_items = realloc(stack->items, new_capacity * sizeof(int));

		if (new_items == NULL) {
			OOM
		}

		stack->capacity = new_capacity;
		stack->items = new_items;
	}

	// memory has definitely been allocated for it
	stack->items[stack->len] = value;

	// increase len as well
	stack->len++;

	return;
}

int stack_pop(stack_t *stack) {
	// if it's 0 or less, then it's empty
	// or if its pointer is NULL, it's also empty
	if (stack->len <= 0 || stack->items == NULL) {
		printf("Stack underflow!!!\n");
		exit(-1);
	}

	const int value = stack->items[stack->len - 1];

	--stack->len;

	if (stack->len == 0) {
		stack->capacity = 0;
		free(stack->items);
		stack->items = NULL; // to prevent a dangling pointer
		return value;
	}

	// if there are 4x less elements than the capacity allows, then reduce capacity by 2x
	if (stack->len <= (stack->capacity / 4)) {
		int new_capacity = (stack->capacity / 2) + (stack->capacity % 2 != 0); // ceiling division
		int *new_items = realloc(stack->items, (new_capacity) * sizeof(int));

		if (new_items == NULL) {
			OOM
		}

		stack->capacity = new_capacity;
		stack->items = new_items;
	}

	return value;
}

bool stack_isEmpty(stack_t *stack) {
	return !(stack->len > 0);
}

int stack_peek(stack_t *stack) {
	if (stack_isEmpty(stack)) {
		return 0;
	}
	return stack->items[stack->len - 1];
}

void stack_printStack(stack_t *stack) {
	int temp_stack_size = stack->len;

	while (temp_stack_size > 0) {
		printf("%d\n", stack->items[temp_stack_size - 1]);
		temp_stack_size--;
	}
}

stack_t input_stack = {
	.items = NULL,
	.len = 0,
	.capacity = 0
};

void stack_handleInput(int input) {
	if (stack_isEmpty(&input_stack)) {
		stack_push(&input_stack, input);
	}
	else {
		int peek_value = stack_peek(&input_stack);
		if (input > 0) {

			if (peek_value > 0) {
				stack_push(&input_stack, input);
			}

			else if (peek_value < 0) {
				int top_el = stack_pop(&input_stack);
				int sum = input + top_el;

				if (sum != 0) {
					stack_push(&input_stack, sum);
				}
			}
		}
		else if (input < 0) {
			int top_el = stack_pop(&input_stack);
			int sum = input + top_el;

			if (sum != 0) {
				stack_push(&input_stack, sum);
			}
		}
	}
}

int stack_len(stack_t *stack) {
	return stack->len;
}

void stack_clear(stack_t *stack) {
	int temp_stack_size = stack->len;

	while (temp_stack_size > 0) {
		stack_pop(stack);
		temp_stack_size--;
	}
	free(stack->items);
	stack->items = NULL;
	stack->capacity = 0;
	stack->len = 0;
}

void stack_inputLoop(void) {
	int sisend;
	do {
		int numFilled = scanf("%d", &sisend);
		ASSERT(numFilled == 1);
		// printf("sisestati %d\n", sisend);
		stack_handleInput(sisend);
	} while (sisend != 0);
	printf("\n");
}
