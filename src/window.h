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
 * Show the window passed if hidden.
 */
void show_window(struct window *);

/*
 * Hide the window passed if shown.
 */
void hide_window(struct window *);

/*
 * Set the geometry of a window.
 */
void set_window_geometry(struct window *, struct swc_rectangle *);

/*
 * Change the focused window, handle borders.
 */
void focus_window(struct window *);

/*
 * Focus a window and set it to fullscreen.
 */
void fullscreen_winodw(struct window *);

/*
 * Callback for entering windows, essentially focus them.
 */
void window_entered(void *);

/*
 * Callback for destroying windows. Trigger removal from screen, free
 * the window structure.
 */
void window_destroy(void *);

/*
 * Hold window callbacks.
 */
static const struct swc_window_handler window_handler = {
	.destroy = &window_destroy,
	.entered = &window_entered,
};

#endif

