#ifndef I68S_INTERRUPTS_H
#define I68S_INTERRUPTS_H

// save default interrupt handlers for later
void setup_ints(void);

// replace interrupt autovectors 1 and 5 with dummies
void disable_ints(void);

// restore default interrupt autovectors 1 and 5
void restore_ints(void);

#endif
