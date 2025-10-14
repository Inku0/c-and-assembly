#include "coolStack.h"
#include <stdlib.h>

stack_t main_stack = {
	.items = NULL,
	.len = 0,
	.capacity = 0
};

int main(void) {
	stack_push(&main_stack, 5);
	stack_pop(&main_stack);
  return 0;
}
