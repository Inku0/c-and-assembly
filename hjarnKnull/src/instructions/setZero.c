#include "instructions.h"
#include "mem.h"
#include <stdio.h>
#include <stdlib.h>

void BF_setZero_run(const BF_instruction_t *instruction, int *index) {
	// increase it by the amount given in *instruction
	mem_set(0);

	// move counter forward by 1
	(*index)++;
}

void BF_setZero_asm(const BF_instruction_t *instruction, int *index) {
#ifdef DEBUG
	printf("\t; instruction: setZero\n");
	printf("\t; index %d\n", *index);
#endif
	printf("\tmov [esi+edi], 0\n");

	(*index)++;
}

BF_instruction_t* BF_setZero_new(void) {
	inst_boilerplate;

	new->run = BF_setZero_run;
	new->asmify = BF_setZero_asm;

	cleanup:
		return new;
}
