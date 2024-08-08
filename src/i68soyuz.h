#ifndef SOYUZ_DEFS_H
#define SOYUZ_DEFS_H

// set global state needed by other functions
void setup(void);

// restore global state on exit
void cleanup(void);

// read key matrix state into global variable ~key_matrix_state~
void read_key_matrix_state(void);

// primary logic
void run(void);

#endif
