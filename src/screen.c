#include "wayland.h"
#include "wm.h"

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

