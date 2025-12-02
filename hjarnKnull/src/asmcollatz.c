#include <stdio.h>

unsigned int collatz(unsigned int);

int main(void) {

    unsigned int i = 10;

    while (1) {
        printf("i = %d\n", i);

        if (i == 1) break;

        i = collatz(i);
    }
}