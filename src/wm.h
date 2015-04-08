#ifndef WM_H
#define WM_H

#include <stdbool.h>

#define VERSION "0.2a"

/*
 * Hold the complete global state, the Wayland connection, active
 * screens and windows.
 */
struct wm {
	bool debug;
	struct wl_connection *wl_connection;
	struct screen *active_screen;
	struct window *active_window;
	/*
	 * Keep this back here under all circumstances. For some
	 * reason, if it is placed in front of the wl_connection,
	 * everything will die. I assume it has something to do with
	 * swc relying on fixed pointers, which are not so fixed when
	 * placing a variably sized string in front. Fixed-size arrays
	 * do not work either, so this is the workaround until I have
	 * figured out something.
	 */
	char *config;
} wm;

#endif

