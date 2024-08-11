#include <intr.h>

#include "i68s_sys_break.h"
#include "i68s_sys_interrupts.h"
#include "i68s_sys_matrix.h"

INT_HANDLER default_int_1; // heartbeat/key scan timer
INT_HANDLER default_int_5; // system timer
INT_HANDLER default_int_6; // on/break key pressed

volatile char break_key_pressed;

DEFINE_INT_HANDLER(OnBreakKey) {
    break_key_pressed = 1 << BREAK_KEY_COL;

    // ExecuteHandler(default_int_6);
}

void i68s_sys_setup_interrupts(void) {
    // save the default interrupt handlers
    default_int_1 = GetIntVec(AUTO_INT_1);
    default_int_5 = GetIntVec(AUTO_INT_5);

    default_int_6 = GetIntVec(AUTO_INT_6);

    // override on key pressed autovector
    SetIntVec(AUTO_INT_6, OnBreakKey);

    // break key has not been pressed
    break_key_pressed = 0;
}

void i68s_sys_disable_keyboard_interrupts(void) {
    // override the default interrupt handlers
    SetIntVec(AUTO_INT_1, DUMMY_HANDLER);
    SetIntVec(AUTO_INT_5, DUMMY_HANDLER);
}

void i68s_sys_restore_keyboard_interrupts(void) {
    // restore the default interrupt handlers
    SetIntVec(AUTO_INT_1, default_int_1);
    SetIntVec(AUTO_INT_5, default_int_5);
}

void i68s_sys_restore_all_interrupts(void) {
    // restore the default interrupt handlers
    i68s_sys_restore_keyboard_interrupts();
    SetIntVec(AUTO_INT_6, default_int_6);
}

char i68s_sys_break_key(void) {
    char result = break_key_pressed;
    break_key_pressed = 0;
    return result;
}
