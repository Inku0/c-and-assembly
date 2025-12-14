#include "instructions.h"
#include "mem.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef DEBUG
  #define PRINT_PARAMS "'%c' (kood = %d)\n", c, c
#else
  #define PRINT_PARAMS "%c", c
#endif


void BF_write_run(const BF_instruction_t *instruction, int *index) {
	const char c = (char)mem_get();
	printf(PRINT_PARAMS);

   // move counter forward by 1
  (*index)++;
}

void BF_write_asm(const BF_instruction_t *instruction, int *index) {
#ifdef DEBUG
	printf("\t; instruction: .\n");
	printf("\t; index %d\n", *index);
#endif
	printf("\tmov eax, 4\n");
	printf("\tmov ebx, 1\n");
	printf("\tlea ecx, [esi+edi]\n");
	printf("\tmov edx, 1\n");
	printf("\tint 0x80\n");

	(*index)++;
}

BF_instruction_t* BF_write_new(void) {
	inst_boilerplate;

	new->run = BF_write_run;
	new->asmify = BF_write_asm;

	cleanup:
		return new;
}
