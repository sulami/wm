#ifndef WAYLAND_H
#define WAYLAND_H

#include <swc.h>

/*
 * Use swc to initialize a Wayland connection.
 */
struct wl_connection *wayland_init();

/*
 * Callback for adding new screens via swc.
 */
void new_screen(struct swc_screen *);

/*
 * Callback for adding new windows via swc.
 */
void new_window(struct swc_window *);

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

