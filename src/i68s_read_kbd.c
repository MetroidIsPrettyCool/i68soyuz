#include "i68s_interrupts.h"

#include "i68s_read_kbd.h"

void read_key_matrix_state(void) {
    // read key matrix
    disable_ints15();

    for (unsigned int i = 0; i < sizeof(key_matrix_state); i++) {
        key_matrix_state[i] = (unsigned char)_rowread(~((short)(1<<i)));
    }

    restore_ints15();

    // handle "ON" key
    key_matrix_state[BREAK_KEY_ROW] |= read_break_key(); // row 1 bit 0 is unused, so we'll stick the break key status here
}
