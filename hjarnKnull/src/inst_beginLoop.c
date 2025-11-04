#include "instructions.h"
#include "mem.h"
#include <stdio.h>
#include <stdlib.h>

void BF_beginLoop_run(BF_instruction_t *instruction, int *index) {
  const int val = mem_get();

  // anything below 0 is an illegal and illogical value
  if (instruction->loopForwardIndex < 0) {
    printf("illegal loopForwardIndex %d\n", instruction->loopForwardIndex);
    exit(-1);
  }

  if (val == 0) {
    // + 1 in order to get 1 step forward from loop beginning (content)
    *index = instruction->loopForwardIndex + 1;
  } else {
  	(*index)++;
  }
}

BF_instruction_t *BF_beginLoop_new(void) {
	inst_boilerplate;

	// don't know the index at compile-time => instantiate it with an illegal value
  new->loopForwardIndex = -1;
  new->run = BF_beginLoop_run;
cleanup:
  return new;
}
