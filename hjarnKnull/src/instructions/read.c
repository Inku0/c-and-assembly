#include "instructions.h"
#include "mem.h"
#include <stdio.h>
#include <stdlib.h>

void BF_read_asm(const BF_instruction_t *instruction, int *index) {
#ifdef DEBUG
	printf("\t; instruction: ,\n");
	printf("\t; index %d\n", *index);
#endif
	printf("\tgetchar_loop_%d:\n", *index);
	printf("\t\tcall getchar\n");
	printf("\t\tcmp eax, 10\n"); // \n ascii value is 10
	printf("\t\tje getchar_loop_%d\n", *index);
	printf("\t\tmov [esi+edi], eax\n");
	// loop is needed to handle \n aka pressing enter

	(*index)++;
}

void BF_read_run(const BF_instruction_t *instruction, int *index) {
	char c = getc(stdin);

	// sanity check
	if (c == EOF) {
		printf("got EOF from input\n");
		return;
	}

  // set mem to the given char
  mem_set(c);

  // move counter forward by 1
  (*index)++;
}

BF_instruction_t* BF_read_new(void) {
	inst_boilerplate;

	new->run = BF_read_run;
	new->asmify = BF_read_asm;

	cleanup:
		return new;
}
