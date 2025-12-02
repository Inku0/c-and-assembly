#include <stdio.h>

int main(void) {
  int vajaLabida = 10;

  do {
    if (vajaLabida == 1) {
      printf("Läbida on jäänud veel %d aine\n", vajaLabida);
      vajaLabida--;
      printf("Üks aine sai läbitud ja ongi semester läbi.\n");
    } else {
      printf("Läbida on jäänud veel %d ainet\n", vajaLabida);
      vajaLabida--;
      printf("Üks aine sai läbitud ja jaanud on veel %d.\n", vajaLabida);
    }
  } while (vajaLabida > 0);

  return 0;
}
