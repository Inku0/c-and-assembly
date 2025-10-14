#include <stdio.h>
#include <stdlib.h>
#include "coolStack.h"
#include "mem.h"
#include "bfi.h"

#ifdef DEBUG
  #define PRINT_PARAMS "'%c' (kood = %d)\n", c, c
#else
  #define PRINT_PARAMS "%c", c
#endif

void handleStdIn(char c) {
	if (EOF == c) {
		printf("Sisendi lõpp!\n");
		return;
	}
	// imaginary else
	mem_set(c);
}

void interpret(char *program) {
	stack_t beginning_stack = {
		.items = NULL,
		.len = 0,
		.capacity = 0
	};
	stack_t ending_stack = {
		.items = NULL,
		.len = 0,
		.capacity = 0
	};
	int i = 0;
	char c;

	while (program[i] != 0 ) {
		switch (program[i]) {
			case BF_INCREASE:
				mem_inc();
				break;
			case BF_DECREASE:
				mem_dec();
				break;
			case BF_RIGHT:
				mem_right();
				break;
			case BF_LEFT:
				mem_left();
				break;
			case BF_READ:
				// int c = getc(stdin);
				// why use getc?
				handleStdIn(getc(stdin));
				break;
			case BF_PRINT:
				// char c = mem_get(); Label followed by a declaration is a C23 extension (clang -Wc23-extensions)
				c = mem_get();
				printf(PRINT_PARAMS);
				break;
			case BF_START_LOOP: {
				if (mem_get() == 0) {
					i = stack_pop(&ending_stack);
				} else {
					// -1 to get to the start_loop and not the content
					if (!(stack_isEmpty(&ending_stack))) {
						stack_pop(&ending_stack);
					}
					stack_push(&beginning_stack, i - 1);
				}
			}
				break;
			case BF_END_LOOP:
				stack_push(&ending_stack, i);
				i = stack_pop(&beginning_stack);
				break;
			case BF_DEBUG:
				mem_printDebug();
				break;
			default:
				break;
				/* Ignoreerime sümboleid, mida me ei tunne. */
		}

		i++;
	}

	stack_clear(&beginning_stack);
	stack_clear(&ending_stack);
}

// miks double pointer?
// argument Count and argument Vector
int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Programmil peab olema üks parameeter, milleks on BF programm!\n");

    return 1;
  }

  interpret(argv[1]);

	//interpret("++++>>++<<#");
	/* Eeldatav väljund:
	index: 0 mem[0 .. 9]: 4 0 2 0 0 0 0 0 0 0
	*/
}
