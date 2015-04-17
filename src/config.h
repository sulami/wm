#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>
#include <stdio.h>

/*
 * Load the config file and initiate the parsing.
 */
void load_config(char *);

/*
 * Take the already opened FILE, read it line by line and parse it.
 */
void parse_config(FILE *);

/*
 * Trigger a manual config reload.
 */
void reload_config(void *, uint32_t, uint32_t, uint32_t);

#endif

