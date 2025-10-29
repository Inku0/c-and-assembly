#include "instructions.h"
#include "mem.h"
#include <stdio.h>
#include <stdlib.h>

void BF_increment_run(BF_instruction_t *instruction, int *index) {
  // increase it by the amount given in *instruction
  mem_add(instruction->amount);

  // move counter forward by 1
  (*index)++;
}

BF_instruction_t* BF_increment_new(int amount) {
	// sanity check
	if (amount == 0) {
  	printf("increment can't be 0\n");
   	return NULL;
	}

	inst_boilerplate;

	new->amount = amount;
	new->run = BF_increment_run;

	cleanup:
		return new;
}
