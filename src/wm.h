#ifndef WM_H
#define WM_H

#include <stdbool.h>

#define VERSION "0.2a"

/*
 * Hold the complete global state, the Wayland connection, active
 * screens and windows.
 */
struct wm {
	struct wl_connection *wl_connection;
	struct screen *active_screen;
	struct window *active_window;
	bool debug;
} wm;

#endif

