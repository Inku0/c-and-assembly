#pragma once
#include <stdint.h>

// inits the memory with nulls
void mem_init(void);

// add amount given to current memory index
// returns the new value
int mem_add(int8_t amount);

// move memory index n units to the left or right
// returns the new index
int mem_move(int units);

// increment memory
// returns the new value
int mem_inc(void);

// decrement memory
// returns the new value
int mem_dec(void);

// move memory index 1 unit to the left
// returns the new index
int mem_left(void);

// move memory index 1 unit to the right
// returns the new index
int mem_right(void);

// return value at current index
int mem_get(void);

// save value to current index and also return it
int mem_set(char v);

// print debug info
// example: index: 10 mem [10 .. 19]: 7 6 10 -12 55 22 0 0 0 0
void mem_printDebug(void);
