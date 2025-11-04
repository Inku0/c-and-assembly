#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "coolStack.h"
#include "instructions.h"
#include "mem.h"
#include "bfi.h"

int optimize_length(char *program) {
	int i = 0;
	int optimized_count = 0;

	// get the optimized length of instructions
	while (program[i] != 0) {
		char current = program[i];

		if (current == BF_INCREASE || current == BF_DECREASE ) {
			int count = 1;
			while (program[i + count] == BF_INCREASE || program[i + count] == BF_DECREASE) {
				// count up the number of elements in the optimizable instruction sequence
				count++;
			}
			if (optimized_count != 0) {
				// treat the sequence as just one optimized instruction
				optimized_count++;
			}
			// move forward to the next instruction
			i += count;
		}

		else if (current == BF_RIGHT || current == BF_LEFT) {
			int count = 1;
			while (program[i + count] == BF_RIGHT || program[i + count] == BF_LEFT) {
				// count up the number of elements in the optimizable instruction sequence
				count++;
			}
			if (optimized_count != 0) {
				// treat the sequence as just one optimized instruction
				optimized_count++;
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

// why the double pointer?
BF_instruction_t **parse(char *program, int program_len) {
	stack_t loop_stack = {
		.items = NULL,
		.len = 0,
		.capacity = 0
	};

	// a stack which contains optimized_count number of pointers
	// calloc inits all values to 0
  BF_instruction_t **inst_array = calloc(program_len, sizeof(BF_instruction_t*));

  int read_i = 0; // index for reading from program string
  int write_i = 0; // index for writing to instruction array

	while (program[read_i] != 0 ) {

		// init every instruction as NULL
		inst_array[write_i] = NULL;

		switch (program[read_i]) {
			case BF_INCREASE:
			case BF_DECREASE: {
				int j = 1;
				int sum = (program[read_i] == BF_INCREASE) ? 1 : -1;
				while (program[read_i+j] == BF_DECREASE || program[read_i+j] == BF_INCREASE) {
					program[read_i+j] == BF_INCREASE ? sum++ : --sum;
					j++;
				}
				if (sum != 0 ) {
					inst_array[write_i] = BF_increment_new(sum);
				} else {
					--write_i;
				}
				read_i += j;
				break;
			}
			case BF_RIGHT:
			case BF_LEFT: {
				int j = 1;
				int sum = (program[read_i] == BF_RIGHT) ? 1 : -1;
				while (program[read_i+j] == BF_RIGHT || program[read_i+j] == BF_LEFT) {
					program[read_i+j] == BF_RIGHT ? sum++ : --sum;
					j++;
				}
				if (sum != 0 ) {
					inst_array[write_i] = BF_move_new(sum);
				} else {
					--write_i;
				}
				read_i += j;
				break;
			}
			case BF_READ:
				inst_array[write_i] = BF_read_new();
				read_i++;
				break;
			case BF_PRINT:
				inst_array[write_i] = BF_write_new();
				read_i++;
				break;
			case BF_START_LOOP: {
				inst_array[write_i] = BF_beginLoop_new();
				stack_push(&loop_stack, write_i);
				read_i++;
				break;
			}
			case BF_END_LOOP: {
				int beginIndex = stack_pop(&loop_stack);
				inst_array[write_i] = BF_endLoop_new(beginIndex);
				inst_array[beginIndex]->loopForwardIndex = write_i;
				read_i++;
				break;
			}
			default:
				// default behavior is to silently ignore unknown symbols
				--write_i; // counteract the default ++ behavior
				read_i++;
				break;
		}
		write_i++;
	}

	stack_clear(&loop_stack);

	return inst_array;
}

void run(BF_instruction_t **inst_array, int inst_array_length) {
	int i = 0;
	while (1) {
		if (i < 0 || i >= inst_array_length) break;
		if (inst_array[i] != NULL) {
			inst_array[i]->run(inst_array[i], &i);
		} else{
			i++;
		}
	}
	for (i = 0; i < inst_array_length; i++)
		if (inst_array[i] != NULL) {
			inst_array[i]->free(inst_array[i]);
			inst_array[i] = NULL;
		}
	return;
}

void interpret2(char *program) {
  // length of BF program
  int program_len = optimize_length(program);

  // parses the program into a stack of instructions
  BF_instruction_t **inst_array = parse(program, program_len);

  // run takes the edited inst_array and executes the instructions
  run(inst_array, program_len);

  // free the allocated memory
  free(inst_array);
}

// argument Count and argument Vector
int main(int argc, char **argv) {
  if (argc != 2) {
    printf("bfi must be given an arg in the form of a BF program!\n");
    exit(-1);
  }

  interpret2(argv[1]);
}
