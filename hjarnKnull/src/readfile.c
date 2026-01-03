#include "readfile.h"

#include <stdio.h>
#include <stdlib.h>

char *readline(const char *name) {
	char *line = NULL;
	size_t len = 0;

	FILE* stream = fopen(name, "r");
	if (stream == NULL) {
		free(line);
		// fprintf(stderr, "could not open file %s\n", name);
		return NULL;
	}

	getline(&line, &len, stream);

	fclose(stream);
	return line;
}
