#include <stdio.h>

int main(void) {
  int vajaLabida;

  for (vajaLabida = 10; vajaLabida > 0; vajaLabida--) {
    if (vajaLabida - 1 > 0) {
      if (vajaLabida - 1 == 1) {
        printf("Labida on veel jaanud %d aine\n", vajaLabida);
        printf("Uks aine sai labitud ja jaanud on veel %d aine\n", vajaLabida - 1);
      } else {
        printf("Labida on veel jaanud %d ainet\n", vajaLabida);
        printf("Uks aine sai labitud ja jaanud on veel %d ainet\n", vajaLabida - 1);
      }
    } else {
      printf("Labida on veel jaanud 1 aine\n");
      printf("Uks aine sai labitud ja ongi semester labi\n");
    }
  }
  return 0;
}
