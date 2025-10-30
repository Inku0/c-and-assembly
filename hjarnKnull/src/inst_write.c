#include "instructions.h"
#include "mem.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef DEBUG
  #define PRINT_PARAMS "'%c' (kood = %d)\n", c, c
#else
  #define PRINT_PARAMS "%c", c
#endif


void BF_write_run(BF_instruction_t *instruction, int *index) {
	char c = mem_get();
	printf(PRINT_PARAMS);

   // move counter forward by 1
  (*index)++;
}

BF_instruction_t* BF_write_new(void) {
	inst_boilerplate;

	new->run = BF_write_run;

	cleanup:
		return new;
}
