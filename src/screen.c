#include <stdlib.h>

#include "util.h"
#include "wayland.h"
#include "wm.h"

void
new_screen(struct swc_screen *swc)
{
	struct screen *screen = malloc(sizeof(struct screen));
	if (!screen)
		die("Failed to allocate screen");

	screen->swc = swc;
	screen->num_windows = 0;
	wl_list_init(&screen->windows);
	swc_screen_set_handler(swc, &screen_handler, screen);
	wm.active_screen = screen;
}

void
screen_usable_geometry_changed(void *data)
{
	struct screen *screen = data;

	if (screen) {} /* FIXME shut up the compiler */
	/*
	 * TODO
	 * - perhaps rearrange windows
	 */
}

void
screen_entered(void *data)
{
	struct screen *screen = data;

	wm.active_screen = screen;
}

void
screen_add_window(struct screen *screen, struct window *window)
{
	window->screen = screen;
	wl_list_insert(&screen->windows, &window->link);
	++screen->num_windows;
	swc_window_show(window->swc);
}

void
screen_remove_window(struct screen *screen, struct window *window)
{
	window->screen = NULL;
	wl_list_remove(&window->link);
	--screen->num_windows;
	swc_window_hide(window->swc);
}

