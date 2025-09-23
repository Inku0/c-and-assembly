#include <stdio.h>
#include "mem.h"
#include "bfi.h"

void interpret(char *program) {
	int i = 0;
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
			case BF_DEBUG:
				mem_printDebug();
				break;
			default:
				break;
				/* Ignoreerime sümboleid, mida me ei tunne. */
		}

		i++;
	}
}

int main(void) {

	interpret("++++>>++<<#");
	/* Eeldatav väljund:
	index: 0 mem[0 .. 9]: 4 0 2 0 0 0 0 0 0 0
	*/
}
