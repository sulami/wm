#ifndef CONFIG_H
#define CONFIG_H

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

#endif

