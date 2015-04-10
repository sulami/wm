#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>

/*
 * Load the config file and initiate the parsing.
 */
void load_config(char *);

/*
 * Take the already opened FILE, read it line by line and parse it.
 */
void parse_config(FILE *);

/*
 * Register a new move bind with swc/Wayland. Takes the key and
 * coordinates.
 */
void add_move_bind(int, int, int);

/*
 * Register a warp bind. Works just like adding move binds.
 */
void add_warp_bind(int, int, int);

/*
 * Register a spawn bind. Takes the command to run.
 */
void add_spawn_bind(int, char *);

/*
 * Register a config reload bind.
 */
void add_reload_bind(int);

/*
 * Trigger a manual config reload.
 */
void reload_config(void *, uint32_t, uint32_t, uint32_t);

#endif

