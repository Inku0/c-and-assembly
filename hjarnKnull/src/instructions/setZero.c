#include "instructions.h"
#include "mem.h"
#include <stdio.h>
#include <stdlib.h>

void BF_setZero_run(const BF_instruction_t *instruction, int *index) {
	// set the current memory cell to 0
	mem_set(0);

	// move counter forward by 1
	(*index)++;
}

void BF_setZero_asm(const BF_instruction_t *instruction, int *index) {
#ifdef DEBUG
	printf("\t; instruction: setZero\n");
	printf("\t; index %d\n", *index);
#endif
	printf("\tmov al, [esi+edi]\n");
	printf("\txor al, al\n");
	printf("\tmov [esi+edi], al\n");

	(*index)++;
}

BF_instruction_t* BF_setZero_new(void) {
	inst_boilerplate;

	new->run = BF_setZero_run;
	new->asmify = BF_setZero_asm;

	cleanup:
		return new;
}
