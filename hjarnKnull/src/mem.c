#include <stdint.h>
#include <stdio.h>
#include "mem.h"
#include "macros.h"

/*
 * Keele Brainfuck mälu koosneb 8-bitistest märgiga arvude massivist,
 * mille pikkus on 30000
 *
 * Nagu eelnevalt öeldud, siis C keeles ei algväärtustata muutujaid automaatselt ja sealjuures ei algväärtustata massiivi elemente. Massiivi elementide algväärtustamiseks on kaks varianti - kas hoiate mingit tõeväärtuse (int) muutujat, mis ütleb kas mälu on algväärtustatud ja kui ei ole, siis algväärtustab selle - seda on vaja siis kontrollida iga eelnevalt kirjeldatud funktsiooni väljakutsel. Teine (veidikene keerulisem) variant on hoida kaht muutujat, mis näitavad, mis osa mälust on algväärtustatud ja
 * teha algväärtustust iga elemendiga just siis, kui selleni esmakordselt jõutakse.
 */

#define MEM_LEN 30000

int8_t mem[MEM_LEN] = {};
int32_t current_index = 0;

int mem_get(void) {
	return mem[current_index];
}

int mem_inc(void) {
	mem[current_index]++;
	return mem_get();
}

int mem_dec(void) {
	--mem[current_index];
	return mem_get();
}

int mem_left(void) {
	--current_index;
	if (current_index < 0) {
		current_index = 0;
	}
	return current_index;
}

int mem_right(void) {
	current_index++;
	if (current_index >= MEM_LEN) {
		current_index = 0;
	}
	return current_index;
}

// miks char v mitte int v?
int mem_set(char v) {
	mem[current_index] = v;
	return mem_get();
}

void mem_printDebug(void) {
	int real_end_index = current_index + 9 > MEM_LEN ? current_index + 9 - MEM_LEN : current_index + 9;
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
