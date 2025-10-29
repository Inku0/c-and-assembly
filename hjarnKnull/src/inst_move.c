#include "instructions.h"
#include "mem.h"
#include <stdio.h>
#include <stdlib.h>

void BF_move_run(BF_instruction_t *instruction, int *index) {
  // move n units (given by instruction struct)
  mem_move(instruction->units);

  // move counter forward by 1
  (*index)++;
}

BF_instruction_t* BF_move_new(int units) {
	// sanity check
	if (units == 0) {
  	printf("units can't be 0\n");
   	return NULL;
	}

	inst_boilerplate;

	new->amount = units;
	new->run = BF_move_run;

	cleanup:
		return new;
}
