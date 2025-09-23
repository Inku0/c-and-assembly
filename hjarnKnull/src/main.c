#include "coolStack.h"
#include "coolStackTest.h"
#include "mem.h"
#include "macros.h"
#include <stdio.h>

int main(void) {
  //stack_testPinu();
  //stack_inputLoop();
  //stack_printStack();
  ASSERT(mem_get() == 0);
  ASSERT(mem_inc() == 1);
	ASSERT(mem_inc() == 2);
	ASSERT(mem_right() == 1);
	ASSERT(mem_get() == 0);
	ASSERT(mem_dec() == -1);
	ASSERT(mem_left() == 0);
	ASSERT(mem_get() == 2);
  mem_printDebug();
  return 0;
}
