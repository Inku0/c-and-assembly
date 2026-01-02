#pragma once

// optimize instructions like ++, ---, >>>>, <<<<< into 2+, 3-, 4>, 5< -> return the length
int optimize_length(const char *program);