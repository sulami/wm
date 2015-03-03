#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <wayland-server.h>
#include <wayland-util.h>

#include "util.h"

#define VERSION "0.1a"

struct wl_display *display;
struct wl_global *global;
struct wl_event_loop *event_loop;
struct wl_list screens;
struct wl_list hidden_winodws;

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

	display = wl_display_create();
	if (!display)
		die("Failed to create a wayland display");

	if (wl_display_add_socket(display, NULL) != 0)
		die("Failed to add a wayland socket");

	event_loop = wl_display_get_event_loop(display);
	if (!event_loop)
		die("Failed to get a wayland event loop");

	wl_list_init(&screens);
	wl_list_init(&hidden_winodws);

	return EXIT_SUCCESS;
}

