#include <stdlib.h>
#include "bfc.h"
#include "bft.h"

#include <stdio.h>

#include "instructions.h"

#define asmBoilerplate(bfCode) \
	printf("; translated from BF: "); \
	printf("%s \n", bfCode); \
	printf("global main\n"); \
	printf("extern mem_add\n"); \
	printf("extern mem_move\n"); \
	printf("extern mem_inc\n"); \
	printf("extern mem_dec\n"); \
	printf("extern mem_left\n"); \
	printf("extern mem_rigth\n"); \
	printf("extern mem_get\n"); \
	printf("extern mem_set\n"); \
	printf("extern mem_printDebug\n"); \
	printf("extern putchar\n"); \
	printf("extern getchar\n"); \
	printf("section .text\n"); \
	printf("main:\n");

void printTranslate(BF_instruction_t **inst_array, const int inst_array_length, const char *bfCode) {
	asmBoilerplate(bfCode);
	int i = 0;
	while (1) {
		if (i < 0 || i >= inst_array_length) break;
		if (inst_array[i] != NULL) {
			inst_array[i]->asmify(inst_array[i], &i);
		} else{
			i++;
		}
	}
	printf("\tret\n");

	for (i = 0; i < inst_array_length; i++)
		if (inst_array[i] != NULL) {
			inst_array[i]->free(inst_array[i]);
			inst_array[i] = NULL;
		}
	return;
}

void translate(const char *program) {
  // length of BF program
	const int program_len = optimize_length(program);

  // parses the program into a stack of instructions
  BF_instruction_t **inst_array = parse(program, program_len);

  // run takes the edited inst_array and executes the instructions
  printTranslate(inst_array, program_len, program);

  // free the allocated memory
  free(inst_array);
}
