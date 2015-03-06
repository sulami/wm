#define _DEFAULT_SOURCE

#include <stdio.h>

#include "util.h"

FILE *
open_config(char *path)
{
	FILE *file;

	if ((file = fopen(path, "r")))
		debug("Loaded config file");
	else {
		warn("Could not load config file");
		return NULL;
	}

	return file;
}

void
parse_config(FILE *file)
{
	char *line = NULL;
	size_t size;

	while(getline(&line, &size, file) != -1) {
		/*
		 * TODO
		 * - parse the active line
		 * - set the settings accordingly
		 */
	}
}

void
load_config(char *path)
{
	debug("Loading config file");
	FILE *file = open_config(path);
	if (file)
		parse_config(file);
}

