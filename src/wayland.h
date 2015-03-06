#ifndef WAYLAND_H
#define WAYLAND_H

#include <swc.h>

#include "screen.h"
#include "window.h"

/*
 * Use swc to initialize a Wayland connection.
 */
struct wl_connection *wayland_init();

/*
 * Terminate an existing Wayland connection by destroying the display.
 */
void wayland_exit(struct wl_connection *);

/*
 * Swc manager to point to required callbacks.
 */
static const struct swc_manager manager = {
	&new_screen,
	&new_window,
};

/*
 * Connection struct to keep all wayland-specific stuff in one place.
 */
struct wl_connection {
	struct wl_display *display;
	struct wl_event_loop *event_loop;
};

#endif

