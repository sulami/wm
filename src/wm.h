#ifndef WM_H
#define WM_H

#include <stdbool.h>

#define VERSION "0.2a"

/*
 * Hold the complete global state, the Wayland connection, active
 * screens and windows.
 */
struct wm {
	char *config;

	bool debug;
	int borderwidth;
	unsigned int bordercolor;
	int margins;

	struct wl_connection *wl_connection;
	struct screen *active_screen;
	struct window *active_window;
} wm;

#endif

