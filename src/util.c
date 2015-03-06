#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wayland-client.h>

void
die(char *err)
{
	fprintf(stderr, "ERROR: %s.\n", err);
	exit(EXIT_FAILURE);
}

void
spawn(void *data, uint32_t time, uint32_t value, uint32_t state)
{
	char * const *command = data;

	if (time || value) {} /* FIXME shut up compiler */

	if (state != WL_KEYBOARD_KEY_STATE_PRESSED)
		return;

	if (fork() == 0) {
		execvp(command[0], command);
		exit(EXIT_FAILURE);
	}
}

