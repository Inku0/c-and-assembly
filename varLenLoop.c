#include "stdio.h"


int collatz(int input) {
  int collatzedInput;

  if (input % 2 == 0) {
    collatzedInput = input / 2;
  } else {
    collatzedInput = (input * 3) + 1;
  }

  if (collatzedInput == 1) {
    return 0;
  } else {
    return collatzedInput;
  }
}

void whileCollatz(int input) {
  do {
    printf("%d\n", input);
    input = collatz(input);
  } while (input != 0);
  printf("1\n");
}

int main(void) {
  int someNum = 7;

  whileCollatz(someNum);

  return 0;
}
