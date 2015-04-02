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
add_move_bind(int key, int x, int y)
{
	struct movement_set *ms = malloc(sizeof(struct movement_set));
	if (!ms) {
		warn("Failed to allocate memory for move bind");
		return;
	}

	ms->x = x;
	ms->y = y;

	swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO, key, &window_move, ms);
}

void
add_warp_bind(int key, int x, int y)
{
	struct warp_set *ws = malloc(sizeof(struct warp_set));
	if (!ws){
		warn("Failed to allocate memory for warp bind");
		return;
	}

	ws->x = x;
	ws->y = y;

	swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO, key, &window_warp, ws);
}

void
add_spawn_bind(int key, char *cmd)
{
	char *command = malloc(sizeof(char) * strlen(cmd));
	if (!command) {
		warn("Failed to allocate memory for spawn bind");
		return;
	}

	strcpy(command, cmd);

	swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO, key, &spawn, command);
}

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

				add_spawn_bind(ks, prog);
			} else if (!strcmp(cmd, "move")) {
				char *cx = strtok(NULL, " \t\n");
				char *cy = strtok(NULL, " \t\n");

				if (!cx || !cy) {
					warn("Failed to register move bind");
					continue;
				}

				int x = strtol(cx, NULL, 10);
				int y = strtol(cy, NULL, 10);

				add_move_bind(ks, x, y);
			} else if (!strcmp(cmd, "warp")) {
				char *cx = strtok(NULL, " \t\n");
				char *cy = strtok(NULL, " \t\n");

				if (!cx || !cy) {
					warn("Failed to register spawn bind");
					continue;
				}

				int x = strtol(cx, NULL, 10);
				int y = strtol(cy, NULL, 10);

				add_warp_bind(ks, x, y);
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

