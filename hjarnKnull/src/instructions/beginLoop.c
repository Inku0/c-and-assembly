#include "instructions.h"
#include "mem.h"
#include <stdio.h>
#include <stdlib.h>

void BF_beginLoop_run(const BF_instruction_t *instruction, int *index) {
  const int val = mem_get();

  // anything below 0 is an illegal and illogical value
  if (instruction->loopForwardIndex < 0) {
    fprintf(stderr, "illegal loopForwardIndex %d\n", instruction->loopForwardIndex);
    exit(EXIT_FAILURE);
  }

  if (val == 0) {
    // + 1 in order to get 1 step forward from loop beginning (content)
    *index = instruction->loopForwardIndex + 1;
  } else {
  	(*index)++;
  }
}

void BF_beginLoop_asm(const BF_instruction_t *instruction, int *index) {
#ifdef DEBUG
	printf("\t; instruction: [ at %d\n", instruction->loopForwardIndex);
	printf("\t; index %d\n", *index);
#endif
	printf("\tblp_%d:\n", *index);
	printf("\t\tmov eax, 0\n"); // why??? optimization?
	printf("\t\tmov al, [esi+edi]\n");
	printf("\t\tcmp eax, 0\n");
	printf("\t\tje elp_%d\n", instruction->loopForwardIndex+1);

	(*index)++;
}

BF_instruction_t *BF_beginLoop_new(int index) {
	inst_boilerplate;

  new->loopForwardIndex = index;
  new->run = BF_beginLoop_run;
  new->asmify = BF_beginLoop_asm;
cleanup:
  return new;
}
