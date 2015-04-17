#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <swc.h>
#include <wayland-server.h>
#include <wayland-util.h>
#include <X11/Xlib.h>

#include "binding.h"
#include "config.h"
#include "wm.h"
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
			} else if (!strcmp(cmd, "resize")) {
				char *cw = strtok(NULL, " \t\n");
				char *ch = strtok(NULL, " \t\n");

				if (!cw || !ch) {
					warn("Failed to register resize bind");
					continue;
				}

				int w = strtol(cw, NULL, 10);
				int h = strtol(ch, NULL, 10);

				add_resize_bind(ks, w, h);
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
			} else if (!strcmp(cmd, "focus")) {
				char *cd = strtok(NULL, " \t\n");

				if (!cd) {
					warn("Failed to register focus bind");
					continue;
				}

				int d = strtol(cd, NULL, 10);
				add_focus_bind(ks, d);
			} else if (!strcmp(cmd, "reload")) {
				add_reload_bind(ks);
			} else if (!strcmp(cmd, "quit")) {
				add_quit_bind(ks);
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

			if (!strcmp(setting, "borderwidth")) {
				int b = strtol(value, NULL, 10);
				if (!b) {
					warn("Failed to register border width");
					continue;
				}
				wm.borderwidth = b;
			} else if (!strcmp(setting, "bordercolor")) {
				int c = strtol(value, NULL, 16);
				if (!c) {
					warn("Failed to register border color");
					continue;
				}
				wm.bordercolor = c;
			} else if (!strcmp(setting, "margins")) {
				int m = strtol(value, NULL, 10);
				if (!m) {
					warn("Failed to register margins");
					continue;
				}
				wm.margins = m;
			} else {
				warn("Unknown setting in config");
				continue;
			}

			debug("Setting registered");
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

void
reload_config(void *data, uint32_t time, uint32_t value, uint32_t state)
{
	load_config(wm.config);
}

