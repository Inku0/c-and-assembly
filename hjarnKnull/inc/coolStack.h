#pragma once

#include <stdbool.h>

typedef struct stack_st_old {
	int len;
	int capacity;
	int *items;

	void (*push)(struct stack_st_old *stack, int value);
	int (*pop)(struct stack_st_old *stack);
	bool (*isEmpty)(struct stack_st_old *stack);
	// TODO: implement these as almost class-like methods
} stack_t_old;

/* Funktsioon stack_push saab parameetriks int tüüpi väärtuse, mille lisab globaalsesse pinusse, kui
 * selles on veel ruumi. Vastasel korral trükib ekkraanile vea. Funktsioon ei tagasta midagi.
 */
void stack_push(stack_t_old *stack, int value);

/* Funktsioon stack_pop ei saa ühtegi parameetrit ja tagastab globaalse pinu pealmise elemendi, mille ta
 * pinust eemaldab. Kui pinu on juba tühi, siis funktsioon tagastab väärtuse 0.
 */
int stack_pop(stack_t_old *stack);

/* Funktsioon stack_isEmpty tagastab tõeväärtuse (0-vale ja mitte 0 tõene) vastavalt sellele kas
 * pinu on tühi või mitte.
 */
bool stack_isEmpty(stack_t_old *stack);

/* Funktsioon stack_peek tagastab pinu pealmise elemendi ilma seda eemaldamata.
 * Kui pinu on tühi, siis see tagastab 0 väärtuse.
 */
int stack_peek(stack_t_old *stack);


/* Funktsioon stack_printStack trükib ekraanile kõik pinu elemendid eraldi reale alustades ülemisest.
 */
void stack_printStack(stack_t_old *stack);

/* Funktsioon stack_handleInput võtab argumendina inputi ja lisab/ei lisa seda pinusse
 */
void stack_handleInput(int input);

/* Funktsioon stack_clear pop'ib välja kõik pinu elemendid
 */
void stack_clear(stack_t_old *stack);

/* annab stacki pikkuse
 */
int stack_len(stack_t_old *stack);

/* Funktsioon stack_inputLoop jookseb ja handle'ib kuni sisendiks on 0
 */
void stack_inputLoop(void);
