#ifndef I68S_READ_KDB_H
#define I68S_READ_KDB_H

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

unsigned char key_matrix_state[KEY_MATRIX_HEIGHT];
unsigned char prev_key_matrix_state[KEY_MATRIX_HEIGHT];

void read_key_matrix_state(void);

#endif
