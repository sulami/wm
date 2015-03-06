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

	struct wm *wm = malloc(sizeof(struct wm));
	if (!wm)
		die("Failed to allocate wm struct");

	wm->wl_connection = wayland_init();

	wayland_exit(wm->wl_connection);

	return EXIT_SUCCESS;
}

