#include <stdlib.h>
#include <swc.h>

#include "util.h"
#include "window.h"

void
new_window(struct swc_window *swc)
{
	struct window *window = malloc(sizeof(struct window));
	if (!window)
		die("Failed to allocate window");

	window->swc = swc;
	window->screen = NULL;

	/* TODO
	 * - set handler
	 * - add window to active screen
	 * - focus window
	 */
}

