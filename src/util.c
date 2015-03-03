#include <stdlib.h>
#include <stdio.h>

void
die(char *err)
{
	fprintf(stderr, "ERROR: %s.\n", err);
	exit(EXIT_FAILURE);
}

