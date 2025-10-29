#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "coolStack.h"
#include "instructions.h"
#include "mem.h"
#include "bfi.h"

// why the double pointer?
void parse(BF_instruction_t **inst_array, char *program) {
	stack_t loop_stack = {
		.items = NULL,
		.len = 0,
		.capacity = 0
	};

	int i = 0;

	while (program[i] != 0 ) {

		// init every instruction as NULL
		inst_array[i] = NULL;

		switch (program[i]) {
			case BF_INCREASE:
				inst_array[i] = BF_increment_new(1);
				break;
			case BF_DECREASE:
				inst_array[i] = BF_increment_new(-1);
				break;
			case BF_RIGHT:
				inst_array[i] = BF_move_new(1);
				break;
			case BF_LEFT:
				inst_array[i] = BF_move_new(-1);
				break;
			case BF_READ:
				inst_array[i] = BF_read_new();
				break;
			case BF_PRINT:
				inst_array[i] = BF_write_new();
				break;
			case BF_START_LOOP: {
				inst_array[i] = BF_beginLoop_new();
				stack_push(&loop_stack, i);
				break;
			}
			case BF_END_LOOP: {
				int beginIndex = stack_pop(&loop_stack);

				inst_array[i] = BF_endLoop_new(beginIndex);

				inst_array[beginIndex]->loopForwardIndex = i;

				break;
			}
			default:
				// default behavior is to silently ignore unknown symbols
				break;
		}

		i++;
	}

	stack_clear(&loop_stack);
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
  int program_len = strlen(program);

  // a stack which contains program_len number of pointers
  BF_instruction_t **inst_array = malloc(sizeof(BF_instruction_t *) * program_len);

  // this parse changes the inst_array in-place
  parse(inst_array, program);

  // run takes the edited inst_array and executes the instructions
  run(inst_array, program_len);

  // free the allocated memory
  free(inst_array);
}

// miks double pointer?
// argument Count and argument Vector
int main(int argc, char **argv) {
  if (argc != 2) {
    printf("bfi must be given an arg in the form of a BF program!\n");
    exit(-1);
  }

  interpret2(argv[1]);
}
