#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bfc.h"
#include "bfi.h"
#include "bft.h"
#include "check.h"
#include "mem.h"


// TODO: optimize to multiple passes
// TODO: perhaps add ->debug() method to every instruction for easier optimizing?

// argument Count and argument Vector
int main(const int argc, char **argv) {
  if (argc != 3) {
    fprintf(stderr, "bf: bf must be given 2 arguments:\n i | c | t for interpret vs compile vs translate\n and a BF program (either inline or as a file)\n");
    fprintf(stderr, "example: bf c \",+++.\"\n");
  	return EXIT_FAILURE;
  }

	if (!check(argv[2], strlen(argv[2]))) {
		return EXIT_FAILURE;
	}

	mem_init();

  if (argv[1][0] == 'i') {
  	interpret(argv[2]);
  }

	else if (argv[1][0] == 'c') {
		const BF_program bfCode = compile(argv[2]);
  	if (bfCode.inst_array == NULL || bfCode.inst_array_length == 0) {
  		fprintf(stderr, "bf: compile failed\n");
  		return EXIT_FAILURE;
  	}
  	execute(bfCode);
	}

	else if (argv[1][0] == 't') {
		translate(argv[2]);
	}

	else {
		fprintf(stderr, "bf: unknown argument '%c'\n first argument must be 'i' for interpret or 'c' for compile or 't' for translate\n", argv[1][0]);
    fprintf(stderr, "example: bf c \",+++.\"\n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
