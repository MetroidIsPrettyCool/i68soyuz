#ifndef SOYUZ_DEFS_H
#define SOYUZ_DEFS_H

// set global state needed by other functions
void setup(void);

// restore global state on exit
void cleanup(void);

// read key matrix state into global variable ~key_matrix_state~
void read_key_matrix_state(void);

// primary logic, needs be between setup and cleanup
void run(void);

// read key matrix over and over and over again, and send it over the link port
void keymatrix_loop(void);

#endif
