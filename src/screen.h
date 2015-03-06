#ifndef SCREEN_H
#define SCREEN_H

/*
 * Internal representation of a screen.
 */
struct screen {
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
 * Used to bind the screen handling functions.
 */
static const struct swc_screen_handler screen_handler = {
	.usable_geometry_changed = &screen_usable_geometry_changed,
	.entered = &screen_entered,
};

#endif

