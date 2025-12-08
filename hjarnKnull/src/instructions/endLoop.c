#include "instructions.h"
#include "mem.h"
#include <stdio.h>
#include <stdlib.h>

void BF_endLoop_run(const BF_instruction_t *instruction, int *index) {
  const int val = mem_get();

  // anything below 0 is an illegal and illogical value
  if (instruction->loopBackwardIndex < 0) {
    printf("illegal loopBackwardIndex %d\n", instruction->loopBackwardIndex);
    exit(-1);
  }

  if (val == 0) {
    // value is zero aka loop has ended, just go forward
    // optimized compared to previous version
    (*index)++;
  } else {
  	*index = instruction->loopBackwardIndex;
  }
}

void BF_endLoop_asm(const BF_instruction_t *instruction, int *index) {
#ifdef DEBUG
	printf("\t; instruction: ] at %d\n", instruction->loopBackwardIndex);
	printf("\t; index %d\n", *index);
#endif
	printf("\t\tjmp blp_%d\n", instruction->loopBackwardIndex);
	printf("\telp_%d:\n", *index + 1);

	(*index)++;
}

BF_instruction_t *BF_endLoop_new(const int loopBackwardIndex) {
	inst_boilerplate;
	// don't know the index at compile-time => instantiate it with an illegal value
  new->loopBackwardIndex = loopBackwardIndex;
  new->run = BF_endLoop_run;
	new->asmify = BF_endLoop_asm;
cleanup:
  return new;
}
