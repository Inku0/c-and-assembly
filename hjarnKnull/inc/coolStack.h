#pragma once

#include <stdbool.h>

/* Funktsioon stack_push saab parameetriks int tüüpi väärtuse, mille lisab globaalsesse pinusse, kui
 * selles on veel ruumi. Vastasel korral trükib ekkraanile vea. Funktsioon ei tagasta midagi.
 */
void stack_push(int value);

/* Funktsioon stack_pop ei saa ühtegi parameetrit ja tagastab globaalse pinu pealmise elemendi, mille ta
 * pinust eemaldab. Kui pinu on juba tühi, siis funktsioon tagastab väärtuse 0.
 */
int stack_pop(void);

/* Funktsioon stack_isEmpty tagastab tõeväärtuse (0-vale ja mitte 0 tõene) vastavalt sellele kas
 * pinu on tühi või mitte.
 */
bool stack_isEmpty(void);

/* Funktsioon stack_peek tagastab pinu pealmise elemendi ilma seda eemaldamata.
 * Kui pinu on tühi, siis see tagastab 0 väärtuse.
 */
int stack_peek(void);


/* Funktsioon stack_printStack trükib ekraanile kõik pinu elemendid eraldi reale alustades ülemisest.
 */
void stack_printStack(void);

/* Funktsioon stack_handleInput võtab argumendina inputi ja lisab/ei lisa seda pinusse
 */
void stack_handleInput(int input);

/* Funktsioon stack_clear pop'ib välja kõik pinu elemendid
 */
void stack_clear(void);

/* annab stacki pikkuse
 */
int stack_len(void);

/* Funktsioon stack_inputLoop jookseb ja handle'ib kuni sisendiks on 0
 */
void stack_inputLoop(void);
