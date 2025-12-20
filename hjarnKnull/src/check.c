#include "check.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "../inc/loop_map.h"
#include "bf.h"

bool check(const char* program, const size_t program_len) {
	const loop_map *loop_map = build_loop_map(program, program_len);
	// find which loop is unmatched
	for (int i = 0; i <= program_len; ++i) {
		if (loop_map->loops[i].jump == -1) {
			fprintf(stderr, "unmatched '%c' at %d\n", loop_map->loops[i].type, loop_map->loops[i].position);
			free((void*)loop_map);
			return false;
		}
	}

	int read_i = 0; // index for reading from program string

	while (program[read_i] != 0) {
		switch (program[read_i]) {
		case BF_INCREASE:
		case BF_DECREASE:
			{
				read_i++;
				break;
			}
		case BF_RIGHT:
		case BF_LEFT:
			{
				read_i++;
				break;
			}
		case BF_READ:
			read_i++;
			break;
		case BF_PRINT:
			read_i++;
			break;
		case BF_START_LOOP:
			{
				read_i++;
				break;
			}
		case BF_END_LOOP:
			{
				read_i++;
				break;
			}
		default:
			// default behavior is to silently ignore unknown symbols
			// but we go beyond that
			fprintf(stderr, "encountered unknown symbol '%c' at %d\n", program[read_i], read_i + 1); // +1 to get the logical position (starting at 1)
			free((void*)loop_map);
			return false;
		}
	}

	free((void*)loop_map);
	return true;
}
