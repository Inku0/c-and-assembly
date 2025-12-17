#include "../inc/loop_map.h"

#include <stdio.h>
#include <string.h>

#include "bf.h"

loop_map build_loop_map(const char* program, const size_t program_len) {
	int num_begin = 0;
	int num_end = 0;
	loop loops[MAX_LOOPS] = {0};

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

	loop_map lm = {0};
	lm.num_begin = num_begin;
	lm.num_end = num_end;
	// copy the entire local loops array into the returned struct's loops array
	memcpy(lm.loops, loops, sizeof(loops));

	return lm;
}