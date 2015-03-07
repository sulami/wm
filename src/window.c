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
	if (window)
		swc_window_focus(window->swc);
		/*
		* TODO
		* - set borders ?
		*/
	else
		swc_window_focus(NULL);

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

	/*
	 * TODO
	 * - change focus ?
	 */

	screen_remove_window(window->screen, window);
	free(window);
}

