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
 * Set the window position.
 */
void set_window_position(struct window *, int32_t, int32_t);

/*
 * Set the window size.
 */
void set_window_size(struct window *, uint32_t, uint32_t);

/*
 * Set the geometry of a window. This combines setting position and
 * size.
 */
void set_window_geometry(struct window *, struct swc_rectangle *);

/*
 * Set the color and width of the border of a window.
 */
void set_window_border(struct window *, uint32_t, int);

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
 * Begin interactive move of a window.
 */
void begin_move(struct window *);

/*
 * End interactive move of a window.
 */
void end_move(struct window *);

/*
 * Begin interactive resize of a window.
 */
void begin_resize(struct window *);

/*
 * End interactive resize of a window.
 */
void end_resize(struct window *);

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

/*
 * A simple struct for window_move() to package both coordinates in one
 * pointer.
 */
struct movement_set {
	int x;
	int y;
};

/*
 * Move the active window relativ to its current position. To be used
 * as a swc binding with a movement_set struct pointer as first
 * argument, hence the fancy arguments.
 */
void window_move(void *, uint32_t, uint32_t, uint32_t);

#endif

