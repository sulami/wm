#include <stdlib.h>
#include <swc.h>

#include "screen.h"
#include "util.h"
#include "window.h"
#include "wm.h"

void
new_window(struct swc_window *swc)
{
	debug("Adding new window");
	struct window *window = malloc(sizeof(struct window));
	if (!window)
		die("Failed to allocate window");

	window->swc = swc;
	window->screen = NULL;

	swc_window_set_handler(swc, &window_handler, window);
	swc_window_set_stacked(window->swc); /* TODO other modes? */
	screen_add_window(wm.active_screen, window);
	focus_window(window);
}

void
focus_window(struct window *window)
{
	debug("Switching window focus");
	if (window) {
		swc_window_focus(window->swc);
		/* TODO get the border color (and size?) from the config */
		set_window_border(window, 0xffffffff, wm.borderwidth);
	} else {
		swc_window_focus(NULL);
	}

	wm.active_window = window;
}

void
fullscreen_winodw(struct window *window)
{
	debug("Fullscreening window");
	focus_window(window);
	swc_window_set_fullscreen(window->swc, window->screen->swc);
}

void
show_window(struct window *window)
{
	debug("Showing window");
	swc_window_show(window->swc);
}

void
hide_window(struct window *window)
{
	debug("Hiding window");
	swc_window_hide(window->swc);
}

void
set_window_position(struct window *window, int32_t x, int32_t y)
{
	debug("Setting window position");
	swc_window_set_position(window->swc, x, y);
}

void
set_window_size(struct window *window, uint32_t width, uint32_t height)
{
	debug("Setting window size");
	swc_window_set_size(window->swc, width, height);
}

struct swc_rectangle *
get_window_geometry(struct window *window)
{
	debug("Getting window geometry");
	return swc_window_get_geometry(window->swc);
}

void
set_window_geometry(struct window *window, struct swc_rectangle *geometry)
{
	debug("Setting window geometry");
	swc_window_set_geometry(window->swc, geometry);
}

void
set_window_border(struct window *window, uint32_t color, int width)
{
	debug("Setting window border");
	swc_window_set_border(window->swc, color, width);
}

void
window_entered(void *data)
{
	debug("Window entered");
	struct window *window = data;

	focus_window(window);
}

void
window_destroy(void *data)
{
	debug("Window destroyed");
	struct window *window = data;

	/* TODO change focus? */

	screen_remove_window(window->screen, window);
	free(window);
}

void
begin_move(struct window *window)
{
	debug("Beginning interactive window move");
	swc_window_begin_move(window->swc);
}

void
end_move(struct window *window)
{
	debug("Ending interactive window move");
	swc_window_end_move(window->swc);
}

void
begin_resize(struct window *window)
{
	debug("Beginning interactive window resize");
	swc_window_begin_resize(window->swc, SWC_WINDOW_EDGE_AUTO);
}

void
end_resize(struct window *window)
{
	debug("Ending interactive window resize");
	swc_window_end_resize(window->swc);
}

void
window_move(void *data, uint32_t time, uint32_t value, uint32_t state)
{
	debug("Moving window");

	struct movement_set *ms = (struct movement_set *)data;
	struct window *win = wm.active_window;
	struct swc_rectangle *geo = get_window_geometry(win);

	set_window_position(win, geo->x + ms->x, geo->y + ms->y);
}

void
window_resize(void *data, uint32_t time, uint32_t value, uint32_t state)
{
	debug("Resizing window");

	struct resize_set *rs = (struct resize_set *)data;
	struct window *win = wm.active_window;
	struct swc_rectangle *geo = get_window_geometry(win);

	set_window_size(win, geo->width + rs->w, geo->height + rs->h);
}

void
window_warp(void *data, uint32_t time, uint32_t value, uint32_t state)
{
	debug("Warping window");

	int x, y;

	struct warp_set *ws = (struct warp_set *)data;
	struct window *win = wm.active_window;
	struct swc_rectangle *wingeo = get_window_geometry(win);
	struct screen *scr = win->screen;
	struct swc_rectangle *scrgeo = get_screen_geometry(scr);

	if (ws->x < 0)
		x = wm.margins;
	else if (ws->x > 0)
		x = scrgeo->width - wingeo->width - wm.margins;
	else
		x = scrgeo->width / 2 - wingeo->width / 2;

	if (ws->y < 0)
		y = wm.margins;
	else if (ws->y > 0)
		y = scrgeo->height - wingeo->height - wm.margins;
	else
		y = scrgeo->height / 2 - wingeo->height / 2;

	set_window_position(win, x, y);
}

void
window_change_focus(void *data, uint32_t time, uint32_t value, uint32_t state)
{
	debug("Changing focus");

	struct window *win = wm.active_window;

	if (*(int *)data > 0) {
		win = wl_container_of(win->link.next, win, link);
	} else {
		win = wl_container_of(win->link.prev, win, link);
	}

	focus_window(win);
}

