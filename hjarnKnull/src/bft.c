#include "bft.h"
#include <stdio.h>
#include <stdlib.h>
#include "bfc.h"
#include "instructions.h"
#include "optimize.h"
#include "printline.h"

#define asmBoilerplate(bfCode) \
	printf("; translated from BF: "); \
	printline(bfCode); \
	printf("\n"); \
	printf("global main\n"); \
	printf("section .text\n"); \
	printf("main:\n"); \
	printf("\tpush esi\n"); \
	printf("\tpush edi\n"); \
	printf("\tmov ecx, 7500\n");                                                                                         \
	printf("\tmem_init:\n"); \
	printf("\t\tpush dword 0\n"); \
	printf("\t\tloop mem_init\n"); \
	printf("\tmov esi, esp\n"); \
	printf("\tmov edi, 0\n");


// (e)SI = Source Index
// loop checks eCx (counter register), if it's not 0 then it decrements it and loops
// so the loop part here initializes 7500 units of 4-byte (dword) memory, all set to 0

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
	printf("\tadd esp, 30000\n");
	printf("\tpop edi\n");
	printf("\tpop esi\n");

	// exit(0)
	printf("\texit:\n");
	printf("\t\tmov eax, 1\n");
	printf("\t\txor ebx, ebx\n");
	printf("\t\tint 0x80\n");

	for (i = 0; i < inst_array_length; i++) {
		if (inst_array[i] != NULL) {
			inst_array[i]->free(inst_array[i]);
			inst_array[i] = NULL;
		}
	}
	return;
}

void translate(const char *program) {
  // length of BF program
	const int program_len = optimize_length(program);

  // parses the program into a stack of instructions
  BF_instruction_t **inst_array = parse(program, program_len);

	if (inst_array == NULL) {
		fprintf(stderr, "bf: parsing failed\n");
		return;
	}

  // run takes the edited inst_array and executes the instructions
  printTranslate(inst_array, program_len, program);

  // free the allocated memory
  free(inst_array);
}
