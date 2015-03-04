#ifndef WM_H
#define WM_H

/*
 * Internal representation of a screen.
 */
struct screen {
	struct swc_screen *swc;
	struct wl_list windows;
};

/*
 * Internal representation of a window.
 */
struct window {
	struct swc_window *swc;
	struct screen *screen;
	struct wl_list link;
};

#endif

