#pragma once

#define inst_boilerplate \
	BF_instruction_t *new = malloc(sizeof(struct BF_instruction_st)); \
	if (new == NULL) { \
		printf("OOM allocating BF_instruction_t\n"); \
		goto cleanup; \
	} \
	new->free = BF_instruction_free;

// this struct describes a BF instruction. Each BF instruction has a run, free, and asmify method
// furthermore, applicable instructions also contain an amount, which describes, for example, how many units to move or add
typedef struct BF_instruction_st {
	// run executes the instruction
  void (*run)(const struct BF_instruction_st *instruction, int *index);

	// free frees the heap memory allocated to contain the instruction
  void (*free)(struct BF_instruction_st *instruction);

  // emit asm version of instruction
  void (*asmify)(const struct BF_instruction_st *instruction, int *index);

  union { // like polymorphism
    // how much to add or subtract by
    int amount;
    // how many units to move in memory
    int units;
    // where to jump when the loop has ended (value is 0)
    int loopForwardIndex;
    // where to jump when the loop has NOT ended (value is not 0)
    int loopBackwardIndex;
  }; // no name given => any of the "names" can be used
} BF_instruction_t;

// generic free function for instructions
void BF_instruction_free(BF_instruction_t *instruction);

// move instruction takes nr of units to move
BF_instruction_t *BF_move_new(int units);

// increment instruction takes amount to increment by (can be negative)
BF_instruction_t *BF_increment_new(int amount);

// reads the input from getc(stdin), calls mem_set(input) if input != EOF
BF_instruction_t* BF_read_new(void);

// write the current index's value to stdout
BF_instruction_t* BF_write_new(void);

// begin loop at some index
BF_instruction_t *BF_beginLoop_new(int index);

// loop ending and its checks
BF_instruction_t *BF_endLoop_new(int loopBackwardIndex);

// set current memory cell to zero (mainly for optimizing `[-]` instructions)
BF_instruction_t *BF_setZero_new(void);
