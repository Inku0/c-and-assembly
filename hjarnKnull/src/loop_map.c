#include "../inc/loop_map.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bf.h"

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
	loop *loops = calloc(program_len, sizeof(loop));
	if (loops == NULL) {
		fprintf(stderr, "OOM at %d in file %s\n", __LINE__, __FILE__);
		exit(EXIT_FAILURE);
	}

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
	lm->loops = loops;

	return lm;
}

// builds a loop map that mirrors parse()'s optimized instruction stream
loop_map *build_optimized_loop_map(const char *program, const size_t optimized_program_len) {
	const size_t capacity = optimized_program_len ? optimized_program_len : 1;

	loop *loops = calloc(capacity, sizeof(loop));
	if (loops == NULL) {
		fprintf(stderr, "OOM at %d in file %s\n", __LINE__, __FILE__);
		exit(EXIT_FAILURE);
	}

	loop_map *lm = malloc(sizeof(loop_map));
	if (lm == NULL) {
		fprintf(stderr, "OOM at %d in file %s\n", __LINE__, __FILE__);
		free(loops);
		exit(EXIT_FAILURE);
	}

	int *stack = malloc(sizeof(int) * capacity);
	if (stack == NULL) {
		fprintf(stderr, "OOM at %d in file %s\n", __LINE__, __FILE__);
		free(loops);
		free(lm);
		exit(EXIT_FAILURE);
	}

	size_t read_i = 0;
	size_t write_i = 0;
	int top = -1;
	int num_begin = 0;
	int num_end = 0;

	while (program[read_i] != '\0') {
		switch (program[read_i]) {
		case BF_INCREASE:
		case BF_DECREASE: {
			int sum = 0;
			size_t span = 0;
			while (program[read_i + span] == BF_INCREASE || program[read_i + span] == BF_DECREASE) {
				sum += (program[read_i + span] == BF_INCREASE) ? 1 : -1;
				++span;
			}
			if (sum != 0) {
				if (write_i >= capacity) goto capacity_error;
				++write_i;
			}
			read_i += span;
			break;
		}
		case BF_RIGHT:
		case BF_LEFT: {
			int sum = 0;
			size_t span = 0;
			while (program[read_i + span] == BF_RIGHT || program[read_i + span] == BF_LEFT) {
				sum += (program[read_i + span] == BF_RIGHT) ? 1 : -1;
				++span;
			}
			if (sum != 0) {
				if (write_i >= capacity) goto capacity_error;
				++write_i;
			}
			read_i += span;
			break;
		}
		case BF_START_LOOP: {
			if (write_i >= capacity) goto capacity_error;
			loops[write_i].type = '[';
			loops[write_i].position = (int)write_i;
			loops[write_i].jump = -1;
			stack[++top] = (int)write_i;
			++num_begin;
			++write_i;
			++read_i;
			break;
		}
		case BF_END_LOOP: {
			if (write_i >= capacity) goto capacity_error;
			if (top < 0) {
				fprintf(stderr, "unmatched ']' at %zu\n", read_i);
				goto fail;
			}
			int begin = stack[top--];
			loops[write_i].type = ']';
			loops[write_i].position = (int)write_i;
			loops[write_i].jump = begin;
			loops[begin].jump = (int)write_i;
			++num_end;
			++write_i;
			++read_i;
			break;
		}
		default:
			if (write_i >= capacity) goto capacity_error;
			++write_i;
			++read_i;
			break;
		}
	}

	if (top >= 0) {
		fprintf(stderr, "unmatched loops!\n");
	}

	lm->num_begin = num_begin;
	lm->num_end = num_end;
	lm->loops = loops;

	free(stack);
	return lm;

capacity_error:
	fprintf(stderr, "loop map capacity mismatch (write_i=%zu, len=%zu)\n", write_i, capacity);
fail:
	free(stack);
	free(loops);
	free(lm);
	exit(EXIT_FAILURE);
}

void free_loop_map(loop_map *lm) {
	if (lm != NULL) {
		free(lm->loops);
		free(lm);
	}
}
