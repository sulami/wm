#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>

#include "util.h"
#include "wayland.h"
#include "wm.h"

int
main(int argc, char *argv[])
{
	int opt;

	wm.debug = false;

	while((opt = getopt(argc, argv, "dhv")) != -1) {
		switch (opt) {
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
			fprintf(stderr, "Usage: %s [-dhv]\n", argv[0]);
			exit(EXIT_FAILURE);
		}
	}

	wm.wl_connection = wayland_init();

	wayland_exit(wm.wl_connection);

	return EXIT_SUCCESS;
}

