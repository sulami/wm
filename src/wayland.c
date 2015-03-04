#include <stdlib.h>
#include <swc.h>
#include <wayland-server.h>
#include <wayland-util.h>

#include "util.h"
#include "wayland.h"

struct wl_connection *
wayland_init()
{
	struct wl_connection *conn = malloc(sizeof(struct wl_connection));
	if (!conn)
		die("Failed to allocate connection struct");

	conn->display = wl_display_create();
	if (!conn->display)
		die("Failed to create a Wayland display");

	if (wl_display_add_socket(conn->display, NULL) != 0)
		die("Failed to add a socket to the Wayland connection");

	if (!swc_initialize(conn->display, NULL, &manager))
		die("Failed to initialize swc");

	conn->event_loop = wl_display_get_event_loop(conn->display);

	wl_display_run(conn->display);

	return conn;
}

void
new_screen(struct swc_screen *swc)
{
	/* TODO */
	if (swc) {} /* shut up the compiler */
}

void
new_window(struct swc_window *swc)
{
	/* TODO */
	if (swc) {} /* shut up the compiler */
}

