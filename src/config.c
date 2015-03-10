#define _DEFAULT_SOURCE

#include <stdio.h>
#include <string.h>

#include "util.h"

void
parse_config(FILE *file)
{
	size_t size = 0;
	char *line = NULL;

	while(getline(&line, &size, file) != -1) {
		char *cmd = strtok(line, " \t");
		if (cmd[0] == '#' || cmd[0] == '\n')
			continue;

		if (!strcmp(cmd, "bind")) {
			char *key = strtok(NULL, " \t\n");
			char *cmd = strtok(NULL, " \t\n");
			if (!key || !cmd) {
				debug("Failed to register keybind");
				continue;
			}

			debug("Binding registered");
		} else if (!strcmp(cmd, "set")) {
			char *setting = strtok(NULL, " \t\n");
			char *value = strtok(NULL, " \t\n");
			if (!setting || !value) {
				debug("Failed to register setting");
				continue;
			}

			debug("Setting registers");
		} else {
			debug("Found unknown command in config");
		}

		/*
		 * TODO
		 * - set the settings accordingly
		 */
	}
}

void
load_config(char *path)
{
	FILE *file;

	debug("Loading config file");

	file = fopen(path, "r");
	if (!file) {
		warn("Could not load config file");
		return;
	}

	debug("Loaded config file");

	parse_config(file);
	fclose(file);
}

