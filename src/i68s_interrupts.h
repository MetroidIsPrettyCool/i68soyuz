#ifndef I68S_INTERRUPTS
#define I68S_INTERRUPTS

// save default interrupt handlers for later
void setup_ints(void);

// replace interrupt autovectors 1 and 5 with dummies
void disable_ints(void);

// restore default interrupt autovectors 1 and 5
void restore_ints(void);

#endif
