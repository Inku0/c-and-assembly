#include "stdio.h"

int recCollatz(int input) {
  int collatzedInput;

  printf("%d\n", input);

  if (input % 2 == 0) {
    collatzedInput = input / 2;
  } else {
    collatzedInput = (input * 3) + 1;
  }

  if (collatzedInput == 1) {
    printf("1\n");
    return 0;
  } else {
    return recCollatz(collatzedInput);
  }
}

int main(void) {
  int someNumber = 7;

  recCollatz(someNumber);

  return 0;
}
