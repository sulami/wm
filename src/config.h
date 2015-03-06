#ifndef CONFIG_H
#define CONFIG_H

/*
 * Load the config file and parse it.
 */
void load_config(char *);

/*
 * Take the already opened FILE, read it line by line and parse it.
 */
void parse_config(FILE *);

/*
 * Try to open the file at the path given and return the FILE.
 */
FILE *open_config(char *);

#endif

