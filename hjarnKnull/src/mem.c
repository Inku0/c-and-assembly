#include <stdio.h>
#include <string.h>
#include "mem.h"
#include "macros.h"

#define MEM_LEN 30000

int8_t mem[MEM_LEN] = {0};
int32_t current_index = 0;

void mem_init(void) {
	memset(mem, 0, MEM_LEN * sizeof(int8_t));
	current_index = 0;
	// for (int i = 0; i <= MEM_LEN; i++) {
	// 	mem[i] = 0;
	// }
	return;
}

int mem_get(void) {
	return mem[current_index];
}

int mem_add(const int8_t amount) {
	mem[current_index] += amount;
	return mem_get();
}

int mem_move(const int units) {
	const int new_index = current_index + units;
	if (new_index < 0) {
		current_index = 0;
	}
	else if (new_index >= MEM_LEN) {
		current_index = new_index % MEM_LEN; // wrap-around
	}
	else {
		current_index = new_index;
	}
	return current_index;
}

int mem_inc(void) {
	mem_add(1);
	return mem_get();
}

int mem_dec(void) {
	mem_add(-1);
	return mem_get();
}

int mem_left(void) {
	return mem_move(-1);
}

int mem_right(void) {
	return mem_move(1);
}

int mem_set(char v) {
	mem[current_index] = v;
	return mem_get();
}

int mem_capacity(void) {
	return MEM_LEN;
}

int mem_position(void) {
	return current_index;
}

void mem_printDebug(void) {
	const int real_end_index = current_index + 9 > MEM_LEN ? current_index + 9 - MEM_LEN : current_index + 9;
	printf("index: %d; mem [%d ... %d]: ", current_index, current_index, real_end_index);
	for (int i = 0; i < 10; i++) {
		printf("%d ", mem_get());
		mem_right();
	}
	for (int i = 0; i < 10; i++) {
		mem_left();
	}
	printf("\n");
}
