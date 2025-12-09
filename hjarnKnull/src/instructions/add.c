#include "instructions.h"
#include "mem.h"
#include <stdio.h>
#include <stdlib.h>

void BF_increment_run(const BF_instruction_t *instruction, int *index) {
  // increase it by the amount given in *instruction
  mem_add(instruction->amount);

  // move counter forward by 1
  (*index)++;
}

void BF_increment_asm(const BF_instruction_t *instruction, int *index) {
#ifdef DEBUG
	printf("\t; instruction: add %d\n", instruction->amount);
	printf("\t; index %d\n", *index);
#endif
	printf("\tmov al, [esi+edi]\n");
	if (instruction->amount < 0) {
		printf("\tsub al, %d\n", abs(instruction->amount));
	} else {
		printf("\tadd al, %d\n", instruction->amount);
	}
	printf("\tmov [esi+edi], al\n");

	(*index)++;
}

BF_instruction_t* BF_increment_new(const int amount) {
  // sanity check
  if (amount == 0) {
    printf("increment can't be 0\n");
    return NULL;
  }

  inst_boilerplate;

  new->amount = amount;
  new->run = BF_increment_run;
  new->asmify = BF_increment_asm;

  cleanup:
    return new;
}
