// i68s_sys_read_matrix(x) -- read key matrix into specified array

#ifndef I68S_SYS_MATRIX_H
#define I68S_SYS_MATRIX_H

#if defined(USE_TI92PLUS) || defined(USE_TI89)

// unsigned char i68s_sys_read_matrix(unsigned char);
void i68s_sys_read_matrix(unsigned char*);


#endif

#if defined(__TI83p__)

// unsigned char i68s_sys_read_matrix(unsigned char) __z88dk_fastcall __naked __z88dk_callee;

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
