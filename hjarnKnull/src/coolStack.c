#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "coolStack.h"
#include "macros.h"

#define OOM \
printf("OOM\n"); \
exit(-1);

typedef struct stack_st {
	int len;
	int capacity;
	int *items;
} stack_t;

stack_t stack = {
	.len = 0,
	.capacity = 0,
	.items = NULL
};

void stack_push(int value) {
	// check if memory has been allocated, otherwise init it
	if (stack.len == 0 || stack.items == NULL) {
		stack.capacity = 1;

		// allocate 1 int worth of memory
		stack.items = malloc(sizeof(int) * stack.capacity);

		// if it's null, then the OS failed to allocate memory for it
		if (stack.items == NULL) {
			OOM // Out Of Memory
		}

		// can't have any elements right now (why?)
		stack.len = 0;

	// more elements than capacity allows
	} else if (stack.len >= stack.capacity) {
		int new_capacity = stack.capacity * 2;

		// try to get more memory
		int *new_items = realloc(stack.items, new_capacity * sizeof(int));

		if (new_items == NULL) {
			OOM
		}

		stack.capacity = new_capacity;
		stack.items = new_items;
	}

	// memory has definetely been allocated for it
	stack.items[stack.len] = value;

	// increase len as well
	stack.len++;

  return;
}

int stack_pop(void) {
	// if it's 0 or less, then it's empty
	// or if its pointer is NULL, it's also empty
  if (stack.len <= 0 || stack.items == NULL) {
    printf("Stack underflow!!!\n");
    exit(-1);
  }

  const int value = stack.items[stack.len - 1];
  --stack.len;

  if (stack.capacity == 0) {
  	printf("Stack capacity is 0, can't reduce it\n");

    stack.capacity = 0;
    free(stack.items);
    stack.items = NULL; // to prevent a dangling pointer
  }

  // if there are 4x less elements than the capacity allows, then reduce capacity by 2x
  if (stack.len <= stack.capacity / 4) {
  	int new_capacity = stack.capacity / 2;
		int *new_items = realloc(stack.items, (new_capacity) * sizeof(int));

		if (new_items == NULL) {
			OOM
		}

		stack.items = new_items;
	}

  return value;
}

bool stack_isEmpty(void) {
  return !(stack.len > 0);
}

int stack_peek(void) {
  if (stack_isEmpty()) {
    return 0;
  }
  return stack.items[stack.len - 1];
}

void stack_printStack(void) {
  int temp_stack_size = stack.len;

  while (temp_stack_size > 0) {
    printf("%d\n", stack.items[temp_stack_size - 1]);
    temp_stack_size--;
  }
}

void stack_handleInput(int input) {
  if (stack_isEmpty()) {
    stack_push(input);
  }
  else {
    int peek_value = stack_peek();
    if (input > 0) {

      if (peek_value > 0) {
        stack_push(input);
      }

      else if (peek_value < 0) {
        int top_el = stack_pop();
        int sum = input + top_el;

        if (sum != 0) {
          stack_push(sum);
        }
      }
    }
    else if (input < 0) {
      int top_el = stack_pop();
      int sum = input + top_el;

      if (sum != 0) {
        stack_push(sum);
      }
    }
  }
}

int stack_len(void) {
	return stack.len;
}

void stack_clear(void) {
  int temp_stack_size = stack.len;

  while (temp_stack_size > 0) {
    stack_pop();
    temp_stack_size--;
  }
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
