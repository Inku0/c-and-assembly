#include "../inc/loop_map.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bf.h"
#include "str_ll.h"

void print_loop_map(const loop_map *loop_map) {
  for (int i = 0; i <= 1023; i++) {
  	if (loop_map->loops[i].type == '[' || loop_map->loops[i].type == ']') {
  		printf("%c\n", loop_map->loops[i].type);
  		printf("loop nr %d at %d is of type %c and jumps to %d\n\n", i, loop_map->loops[i].position, loop_map->loops[i].type, loop_map->loops[i].jump);
  	}
  }
}

loop_map *build_loop_map(const char* program, const size_t program_len) {
	int num_begin = 0;
	int num_end = 0;
	loop loops[MAX_LOOPS] = {0};

	loop_map *lm = malloc(sizeof(loop_map));
	if (lm == NULL) {
		fprintf(stderr, "OOM at %d in file %s\n", __LINE__, __FILE__);
		exit(EXIT_FAILURE);
	}

	// first pass to count up loops
	for (int read_i = 0; read_i < program_len; ++read_i) {
		switch (program[read_i]) {
		case BF_INCREASE:
		case BF_DECREASE:
		case BF_RIGHT:
		case BF_LEFT:
		case BF_READ:
		case BF_PRINT:
			break;
		case BF_START_LOOP:
		{
			++num_begin;
			loops[read_i].type = '[';
			loops[read_i].position = read_i;
			loops[read_i].jump = -1;
			break;
		}
		case BF_END_LOOP:
		{
			++num_end;
			loops[read_i].type = ']';
			loops[read_i].position = read_i;
			loops[read_i].jump = -1;
			break;
		}
		default:
			break;
		}
	}

	// second pass to confirm that loops have matches
	for (int read_i = 0; read_i < program_len; ++read_i) {
		if (program[read_i] == BF_START_LOOP) {
			int nesting = 1;
			int sub_read_i = read_i + 1;
			while (sub_read_i < program_len && nesting != 0) {
				if (program[sub_read_i] == BF_START_LOOP) {
					++nesting;
				} else if (program[sub_read_i] == BF_END_LOOP) {
					--nesting;
					if (nesting == 0) {
						loops[read_i].jump = sub_read_i;
						loops[sub_read_i].jump = read_i; // set both directions
						break;
					}
				}
				++sub_read_i;
			}
		}
	}

	// simple check
	if (num_begin != num_end) {
		fprintf(stderr, "unmatched loops!\n");
	}

	lm->num_begin = num_begin;
	lm->num_end = num_end;
	// copy the entire local loops array into the returned struct's loops array
	memcpy(lm->loops, loops, sizeof(loops));

	return lm;
}

// builds a loop map in three passes
// first pass to convert optimizable instructions to a single instruction (+++ -> +). this loses data, but that's not a problem here
// second pass to count up loops
// third pass to ensure loops match
loop_map *build_optimized_loop_map(const char *program, const size_t optimized_program_len) {
	Node *code_head = string_to_SLL(program);
	compress_consecutive(code_head); // optimize
	#ifdef DEBUG
		print_list(code_head);
	#endif

	loop_map *lm = malloc(sizeof(loop_map));
	if (lm == NULL) {
		fprintf(stderr, "OOM at %d in file %s\n", __LINE__, __FILE__);
		free_sll(code_head);
		exit(EXIT_FAILURE);
	}

	// compute actual node count and ask SSL_to_string for the correct buffer size
	char *new_program = SSL_to_string(code_head); // ensure space for NUL
	if (new_program == NULL) {
		// fall back to empty program on allocation failure
		fprintf(stderr, "OOM at %d in file %s\n", __LINE__, __FILE__);
		free_sll(code_head);
		exit(EXIT_FAILURE);
	}

	// use the actual returned string length
	const size_t new_optimized_program_len = strlen(new_program);
	if (new_optimized_program_len != optimized_program_len) {
		fprintf(stderr, "optimized too heavily! diff %ld (%zu - %zu)\n",
		        (long)new_optimized_program_len - (long)optimized_program_len,
		        new_optimized_program_len, optimized_program_len);
	}

	int num_begin = 0;
	int num_end = 0;
	loop loops[MAX_LOOPS] = {0};

	// first pass to count up loops (use new_optimized_program_len)
	for (size_t read_i = 0; read_i < new_optimized_program_len; ++read_i) {
		switch (new_program[read_i]) {
			case BF_INCREASE:
			case BF_DECREASE:
			case BF_RIGHT:
			case BF_LEFT:
			case BF_READ:
			case BF_PRINT:
				break;
			case BF_START_LOOP:
			{
				++num_begin;
				loops[read_i].type = '[';
				loops[read_i].position = (int)read_i;
				loops[read_i].jump = -1;
				break;
			}
			case BF_END_LOOP:
			{
				++num_end;
				loops[read_i].type = ']';
				loops[read_i].position = (int)read_i;
				loops[read_i].jump = -1;
				break;
			}
			default:
				break;
			}
	}

	// second pass to confirm that loops have matches (use new_optimized_program_len)
	for (size_t read_i = 0; read_i < new_optimized_program_len; ++read_i) {
		if (new_program[read_i] == BF_START_LOOP) {
			int nesting = 1;
			size_t sub_read_i = read_i + 1;
			while (sub_read_i < new_optimized_program_len && nesting != 0) {
				if (new_program[sub_read_i] == BF_START_LOOP) {
					++nesting;
				} else if (new_program[sub_read_i] == BF_END_LOOP) {
					--nesting;
					if (nesting == 0) {
						loops[read_i].jump = (int)sub_read_i;
						loops[sub_read_i].jump = (int)read_i; // set both directions
						break;
					}
				}
				++sub_read_i;
			}
		}
	}

	// simple check
	if (num_begin != num_end) {
		fprintf(stderr, "unmatched loops!\n");
	}

	lm->num_begin = num_begin;
	lm->num_end = num_end;
	// copy the entire local loops array into the returned struct's loops array
	memcpy(lm->loops, loops, sizeof(loops));

	// clean up
	free_sll(code_head);
	free(new_program);

	return lm;
}
