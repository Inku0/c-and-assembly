#pragma once

#define inst_boilerplate \
	BF_instruction_t *new = malloc(sizeof(struct BF_instruction_st)); \
	if (new == NULL) { \
		printf("OOM allocating BF_instruction_t\n"); \
		goto cleanup; \
	} \
	new->free = BF_instruction_free;

// see struct hoiab bf instruktsioone koos lisainfoga, mis võimaldab optimeeringut
// pmst annab function pointeri, mis omakorda tahab kahte argumenti: viit instruktsiooni objektile ja viit instruktsiooni indeksile
typedef struct BF_instruction_st {
  void (*run)(struct BF_instruction_st *instruction, int *index);
  void (*free)(struct BF_instruction_st *instruction);

  // emit asm version of instruction
  void (*asmify)(const struct BF_instruction_st *instruction, int *index);

  union { // like polymorphism
    // suurendamise/vähendamise suurus
    int amount;
    // mitu kohta liikuda mälus
    int units;
    // indeks kuhu hüpata, kui getMem() == 0
    int loopForwardIndex;
    // indeks kuhu hüpata tsükli lõpus, kui getMem() != 0
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
BF_instruction_t *BF_beginLoop_new(void);

// loop ending and its checks
BF_instruction_t *BF_endLoop_new(int loopBackwardIndex);
