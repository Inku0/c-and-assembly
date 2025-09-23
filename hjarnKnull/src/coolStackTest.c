#include <stdlib.h>
#include <stdio.h>
#include "coolStack.h"
#include "macros.h"

int stack_testPinu(void) {
  ASSERT(stack_isEmpty() == true);
  stack_push(12);
  ASSERT(stack_isEmpty() == false);
  stack_push(15);
  stack_push(17);
  ASSERT(stack_peek() == 17);

  stack_clear();

  // stack_printStack();

  return 0;
}
