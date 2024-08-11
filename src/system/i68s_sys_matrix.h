// i68s_sys_read_matrix(x) -- read key matrix with specified mask

#ifndef I68S_SYS_MATRIX_H
#define I68S_SYS_MATRIX_H

#if defined(USE_TI92PLUS)

#include <kbd.h>

#define i68s_sys_read_matrix _rowread

#endif

#ifdef USE_TI92PLUS

#define KEY_MATRIX_HEIGHT 10

// Row and Column of an empty slot in the key matrix where we'll stuff the break key state
#define BREAK_KEY_ROW 1
#define BREAK_KEY_COL 0

#endif

/* #ifdef USE_TI89 */

/* #define KEY_MATRIX_HEIGHT 7 */

/* // Row and Column of an empty slot in the key matrix where we'll stuff the break key state */
/* #define BREAK_KEY_ROW 6 */
/* #define BREAK_KEY_COL 7 */

/* #endif */

#endif
