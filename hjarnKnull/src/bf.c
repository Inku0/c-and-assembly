#include <stdio.h>
#include <stdlib.h>

#include "bfc.h"
#include "bfi.h"
#include "bft.h"


// TODO: optimize to multiple passes
// TODO: perhaps add ->debug() method to every instruction for easier optimizing?

// argument Count and argument Vector
int main(int argc, char **argv) {
	// TODO: add flag for interpret/compile
  if (argc != 3) {
    printf("takes 2 arguments: i | c | t for interpret vs compile vs translate and BF program\n");
    exit(-1);
  }

  if (argv[1][0] == 'i') {
  	interpret(argv[2]);
  } else if (argv[1][0] == 'c') {
		compile(argv[2]);
	} else if (argv[1][0] == 't') {
		translate(argv[2]);
	} else {
		printf("First argument must be 'i' for interpret or 'c' for compile or 't' for translate\n");
		exit(-1);
	}
}
