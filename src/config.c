#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <swc.h>
#include <wayland-server.h>
#include <wayland-util.h>
#include <X11/Xlib.h>

#include "window.h"
#include "util.h"

void
parse_config(FILE *file)
{
	char line[256];

	while(fgets(line, sizeof(line), file)) {
		char *cmd = strtok(line, " \t");
		if (cmd[0] == '#' || cmd[0] == '\n')
			continue;

		if (!strcmp(cmd, "bind")) {
			char *key = strtok(NULL, " \t\n");
			char *cmd = strtok(NULL, " \t\n");
			if (!key || !cmd) {
				warn("Failed to register keybind");
				continue;
			}

			int ks = XStringToKeysym(key);
			if (!ks) {
				warn("Unknown key in config");
				continue;
			}

			if (!strcmp(cmd, "spawn")) {
				char *prog = strtok(NULL, " \t\n");
				if (!prog) {
					warn("Failed to register spawn bind");
					continue;
				}
			} else if (!strcmp(cmd, "move")) {
				char *cx = strtok(NULL, "\t\n");
				char *cy = strtok(NULL, "\t\n");

				if (!cx || !cy) {
					warn("Failed to register move bind");
					continue;
				}

				int x = strtol(cx, NULL, 10);
				int y = strtol(cy, NULL, 10);

				swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO,
				                ks, &window_move,
				                &(struct movement_set){x,y});
			} else {
				warn("Unknown command in config");
				continue;
			}

			debug("Binding registered");
		} else if (!strcmp(cmd, "set")) {
			char *setting = strtok(NULL, " \t\n");
			char *value = strtok(NULL, " \t\n");
			if (!setting || !value) {
				warn("Failed to register setting");
				continue;
			}

			debug("Setting registers");
		} else {
			warn("Found unknown command in config");
		}
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

	parse_config(file);

	debug("Loaded config file");

	fclose(file);
}

