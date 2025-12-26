#pragma once

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
	loop *loops;
} loop_map;

// returns a loop_map parsed from BF code
loop_map *build_loop_map(const char *program, const size_t program_len);

// necessary for compiling an optimized version
// treats optimizable instructions as just a single instruction in order to get the correct position for loops
loop_map *build_optimized_loop_map(const char* program, const size_t optimized_program_len);

// print first 1024 loops
void print_loop_map(const loop_map *loop_map);

// free memory allocated for loop_map
void free_loop_map(loop_map *lm);
