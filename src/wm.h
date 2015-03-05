#ifndef WM_H
#define WM_H

#define VERSION "0.1a"

/*
 * Internal representation of a window.
 */
struct window {
	struct swc_window *swc;
	struct screen *screen;
	struct wl_list link;
};

#endif

