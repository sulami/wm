#include <getopt.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "config.h"
#include "util.h"
#include "wayland.h"
#include "wm.h"

int
main(int argc, char *argv[])
{
	int opt;

	wm.debug = false;
	wm.borders = 0;
	wm.margins = 0;

	while((opt = getopt(argc, argv, "c:dhv")) != -1) {
		switch (opt) {
		case 'c':
			wm.config = optarg;
			break;
		case 'd':
			wm.debug = true;
			debug("Enabled debug output");
			break;
		case 'h':
			puts("TBD");
			break;
		case 'v':
			printf("%s %s\n", argv[0], VERSION);
			break;
		default:
			fprintf(stderr, "Usage: %s [-dhv] [-c config]\n",
			        argv[0]);
			exit(EXIT_FAILURE);
		}
	}

	wm.wl_connection = wayland_init();

	/* Load the default config if no custom one has been loaded */
	if (!wm.config) {
		char *conf = getenv("XDG_CONFIG_HOME");
		strcat(conf, "/.wmrc");
		wm.config = conf;
	}

	load_config(wm.config);

	wayland_run(wm.wl_connection);

	wayland_exit(wm.wl_connection);

	return EXIT_SUCCESS;
}

