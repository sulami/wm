#ifndef WINDOW_H
#define WINDOW_H

/*
 * Internal representation of a window.
 */
struct window {
	struct swc_window *swc;
	struct screen *screen;
	struct wl_list link;
};

/*
 * Callback for adding new windows via swc.
 */
void new_window(struct swc_window *);

/*
 * Change the focused window, handle borders.
 */
void focus_window(struct window *);

/*
 * Callback for entering windows, essentially focus them.
 */
void window_entered(void *);

/*
 * Hold window callbacks.
 */
static const struct swc_window_handler window_handler = {
	/* FIXME */
	.destroy = NULL,
	.entered = &window_entered,
};

#endif

