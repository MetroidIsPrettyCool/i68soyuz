#ifndef I68S_INTERRUPTS_H
#define I68S_INTERRUPTS_H

// save default interrupt handlers (1, 5 and 6) for later
void setup_ints(void);

// replace interrupt autovectors 1 and 5 with dummies
void disable_ints15(void);

// restore default interrupt autovectors 1 and 5
void restore_ints15(void);

// restore default interrupt handlers (1, 5 and 6)
void cleanup_ints(void);

// get state of break key, and reset it if it's set
char read_break_key(void);

#endif
