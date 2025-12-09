#include "instructions.h"
#include "mem.h"
#include <stdio.h>
#include <stdlib.h>

void BF_move_run(const BF_instruction_t *instruction, int *index) {
  // move n units (given by instruction struct)
  mem_move(instruction->units);

  // move counter forward by 1
  (*index)++;
}

void BF_move_asm(const BF_instruction_t *instruction, int *index) {
#ifdef DEBUG
	printf("\t; instruction: move %d\n", instruction->amount);
	printf("\t; index %d\n", *index);
#endif
	if (instruction->units < 0) {
		printf("\tsub edi, %d\n", abs(instruction->units));
	} else {
		printf("\tadd edi, %d\n", instruction->units);
	}

	(*index)++;
}

BF_instruction_t* BF_move_new(const int units) {
	// sanity check
	if (units == 0) {
  	printf("units can't be 0\n");
   	return NULL;
	}

	inst_boilerplate;

	new->amount = units;
	new->run = BF_move_run;
  new->asmify = BF_move_asm;

	cleanup:
		return new;
}
