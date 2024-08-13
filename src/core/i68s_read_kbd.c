#include "i68s_sys_break.h"
#include "i68s_sys_matrix.h"

#include "i68s_read_kbd.h"

unsigned char key_matrix_state[KEY_MATRIX_HEIGHT] = {0};
unsigned char prev_key_matrix_state[KEY_MATRIX_HEIGHT] = {0};

void read_key_matrix_state(void) {
    i68s_sys_read_matrix(key_matrix_state);

    // handle "ON" key
    key_matrix_state[BREAK_KEY_ROW] |= i68s_sys_break_key();
}
