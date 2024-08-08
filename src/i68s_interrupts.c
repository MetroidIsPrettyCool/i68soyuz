#include <intr.h>

#include "i68s_interrupts.h"

INT_HANDLER default_int_1; // heartbeat/key scan timer
INT_HANDLER default_int_5; // system timer
INT_HANDLER default_int_6; // on/break key pressed

volatile char break_key_pressed;

DEFINE_INT_HANDLER(OnBreakKey) {
    break_key_pressed = 1;

    ExecuteHandler(default_int_6);
}

void setup_ints(void) {
    // save the default interrupt handlers
    default_int_1 = GetIntVec(AUTO_INT_1);
    default_int_5 = GetIntVec(AUTO_INT_5);

    default_int_6 = GetIntVec(AUTO_INT_6);

    // override on key pressed autovector
    SetIntVec(AUTO_INT_6, OnBreakKey);

    // break key has not been pressed
    break_key_pressed = 0;
}

void disable_ints15(void) {
    // override the default interrupt handlers
    SetIntVec(AUTO_INT_1, DUMMY_HANDLER);
    SetIntVec(AUTO_INT_5, DUMMY_HANDLER);
}

void restore_ints15(void) {
    // restore the default interrupt handlers
    SetIntVec(AUTO_INT_1, default_int_1);
    SetIntVec(AUTO_INT_5, default_int_5);
}

void cleanup_ints(void) {
    // restore the default interrupt handlers
    restore_ints15();
    SetIntVec(AUTO_INT_6, default_int_6);
}

char read_break_key(void) {
    char result = break_key_pressed;
    break_key_pressed = 0;
    return result;
}
