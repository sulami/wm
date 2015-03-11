#ifndef SCREEN_H
#define SCREEN_H

#include "window.h"

/*
 * Internal representation of a screen.
 */
struct screen {
	unsigned int num_windows;
	struct swc_screen *swc;
	struct wl_list windows;
};

/*
 * Callback for adding new screens via swc.
 */
void new_screen(struct swc_screen *);

/*
 * Handle a change in screen dimensions, e.g. docks.
 */
void screen_usable_geometry_changed(void *);

/*
 * Change the active screen.
 */
void screen_entered(void *);

/*
 * Add a new window to a screen, add it to the list, map it.
 */
void screen_add_window(struct screen *, struct window *);

/*
 * Remove a window from a screen and the list, unmap it.
 */
void screen_remove_window(struct screen *, struct window *);

/*
 * Used to bind the screen handling functions.
 */
static const struct swc_screen_handler screen_handler = {
	.usable_geometry_changed = &screen_usable_geometry_changed,
	.entered = &screen_entered,
};

/*
 * Helper function to get the geometry of a screen.
 */
struct swc_rectangle *screen_get_geometry(struct screen *);

#endif

