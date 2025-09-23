#include <stdio.h>
#include <assert.h>
#include "coolStack.h"
#include "macros.h"

#define STACK_SIZE 100

struct stack_st {
	int items[STACK_SIZE]; // int stack_items[STACK_SIZE] = {0};
	int len; // int stack_size = 0;
};

typedef struct stack_st stack_t;

stack_t stack = {
	.items = {0},
	.len = 0,
};

void stack_push(int value) {
  // if the stack size equals predefined size, it won't fit => exit
  if (stack.len >= STACK_SIZE) {
    printf("Stack overflow!!!\n");
    return;
  }

  stack.items[stack.len] = value;
  stack.len++; // increase by 1 after having added a value
  return;
}

int stack_pop(void) {
  if (stack.len <= 0) {
    printf("Stack underflow!!!\n");
    return 0;
  }

  stack.len--;
  return stack.items[stack.len - 1]; // starts at 0 so subtract by 1;
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
