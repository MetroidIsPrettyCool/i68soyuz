// void i68s_sys_read_matrix(unsigned char* buf) -- Read the calculator key matrix and store its state into the supplied
// buffer. The buffer should be at least KEY_MATRIX_HEIGHT bytes big. Each byte of the buffer is a platform-specific
// bitfield describing the state of a given key, where 0 indicates "released" and 1 indicates "pressed". This is bitwise
// NOT-ed from the internal representation, where 1 indicated "released" and 0 indicates "pressed".
//
// Defines the following:
//
// KEY_MATRIX_HEIGHT -- Size (number of bytes) in the key matrix, AKA how many rows there are.
//
// BREAK_KEY_ROW -- Because the ON/Break key isn't scanned like the other keys, we need to "stuff" it into an unused
// position of the matrix. This is the row (buffer index) where we'll do that.
//
// BREAK_KEY_COL -- Likewise, this is the column (bit) where we'll inject the ON/Break key state.

#ifndef I68S_SYS_MATRIX_H
#define I68S_SYS_MATRIX_H

#if defined(USE_TI92PLUS) || defined(USE_TI89)

void i68s_sys_read_matrix(unsigned char*);

#endif

#if defined(__TI83p__)

void i68s_sys_read_matrix(unsigned char*) __z88dk_fastcall __naked __z88dk_callee;

#endif

#ifdef USE_TI92PLUS

#define KEY_MATRIX_HEIGHT 10

// Row and Column of an empty slot in the key matrix where we'll stuff the break key state
#define BREAK_KEY_ROW 1
#define BREAK_KEY_COL 0

#endif

#ifdef USE_TI89

#define KEY_MATRIX_HEIGHT 7

// Row and Column of an empty slot in the key matrix where we'll stuff the break key state
#define BREAK_KEY_ROW 6
#define BREAK_KEY_COL 7

#endif

#ifdef __TI83p__

#define KEY_MATRIX_HEIGHT 7

// Row and Column of an empty slot in the key matrix where we'll stuff the break key state
#define BREAK_KEY_ROW 5
#define BREAK_KEY_COL 0

#endif

#endif
