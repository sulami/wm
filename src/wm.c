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
	bool conf = false;

	wm.debug = false;

	while((opt = getopt(argc, argv, "c:dhv")) != -1) {
		switch (opt) {
		case 'c':
			load_config(optarg);
			conf = true;
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

	/* Load the default config if no custom one has been loaded */
	if (!conf) {
		char *conf = getenv("XDG_CONFIG_HOME");
		strcat(conf, "/.wmrc");
		load_config(conf);
	}

	wm.wl_connection = wayland_init();

	wayland_exit(wm.wl_connection);

	return EXIT_SUCCESS;
}

