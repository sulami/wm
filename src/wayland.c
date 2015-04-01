#include <stdlib.h>

#include "util.h"
#include "wayland.h"
#include "window.h"

struct wl_connection *
wayland_init()
{
	debug("Connecting to Wayland");
	struct wl_connection *conn = malloc(sizeof(struct wl_connection));
	if (!conn)
		die("Failed to allocate connection struct");

	debug("Creating display");
	conn->display = wl_display_create();
	if (!conn->display)
		die("Failed to create a Wayland display");

	debug("Adding socket");
	if (wl_display_add_socket(conn->display, NULL) != 0)
		die("Failed to add a socket to the Wayland connection");

	debug("Initializing swc");
	if (!swc_initialize(conn->display, NULL, &manager))
		die("Failed to initialize swc");

	return conn;
}

void
wayland_run(struct wl_connection *conn)
{
	debug("Getting event loop");
	conn->event_loop = wl_display_get_event_loop(conn->display);

	debug("Starting Wayland display");
	wl_display_run(conn->display);
}

void
wayland_exit(struct wl_connection *conn)
{
	debug("Terminating Wayland display");
	wl_display_terminate(conn->display);
	debug("Destroying Wayland display");
	wl_display_destroy(conn->display);
}

