#include "printline.h"

#include <stdio.h>
#include <string.h>

void printline(const char *str) {
	const size_t len = strlen(str);
	for (size_t i = 0; i < len; i++) {
		if (str[i] != '\n') {
			putchar(str[i]);
		}
	}
}