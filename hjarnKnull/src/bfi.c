#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mem.h"
#include "simpleStack.h"
#include "bf.h"

#ifdef DEBUG
  #define PRINT_PARAMS "'%c' (kood = %d)\n", c, c
#else
  #define PRINT_PARAMS "%c", c
#endif

#define LOOP_STACK_LEN 1000

void handleStdIn(const char c) {
	if (EOF == c) {
		printf("received EOF signal!\n");
		return;
	}
	mem_set(c);
}

// Pre-parse the program to find matching loop brackets
// Returns an array where loop_map[i] contains the matching bracket index
int *build_loop_map(const char *program) {
	const int program_len = (int)strlen(program);
	int *loop_map = calloc(program_len, sizeof(int));
	stack_t *loop_stack = create_stack(LOOP_STACK_LEN); // hard-coded?
	
	if (loop_map == NULL) {
		fprintf(stderr, "OOM while allocating loop map\n");
		exit(EXIT_FAILURE);
	}

	// Initialize all positions to -1 (no match)
	for (int i = 0; i < program_len; i++) {
		loop_map[i] = -1;
	}

	// Scan through program and match brackets
	for (int i = 0; i < program_len; i++) {
		if (program[i] == BF_START_LOOP) {
			loop_stack->push(loop_stack, i);
		} else if (program[i] == BF_END_LOOP) {
			if (loop_stack->isEmpty(loop_stack)) {
				fprintf(stderr, "Unmatched ']' at position %d\n", i);
				free(loop_map);
				loop_stack->clear(loop_stack);
				free(loop_stack);
				return NULL;
			}
			int start_pos = 0;
			const bool success = loop_stack->pop(loop_stack, &start_pos);
			if (!success) {
				free(loop_map);
				loop_stack->clear(loop_stack);
				free(loop_stack);
				return NULL;
			}
			// Store bidirectional mapping
			loop_map[start_pos] = i;  // '[' maps to ']'
			loop_map[i] = start_pos;  // ']' maps to '['
		}
	}

	if (!loop_stack->isEmpty(loop_stack)) {
		printf("Unmatched '[' in program\n");
		free(loop_map);
		loop_stack->clear(loop_stack);
		free(loop_stack);
	  return NULL;
	}

	loop_stack->clear(loop_stack);
	free(loop_stack);
	
	return loop_map;
}

void interpret(const char *program) {
	// Pre-build the loop position map using one stack
	int *loop_map = build_loop_map(program);
	if (loop_map == NULL) {
		fprintf(stderr, "Encountered an error while building loop map\n");
		free(loop_map);
		return;
	}
	
	int i = 0;
	char c;

	while (program[i] != 0) {
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
				handleStdIn((char)getchar());
				break;
			case BF_PRINT:
				c = (char)mem_get();
				printf(PRINT_PARAMS);
				break;
			case BF_START_LOOP:
				// If current cell is 0, jump forward to matching ']'
				if (mem_get() == 0) {
					i = loop_map[i];
				}
				break;
			case BF_END_LOOP:
				// If current cell is not 0, jump back to matching '['
				if (mem_get() != 0) {
					i = loop_map[i];
				}
				break;
			case BF_DEBUG:
				mem_printDebug();
				break;
			default:
				// default behavior is to ignore unknown symbols
				break;
		}
		// increment index
		i++;
	}

	free(loop_map);
}