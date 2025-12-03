#pragma once
#include "instructions.h"

void compile(const char *program);

int optimize_length(const char *program);

BF_instruction_t **parse(const char *program, int program_len);