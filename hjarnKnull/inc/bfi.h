#pragma once

// acts as an interpreter for BF code, executing it directly without optimizations
void interpret(const char *program);

// pre-parse the program to find matching loop brackets
// returns an array where loop_map[i] contains the matching bracket index
int *build_loop_map(const char *program);