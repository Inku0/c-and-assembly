#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/loop_map.h"
#include "bf.h"
#include "mem.h"
#include "simpleStack.h"

#ifdef DEBUG
  #define PRINT_PARAMS "'%c' (kood = %d)\n", c, c
#else
  #define PRINT_PARAMS "%c", c
#endif

#define LOOP_STACK_LEN 1000

void handleStdIn(const char c) {
	if (EOF == c) {
		return;
	}
	mem_set(c);
}

void interpret(const char *program) {
	// Pre-build the loop position map using one stack
	loop_map *loop_map = build_loop_map(program, strlen(program));
	if (loop_map == NULL) {
		fprintf(stderr, "failed to build loop map");
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
					i = loop_map->loops[i].jump;
				}
				break;
			case BF_END_LOOP:
				// If current cell is not 0, jump back to matching '['
				if (mem_get() != 0) {
					i = loop_map->loops[i].jump;
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
	free_loop_map(loop_map);
}