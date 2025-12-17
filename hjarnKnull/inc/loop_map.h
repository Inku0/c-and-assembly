#pragma once

#define MAX_LOOPS 1024
#include <stddef.h>

// holds the loop type, its position in the BF code, and where it jumps
typedef struct {
	char type;
	int position;
	int jump;
} loop;

// holds a map of loops and their count
typedef struct {
	int num_begin;
	int num_end;
	loop loops[MAX_LOOPS];
} loop_map;

// returns a loop_map parsed from BF code
loop_map build_loop_map(const char *program, const size_t program_len);
