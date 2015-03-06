#include <stdlib.h>
#include <swc.h>

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
	window->screen = wm.active_screen;

	/* TODO
	 * - set handler
	 * - focus window
	 */
}

