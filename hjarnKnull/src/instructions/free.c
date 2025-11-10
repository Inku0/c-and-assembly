#include "instructions.h"
#include <stdlib.h>

void BF_instruction_free(BF_instruction_t *instruction) {
  free(instruction);
}
