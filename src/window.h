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

#endif

