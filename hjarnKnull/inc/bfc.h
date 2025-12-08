#pragma once
#include "instructions.h"

// struct to hold the parsed BF program and its length
typedef struct {
	BF_instruction_t** inst_array;
	int inst_array_length;
} BF_program;

// takes an array of chars as the argument, returns a compiled array of instructions
BF_program compile(const char *program);

// helper function which runs and frees the BF program
void execute(BF_program bfCode);

// helper function which optimizes length by summing up inc/dec and left/right instructions
int optimize_length(const char *program);

// helper function which parses BF code, must also be given the program's length
BF_instruction_t **parse(const char *program, int program_len);