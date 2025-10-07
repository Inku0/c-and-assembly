#include <stdio.h>
#include <assert.h>
#include "coolStack.h"
#include "macros.h"

#define STACK_SIZE 100

#define STACK_PICKER stack_t *stack_ptr; \
	if ('b' == c) { \
		stack_ptr = &beginning_stack; \
	} else if ('e' == c) { \
		stack_ptr = &ending_stack; \
	} else { \
		exit(-1); \
	}

struct stack_st {
	int items[STACK_SIZE];
	int len;
};

typedef struct stack_st stack_t;

stack_t beginning_stack = {
	.items = {0},
	.len = 0,
};

stack_t ending_stack = {
	.items = {0},
	.len = 0,
};

void stack_push(int value, char c) {
	STACK_PICKER
  // if the stack size equals predefined size, it won't fit => exit
  if (stack_ptr->len >= STACK_SIZE) {
    printf("Stack overflow!!!\n");
    exit(-1);
  }

  stack_ptr->items[stack_ptr->len] = value;
  stack_ptr->len++; // increase by 1 after having added a value
  return;
}

int stack_pop(char c) {
	STACK_PICKER
  if (stack_ptr->len <= 0) {
    printf("Stack underflow!!!\n");
    exit(-1);
  }

  const int value = stack_ptr->items[stack_ptr->len - 1];
  stack_ptr->len--;
  return value;
}

bool stack_isEmpty(char c) {
	STACK_PICKER
  return !(stack_ptr->len > 0);
}

int stack_peek(char c) {
	STACK_PICKER
  if (stack_isEmpty(c)) {
    return 0;
  }
  return stack_ptr->items[stack_ptr->len - 1];
}

void stack_printStack(char c) {
	STACK_PICKER
  int temp_stack_size = stack_ptr->len;

  while (temp_stack_size > 0) {
    printf("%d\n", stack_ptr->items[temp_stack_size - 1]);
    temp_stack_size--;
  }
}

void stack_handleInput(int input) {
  char c = 'b'; // Default to beginning stack
  if (stack_isEmpty(c)) {
    stack_push(input, c);
  }
  else {
    int peek_value = stack_peek(c);
    if (input > 0) {

      if (peek_value > 0) {
        stack_push(input, c);
      }

      else if (peek_value < 0) {
        int top_el = stack_pop(c);
        int sum = input + top_el;

        if (sum != 0) {
          stack_push(sum, c);
        }
      }
    }
    else if (input < 0) {
      int top_el = stack_pop(c);
      int sum = input + top_el;

      if (sum != 0) {
        stack_push(sum, c);
      }
    }
  }
}

int stack_len(char c) {
	STACK_PICKER
	return stack_ptr->len;
}

void stack_clear(char c) {
	STACK_PICKER
  int temp_stack_size = stack_ptr->len;

  while (temp_stack_size > 0) {
    stack_pop(c);
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
