#include <kbd.h>
#include <intr.h>

#include "i68s_sys_break.h"
#include "i68s_sys_input.h"
#include "i68s_sys_matrix.h"
#include "i68s_sys_setup_cleanup.h"
#include "i68s_sys_output.h"

INT_HANDLER default_int_1; // heartbeat/key scan timer
INT_HANDLER default_int_5; // system timer
INT_HANDLER default_int_6; // on/break key pressed

volatile unsigned char break_key_pressed;

DEFINE_INT_HANDLER(OnBreakKey) {
    break_key_pressed = 1 << BREAK_KEY_COL;

    // ExecuteHandler(default_int_6);
}

static void setup_interrupts(void) {
    // save the default interrupt handlers
    default_int_1 = GetIntVec(AUTO_INT_1);
    default_int_5 = GetIntVec(AUTO_INT_5);

    default_int_6 = GetIntVec(AUTO_INT_6);

    // override on key pressed autovector
    SetIntVec(AUTO_INT_6, OnBreakKey);

    // break key has not been pressed
    break_key_pressed = 0;
}

static void disable_keyboard_interrupts(void) {
    // override the default interrupt handlers
    SetIntVec(AUTO_INT_1, DUMMY_HANDLER);
    SetIntVec(AUTO_INT_5, DUMMY_HANDLER);
}

static void restore_keyboard_interrupts(void) {
    // restore the default interrupt handlers
    SetIntVec(AUTO_INT_1, default_int_1);
    SetIntVec(AUTO_INT_5, default_int_5);
}

static void restore_all_interrupts(void) {
    // restore the default interrupt handlers
    restore_keyboard_interrupts();
    SetIntVec(AUTO_INT_6, default_int_6);
}

void i68_sys_setup(void) {
    setup_interrupts();

    i68s_sys_clear_screen();
}

void i68_sys_cleanup(void) {
    restore_all_interrupts();

    i68s_sys_clear_keys();
}

unsigned char i68s_sys_break_key(void) {
    unsigned char result = break_key_pressed;
    break_key_pressed = 0;
    return result;
}

void i68s_sys_read_matrix(unsigned char* matrix) {
    static unsigned short i, j;

    i = 0;
    j = 1;
    for (; i != KEY_MATRIX_HEIGHT; i++, j <<= 1) {
        disable_keyboard_interrupts();
        
        matrix[i] = (unsigned char)_rowread_inverted(j);
        
        restore_keyboard_interrupts();
    }
}
