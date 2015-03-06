#include <stdlib.h>
#include <swc.h>

#include "screen.h"
#include "util.h"
#include "window.h"
#include "wm.h"

void
new_window(struct swc_window *swc)
{
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

