#ifndef I68S_READ_KDB_H
#define I68S_READ_KDB_H

extern unsigned char key_matrix_state[KEY_MATRIX_HEIGHT];
extern unsigned char prev_key_matrix_state[KEY_MATRIX_HEIGHT];

void read_key_matrix_state(void);

#endif
