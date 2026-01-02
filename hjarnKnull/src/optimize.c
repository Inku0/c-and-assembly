#include "optimize.h"

#include "bf.h"

int optimize_length(const char *program) {
	int i = 0;
	int optimized_count = 0;

	// get the optimized length of instructions
	while (program[i] != 0) {
		const char current = program[i];

		if (current == BF_START_LOOP && program[i + 1] == BF_DECREASE && program[i + 2] == BF_END_LOOP) {
			optimized_count++;
			i += 3;
		}

		if (current == BF_INCREASE || current == BF_DECREASE ) {
			int count = 1;
			while ((program[i + count] == BF_INCREASE || program[i + count] == BF_DECREASE) && program[i + count] != '\0') {
				// count up the number of elements in the optimizable instruction sequence
				count++;
			}
			// treat the sequence as just one optimized instruction
			optimized_count++;
			// move forward to the next instruction
			i += count;
		}

		else if (current == BF_RIGHT || current == BF_LEFT) {
			int count = 1;
			while ((program[i + count] == BF_RIGHT || program[i + count] == BF_LEFT) && program[i + count] != '\0') {
				// count up the number of elements in the optimizable instruction sequence
				count++;
			}
			// treat the sequence as just one optimized instruction
			optimized_count++;
			// move forward to the next instruction
			i += count;
		}

		else {
			// non-optimizable instruction, just count it as is
			optimized_count++;
			i++;
		}
	}
	return optimized_count;
}
