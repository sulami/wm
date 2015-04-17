#ifndef BINDING_H
#define BINDING_H

/*
 * Register a new move bind with swc/Wayland. Takes the key and
 * coordinates.
 */
void add_move_bind(int, int, int);

/*
 * Register a resize bind, takes the key and dimensions.
 */
void add_resize_bind(int, int, int);

/*
 * Register a warp bind. Works just like adding move binds.
 */
void add_warp_bind(int, int, int);

/*
 * Register a focus bind. Takes the key and the direction to switch in,
 * usually -1 or 1.
 */
void add_focus_bind(int, int);

/*
 * Register a spawn bind. Takes the command to run.
 */
void add_spawn_bind(int, char *);

/*
 * Register a config reload bind.
 */
void add_reload_bind(int);

/*
 * Register a quit bind.
 */
void add_quit_bind(int);

#endif

