#include <stdlib.h>
#include "bf.h"
#include "bfc.h"

#include <stdio.h>

#include "instructions.h"
#include "loop_map.h"

// TODO: treat add(0) and move(0) as non-operations

// why the double pointer?
BF_instruction_t **parse(const char *program, const int program_len) {
	loop_map *loop_map = build_optimized_loop_map(program, program_len);
	if (loop_map == NULL) {
		fprintf(stderr, "failed to build loop map\n");
		return NULL;
	}

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
				// TODO: optimize cycle immediately if it doesn't depend on user input (is fully deterministic)
				if (program[read_i + 1] == BF_DECREASE && program[read_i + 2] == BF_END_LOOP) {
					inst_array[write_i] = BF_setZero_new();
					read_i += 3; // jump ahead of the `[-]` loop
				} else {
					inst_array[write_i] = BF_beginLoop_new(loop_map->loops[write_i].jump);
					read_i++;
				}
				break;
			}
			case BF_END_LOOP: {
				inst_array[write_i] = BF_endLoop_new(loop_map->loops[write_i].jump);
				read_i++;
				break;
			}
			default:
				read_i++;
				break;
		}
		write_i++;
	}

	free_loop_map(loop_map);
	return inst_array;
}

void run(BF_instruction_t **inst_array, const int inst_array_length) {
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

BF_program compile(const char *program) {
  // length of BF program
	const int program_len = optimize_length(program);

  // parses the program into a stack of instructions
  BF_instruction_t **inst_array = parse(program, program_len);
	if (inst_array == NULL) {
		const BF_program bfCode = {
			.inst_array = NULL,
			.inst_array_length = 0,
		};
		return bfCode;
	}

	// for clarity
	const BF_program bfCode = {
		.inst_array = inst_array,
		.inst_array_length = program_len,
	};

  return bfCode;
}

void execute(const BF_program bfCode) {
	// run takes an inst_array and executes the instructions contained therein
	run(bfCode.inst_array, bfCode.inst_array_length);

	// free the allocated memory
	free(bfCode.inst_array);
}
