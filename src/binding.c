#include <stdlib.h>
#include <string.h>
#include <swc.h>

#include "config.h"
#include "window.h"
#include "wm.h"
#include "util.h"

void
add_move_bind(int key, int x, int y)
{
	struct movement_set *ms = malloc(sizeof(struct movement_set));
	if (!ms) {
		warn("Failed to allocate memory for move bind");
		return;
	}

	ms->x = x;
	ms->y = y;

	swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO, key, &window_move, ms);
}

void
add_resize_bind(int key, int w, int h)
{
	struct resize_set *rs = malloc(sizeof(struct resize_set));
	if (!rs) {
		warn("Failed to allocate memory for resize bind");
		return;
	}

	rs->w = w;
	rs->h = h;

	swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO, key, &window_resize, rs);
}

void
add_warp_bind(int key, int x, int y)
{
	struct warp_set *ws = malloc(sizeof(struct warp_set));
	if (!ws){
		warn("Failed to allocate memory for warp bind");
		return;
	}

	ws->x = x;
	ws->y = y;

	swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO, key, &window_warp, ws);
}

void
add_spawn_bind(int key, char *cmd)
{
	char *command = malloc(sizeof(char) * strlen(cmd) + 1);
	if (!command) {
		warn("Failed to allocate memory for spawn bind");
		return;
	}

	strcpy(command, cmd);

	swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO, key, &spawn, command);
}

void
add_focus_bind(int key, int direction)
{
	int *dir = malloc(sizeof(int));
	if (!dir) {
		warn("Failed to allocate memory for focus bind");
		return;
	}

	swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO, key,
	                &window_change_focus, dir);
}

void
add_reload_bind(int key)
{
	swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO, key, &reload_config,
	                NULL);
}

void
add_quit_bind(int key)
{
	swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO, key, &quit, NULL);
}

