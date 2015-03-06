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
	wl_list_init(&screen->windows);
	swc_screen_set_handler(swc, &screen_handler, screen);
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
	if (data) {} /* FIXME shut up the compiler */
}

