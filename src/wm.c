#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>

#include "util.h"
#include "wayland.h"

#define VERSION "0.1a"

struct wl_connection *wl;

int
main(int argc, char *argv[])
{
	int opt;

	while((opt = getopt(argc, argv, "vh")) != -1) {
		switch (opt) {
		case 'h':
			puts("TBD");
			break;
		case 'v':
			printf("%s %s\n", argv[0], VERSION);
			break;
		default:
			fprintf(stderr, "Usage: %s [-vh]\n", argv[0]);
			exit(EXIT_FAILURE);
		}
	}

	wl = wayland_init();

	return EXIT_SUCCESS;
}

